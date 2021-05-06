#include <linux/module.h>
#include <linux/init.h>
#include <linux/timer.h>
#include <linux/cdev.h>
#include <linux/slab.h>
#include <linux/uaccess.h>
#include <asm/uaccess.h>

MODULE_LICENSE("Dual BSD/GPL");

static unsigned int timeout_value = 10;
static unsigned int irq_value = 3;

module_param(timeout_value, uint, 0);
module_param(irq_value, uint, 0);

static int devone_devs = 1;
static int devone_major = 0;
static struct cdev devone_cdev;

struct devone_data {
    struct timer_list timeout;
    struct timer_list irq;
    spinlock_t lock;
    wait_queue_head_t wait;
    int dma_done;
    int timeout_done;
};

static void devone_timeout(struct timer_list *timer)
{
    struct devone_data *dev = from_timer(dev, timer, timeout);
    unsigned long flags;

    spin_lock_irqsave(&dev->lock, flags);
    printk("%s called\n", __func__);
    dev->timeout_done = 1;
    wake_up(&dev->wait);
    spin_unlock_irqrestore(&dev->lock, flags);
}

static void devone_irq(struct timer_list *timer)
{
    struct devone_data *dev = from_timer(dev, timer, irq);
    unsigned long flags;

    spin_lock_irqsave(&dev->lock, flags);
    printk("%s called\n", __func__);
    dev->dma_done = 1;
    wake_up(&dev->wait);
    spin_unlock_irqrestore(&dev->lock, flags);
}

static void devone_dma_transfer(struct devone_data *dev)
{
    dev->dma_done = 0;
    mod_timer(&dev->irq, jiffies + irq_value * HZ);
}

ssize_t devone_read(struct file *filp, char __user *buf, size_t count, loff_t *f_pos)
{
    struct devone_data *dev = filp->private_data;
    int i;
    unsigned char val = 0xab;
    int retval;

    printk("%s called\n", __func__);

    dev->timeout_done = 0;
    mod_timer(&dev->timeout, jiffies + timeout_value * HZ);

    devone_dma_transfer(dev);

    wait_event(dev->wait, (dev->dma_done == 1) || (dev->timeout_done == 1));

    del_timer_sync(&dev->timeout);

    if (dev->timeout_done == 1) {
        return -EIO;
    }

    for (i = 0; i < count; ++i) {
        if (copy_to_user(&buf[i], &val, 1)) {
            retval = -EFAULT;
            goto out;
        }
    }

    retval = count;

out:
    return (retval);
}

int devone_open(struct inode *inode, struct file *filp)
{
    struct devone_data *dev;

    printk("%s called\n", __func__);

    dev = kmalloc(sizeof(struct devone_data), GFP_KERNEL);
    if (dev == NULL) {
        return -ENOMEM;
    }

    spin_lock_init(&dev->lock);

    init_waitqueue_head(&dev->wait);

    dev->dma_done = 0;
    dev->timeout_done = 0;

    timer_setup(&dev->timeout, devone_timeout, 0);

    timer_setup(&dev->irq, devone_irq, 0);

    filp->private_data = dev;

    return 0;
}

int devone_close(struct inode *inode, struct file *filp)
{
    struct devone_data *dev = filp->private_data;

    printk("%s called\n", __func__);

    if (dev) {
        del_timer_sync(&dev->timeout);
        del_timer_sync(&dev->irq);
        kfree(dev);
    }

    return 0;
}

struct file_operations devone_fops = {
    .open = devone_open,
    .release = devone_close,
    .read = devone_read,
};

static int devone_init(void)
{
    dev_t dev = MKDEV(devone_major, 0);
    int ret;
    int major;
    int err;

    ret = alloc_chrdev_region(&dev, 0, devone_devs, "devone");
    if (ret < 0) {
        return ret;
    }

    devone_major = major = MAJOR(dev);

    cdev_init(&devone_cdev, &devone_fops);
    devone_cdev.owner = THIS_MODULE;
    devone_cdev.ops = &devone_fops;

    err = cdev_add(&devone_cdev, MKDEV(devone_major, 0), 1);
    if (err) {
        return err;
    }

    printk("driver (major %d) loaded\n", major);
    printk("timeout %u irq %u timer (%s)\n", timeout_value, irq_value, __func__);

    return 0;
}

static void devone_exit(void)
{
    dev_t dev = MKDEV(devone_major, 0);

    printk("driver unloaded\n");

    cdev_del(&devone_cdev);

    unregister_chrdev_region(dev, devone_devs);
}

module_init(devone_init);
module_exit(devone_exit);
