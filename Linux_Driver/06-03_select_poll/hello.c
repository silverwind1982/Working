#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>  // for imajor

#include <linux/types.h>
#include <linux/kernel.h>
#include <linux/cdev.h>
#include <linux/sched.h>
#include <linux/device.h>
#include <linux/uaccess.h>
#include <linux/slab.h>
#include <linux/poll.h>
#include <linux/timer.h>

MODULE_LICENSE("Dual BSD/GPL");

static unsigned int timeout_value = 3;

module_param(timeout_value, uint, 0);

#define DRIVER_NAME "devone"

static int devone_devs = 1;
static int devone_major = 0;
static int devone_minor_base = 0;
static int devone_minor = 0;
static struct cdev devone_cdev;
static struct class *devone_class = NULL;

struct devone_data {
    struct timer_list timeout;
    spinlock_t lock;
    wait_queue_head_t read_wait;
    int timeout_done;
    struct semaphore sem;
};

static void devone_timeout(struct timer_list* arg)
{
    struct devone_data *dev_data = (struct devone_data *)arg;
    unsigned long flags;

    printk("%s called\n", __func__);

    spin_lock_irqsave(&dev_data->lock, flags);

    dev_data->timeout_done = 1;
    wake_up_interruptible(&dev_data->read_wait);

    spin_unlock_irqrestore(&dev_data->lock, flags);
}

unsigned int devone_poll(struct file *filp, poll_table *wait)
{
    struct devone_data *dev_data = filp->private_data;
    unsigned int mask = 0;//POLLOUT | POLLWRNORM;

    printk("%s called\n", __func__);

    if (dev_data == NULL) {
        return -EBADFD;
    }

    down(&dev_data->sem);
    poll_wait(filp, &dev_data->read_wait, wait);
    if (dev_data->timeout_done == 1) {
        mask |= POLLIN | POLLRDNORM;
    }
    up(&dev_data->sem);

    printk("%s returned (mask 0x%x)\n", __func__, mask);
    return mask;
}

static ssize_t devone_write(struct file *filp, const char __user *buf, size_t count, loff_t *f_pos)
{
    return -EFAULT;
}

long devone_ioctl(struct file *filp, unsigned int cmd, unsigned long arg)
{
    return -EFAULT;
}

static ssize_t devone_read(struct file *filp, char __user *buf, size_t count, loff_t *f_pos)
{
    struct devone_data *dev_data = filp->private_data;
    unsigned char val;
    int retval;
    int i;

    if (down_interruptible(&dev_data->sem))
        return -ERESTARTSYS;

    if (dev_data->timeout_done == 0) {
        up(&dev_data->sem);
        if (filp->f_flags & O_NONBLOCK) {
            printk("dev_data->timeout_done = %d\n", dev_data->timeout_done);
            //if (dev_data->timeout_done != 1) {
                return -EAGAIN;
            //}
        }
        printk("filp->f_flags = %x\n", filp->f_flags);

        do {
            retval = wait_event_interruptible_timeout(dev_data->read_wait, dev_data->timeout_done == 1, 1*HZ);
            if (retval == -ERESTARTSYS)
                return retval;
        } while (retval == 0);

        if (down_interruptible(&dev_data->sem))
            return -ERESTARTSYS;
    }

    val = 0xff;
    for (i = 0; i < count; ++i) {
        if (copy_to_user(&buf[i], &val, 1)) {
            retval = -EFAULT;
            goto out;
        }
    }
    retval = count;

out:
    dev_data->timeout_done = 0;
    /* restart timer */
    mod_timer(&dev_data->timeout, jiffies + timeout_value * HZ);

    up(&dev_data->sem);
    return (retval);
}

static int devone_close(struct inode *inode, struct file *filp)
{
    struct devone_data *dev_data = filp->private_data;

    printk("%s called\n", __func__);

    if (dev_data) {
        del_timer_sync(&dev_data->timeout);
        kfree(dev_data);
    }

    return 0;
}

static int devone_open(struct inode *inode, struct file *filp)
{
    struct devone_data *dev_data;

    printk("%s called\n", __func__);

    dev_data = kmalloc(sizeof(struct devone_data), GFP_KERNEL);
    if (dev_data == NULL) {
        return -ENOMEM;
    }

    spin_lock_init(&dev_data->lock);

    init_waitqueue_head(&dev_data->read_wait);

    sema_init(&dev_data->sem, 1);

    timer_setup(&dev_data->timeout, NULL, 0);
    dev_data->timeout.function = devone_timeout;

    filp->private_data = dev_data;

    /* start timer */
    dev_data->timeout_done = 0;
    mod_timer(&dev_data->timeout, jiffies + timeout_value * HZ);

    return 0;
}

struct file_operations devone_fops = {
    .owner = THIS_MODULE,
    .open = devone_open,
    .release = devone_close,
    .read = devone_read,
    .write = devone_write,
    .unlocked_ioctl = devone_ioctl,
    .poll = devone_poll,
};

static int devone_init(void)
{
    dev_t dev = MKDEV(devone_major, 0);
    int alloc_ret = 0;
    int cdev_err = 0;
    struct device *class_dev = NULL;
    dev_t devone_dev;

    alloc_ret = alloc_chrdev_region(&dev, devone_minor_base, devone_devs, DRIVER_NAME);
    if (alloc_ret)
        goto error;
    devone_major = MAJOR(dev);

    cdev_init(&devone_cdev, &devone_fops);

    devone_dev = MKDEV(devone_major, devone_minor_base + devone_minor);
    cdev_err = cdev_add(&devone_cdev, devone_dev, devone_devs);
    if (cdev_err)
        goto error;

    /* register class */
    devone_class = class_create(THIS_MODULE, DRIVER_NAME);
    if (IS_ERR(devone_class)) {
        goto error;
    }
    class_dev = device_create(devone_class, NULL, devone_dev, NULL, "devone%d", devone_minor_base + devone_minor);

    printk("%s driver(major: %d) installed.\n", DRIVER_NAME, devone_major);

    return 0;

error:
    if (cdev_err == 0)
        cdev_del(&devone_cdev);

    if (alloc_ret == 0)
        unregister_chrdev_region(dev, devone_devs);

    return -1;
}

static void devone_exit(void)
{
    dev_t devone_dev = MKDEV(devone_major, devone_minor_base + devone_minor);

    /* unregister class */
    device_destroy(devone_class, devone_dev);
    class_destroy(devone_class);

    cdev_del(&devone_cdev);
    unregister_chrdev_region(devone_dev, devone_devs);


    printk(KERN_ALERT "%s driver removed.\n", DRIVER_NAME);
}

module_init(devone_init);
module_exit(devone_exit);
