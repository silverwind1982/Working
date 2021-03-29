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

static unsigned int devone_devs = 2;
static unsigned int devone_major = 316;

module_param(devone_major, uint, 0);  // set devone_major as a module parameter, type is uint, file permission is not set
//module_param(devone_major, uint, 0644);  // set devone_major as a module parameter, type is uint, file permission is 644
// usage: # insmod ./hello.ko devone_major=261

static struct cdev devone_cdev;

struct devone_data {
    unsigned char val;
    rwlock_t lock;
};

ssize_t devone_write(struct file *filp, const char __user *buf, size_t count, loff_t *f_pos)
{
    struct devone_data *p = filp->private_data;
    unsigned char val;
    int retval = 0;

    printk("%s: count %zu pos %lld\n", __func__, count, *f_pos);

    if (count >= 1) {
        if (copy_from_user(&val, &buf[0], 1)) {
            retval = -EFAULT;
            goto out;
        }

        write_lock(&p->lock);
        p->val = val;
        write_unlock(&p->lock);
        retval = count;
    }

out:
    return (retval);
}

ssize_t devone_read(struct file *filp, char __user *buf, size_t count, loff_t *f_pos)
{
    struct devone_data *p = filp->private_data;
    int i;
    unsigned char val;
    int retval;

    read_lock(&p->lock);
    val = p->val;
    read_unlock(&p->lock);

    printk("%s: count %zu pos %lld\n", __func__, count, *f_pos);

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
    struct devone_data *p;

    printk("%s: major: %d minor: %d (pid: %d)\n",
            __func__, imajor(inode), iminor(inode), current->pid);

    p = kmalloc(sizeof(struct devone_data), GFP_KERNEL);
    if (p == NULL) {
        printk("%s: No memory\n", __func__);
        return -ENOMEM;
    }

    p->val = 0xff;
    rwlock_init(&p->lock);

    file->private_data = p;

    return 0;
}

static int devone_close(struct inode *inode, struct file *file)
{
    printk("%s: major: %d minor: %d (pid: %d)\n",
            __func__, imajor(inode), iminor(inode), current->pid);

    if (file->private_data) {
        kfree(file->private_data);
        file->private_data = NULL;
    }

    return 0;
}

struct file_operations devone_fops = {
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

    alloc_ret = alloc_chrdev_region(&dev, 0, devone_devs, DRIVER_NAME);
    if (alloc_ret) {
        goto error;
    }
    devone_major = MAJOR(dev);

    cdev_init(&devone_cdev, &devone_fops);
    devone_cdev.owner = THIS_MODULE;

    cdev_err = cdev_add(&devone_cdev, MKDEV(devone_major, 0), devone_devs);
    if (cdev_err) {
        goto error;
    }

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
    cdev_del(&devone_cdev);
    unregister_chrdev_region(dev, devone_devs);

    printk(KERN_ALERT "%s driver removed.\n", DRIVER_NAME);
}

module_init(devone_init);
module_exit(devone_exit);
