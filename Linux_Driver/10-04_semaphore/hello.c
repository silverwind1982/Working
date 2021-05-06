#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>  // for imajor

#include <linux/types.h>  // for current
#include <linux/kernel.h>  // for current
#include <linux/cdev.h>  // for current
#include <linux/sched.h>  // for current
#include <linux/uaccess.h>  // for current
#include <linux/slab.h>  // for current

MODULE_LICENSE("Dual BSD/GPL");

#define DRIVER_NAME "devone"

static unsigned int devone_devs = 1;
static unsigned int devone_major = 0;
static unsigned int devone_minor = 0;

static struct cdev devone_cdev;
static struct class *devone_class = NULL;
static dev_t devone_dev;

struct devone_data {
    struct semaphore sem;
};

#define DATA_MAX 64
static unsigned char data[DATA_MAX];

ssize_t devone_write(struct file *filp, const char __user *buf, size_t count, loff_t *f_pos)
{
    struct devone_data *dev = filp->private_data;
    int len;
    int retval = 0;

    if (down_interruptible(&dev->sem)) {
        return -ERESTARTSYS;
    }

    if (count > DATA_MAX) {
        len = DATA_MAX;
    } else {
        len = count;
    }

    if (copy_from_user(data, buf, len)) {
        retval = -EFAULT;
        goto out;
    }
    retval = len;

out:
    up(&dev->sem);
    return (retval);
}

ssize_t devone_read(struct file *filp, char __user *buf, size_t count, loff_t *f_pos)
{
    struct devone_data *dev = filp->private_data;
    int len;
    int retval;

    if (down_interruptible(&dev->sem)) {
        return -ERESTARTSYS;
    }

    if (count > DATA_MAX) {
        len = DATA_MAX;
    } else {
        len = count;
    }

    if (copy_to_user(buf, data, len)) {
        retval = -EFAULT;
        goto out;
    }
    retval = len;

out:
    up(&dev->sem);
    return (retval);
}

static int devone_open(struct inode *inode, struct file *file)
{
    struct devone_data *dev;

    dev = kmalloc(sizeof(struct devone_data), GFP_KERNEL);
    if (dev == NULL) {
        printk("%s: No memory\n", __func__);
        return -ENOMEM;
    }

    sema_init(&dev->sem, 1);

    file->private_data = dev;

    return 0;
}

static int devone_close(struct inode *inode, struct file *filp)
{
    struct devone_data *dev = filp->private_data;

    if (dev) {
        kfree(dev);
    }

    return 0;
}

struct file_operations devone_fops = {
    .owner = THIS_MODULE,
    .open = devone_open,
    .release = devone_close,
    .read = devone_read,
    .write = devone_write,
};

static int devone_init(void)
{
    dev_t dev = MKDEV(devone_major, 0);
    int alloc_ret = 0;
    int cdev_err = 0;
    struct device *class_dev = NULL;

    alloc_ret = alloc_chrdev_region(&dev, 0, devone_devs, DRIVER_NAME);
    if (alloc_ret) {
        goto error;
    }
    devone_major = MAJOR(dev);

    cdev_init(&devone_cdev, &devone_fops);

    cdev_err = cdev_add(&devone_cdev, MKDEV(devone_major, 0), devone_devs);
    if (cdev_err) {
        goto error;
    }

    devone_class = class_create(THIS_MODULE, "devone");
    if (IS_ERR(devone_class)) {
        goto error;
    }

    devone_dev = MKDEV(devone_major, devone_minor);
    class_dev = device_create(devone_class, NULL, devone_dev, NULL, "devone%d", devone_minor);

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
    dev_t dev = MKDEV(devone_major, 0);

    device_destroy(devone_class, devone_dev);
    class_destroy(devone_class);

    cdev_del(&devone_cdev);
    unregister_chrdev_region(dev, devone_devs);

    printk(KERN_ALERT "%s driver removed.\n", DRIVER_NAME);
}

module_init(devone_init);
module_exit(devone_exit);
