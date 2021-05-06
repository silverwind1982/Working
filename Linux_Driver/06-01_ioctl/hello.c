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
#include "devone_ioctl.h"

MODULE_LICENSE("Dual BSD/GPL");

#define DRIVER_NAME "devone"

static int devone_devs = 1;
static int devone_major = 0;
static int devone_minor_base = 0;
static int devone_minor = 0;
static struct cdev devone_cdev;
static struct class *devone_class = NULL;

struct devone_data *dev_data;

struct devone_data {
    rwlock_t lock;
    unsigned char val;
};

long devone_ioctl(struct file *filp, unsigned int cmd, unsigned long arg)
{
    struct devone_data *dev_data = filp->private_data;
    int retval = 0;
    unsigned char val;
    struct ioctl_cmd data;

    printk("%s called\n", __func__);
    memset(&data, 0, sizeof(data));

    switch (cmd) {
        case IOCTL_VALSET:
            if (!capable(CAP_SYS_ADMIN)) {
                retval = -EPERM;
                goto done;
            }
            if (!access_ok(VERIFY_READ, (void __user *)arg, _IOC_SIZE(cmd))) {
                retval = -EFAULT;
                goto done;
            }
            if (copy_from_user(&data, (int __user *)arg, sizeof(data))) {
                retval = -EFAULT;
                goto done;
            }

            printk("IOCTL_cmd IOCTL_VALSET val %u (%s)\n", data.val, __func__);

            write_lock(&dev_data->lock);
            dev_data->val = data.val;
            write_unlock(&dev_data->lock);

            break;

        case IOCTL_VALGET:
            if (!access_ok(VERIFY_READ, (void __user *)arg, _IOC_SIZE(cmd))) {
                retval = -EFAULT;
                goto done;
            }
            read_lock(&dev_data->lock);
            val = dev_data->val;
            read_unlock(&dev_data->lock);
            data.val = val;

            if (copy_to_user((int __user *)arg, &data, sizeof(data))) {
                retval = -EFAULT;
                goto done;
            }

            printk("IOCTL_cmd IOCTL_VALGET val %u (%s)\n", data.val, __func__);

            break;

        default:
            retval = -ENOTTY;
            break;
    }

done:
    return (retval);
}

static ssize_t devone_read(struct file *filp, char __user *buf, size_t count, loff_t *f_pos)
{
    struct devone_data *dev_data = filp->private_data;
    unsigned char val;
    int retval;
    int i;

    printk("%s called\n", __func__);
    read_lock(&dev_data->lock);
    val = dev_data->val;
    read_unlock(&dev_data->lock);

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

    printk("%s called\n", __func__);

    file->private_data = dev_data;

    return 0;
}

static int devone_close(struct inode *inode, struct file *filp)
{
    printk("%s called\n", __func__);

    return 0;
}

struct file_operations devone_fops = {
    .owner = THIS_MODULE,
    .open = devone_open,
    .release = devone_close,
    .read = devone_read,
    .unlocked_ioctl = devone_ioctl,
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

    dev_data = kmalloc(sizeof(struct devone_data), GFP_KERNEL);
    if (dev_data == NULL) {
        return -ENOMEM;
    }

    rwlock_init(&dev_data->lock);
    dev_data->val = 0xAD;

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

    if (dev_data) {
        kfree(dev_data);
    }

    printk(KERN_ALERT "%s driver removed.\n", DRIVER_NAME);
}

module_init(devone_init);
module_exit(devone_exit);
