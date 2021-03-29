#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>  // for imajor

#include <linux/types.h>
#include <linux/kernel.h>
#include <linux/cdev.h>
#include <linux/sched.h>
#include <linux/device.h>
#include <linux/uaccess.h>

MODULE_LICENSE("Dual BSD/GPL");

#define DRIVER_NAME "devone"

static int devone_devs = 2;
static int devone_major = 316;
static int devone_minor_base = 0;
static int devone_minor = 0;
static struct cdev devone_cdev;
static struct class *devone_class = NULL;


static ssize_t devone_read(struct file *filp, char __user *buf, size_t count, loff_t *f_pos)
{
    int i;
    unsigned char val = 0xff;
    int retval;

    if (count > 10) {
        count = 10;
    }

    printk("%s called, count = %zu\n", __func__, count);
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

static int devone_open(struct inode *inode, struct file *file)
{
    printk("%s: major: %d minor: %d (pid: %d)\n",
            __func__, imajor(inode), iminor(inode), current->pid);

    inode->i_private = inode;
    file->private_data = file;

    printk("  i_private = %p, private_data = %p\n",
            inode->i_private, file->private_data);

    return 0;
}

static int devone_close(struct inode *inode, struct file *file)
{
    printk("%s: major: %d minor: %d (pid: %d)\n",
            __func__, imajor(inode), iminor(inode), current->pid);

    printk("  i_private = %p, private_data = %p\n",
            inode->i_private, file->private_data);

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
    int alloc_ret = 0;
    int cdev_err = 0;
    struct device *class_dev = NULL;
    dev_t devone_dev;

    alloc_ret = alloc_chrdev_region(&dev, devone_minor_base, devone_devs, DRIVER_NAME);
    if (alloc_ret)
        goto error;
    devone_major = MAJOR(dev);

    cdev_init(&devone_cdev, &devone_fops);
    devone_cdev.owner = THIS_MODULE;

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
