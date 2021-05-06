#include <linux/module.h>
#include <linux/init.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/slab.h>  // kmalloc
#include <linux/uaccess.h>  // copy_from_user

MODULE_LICENSE("Dual BSD/GPL");

#define PROCNAME "sample"

static char *str = NULL;

static int hello_proc_show(struct seq_file *m, void *v)
{
    if (str != NULL) {
        seq_printf(m, "%s\n", str);
    } else {
        seq_printf(m, "NULL\n");
    }
    return 0;
};

static int sample_proc_open(struct inode *inode, struct file *file)
{
    return single_open(file, hello_proc_show, NULL);
}

static ssize_t sample_proc_write(struct file *file, const char __user *buffer, size_t count, loff_t *f_pos)
{
    char *tmp = kmalloc((count + 1), GFP_KERNEL);
    if (!tmp) {
        return -ENOMEM;
    }

    if (copy_from_user(tmp, buffer, count)) {
        kfree(tmp);
        return -EFAULT;
    }

    kfree(str);
    str = tmp;
    return count;
}

static ssize_t sample_proc_read(struct file *filp, char __user *buf, size_t count, loff_t *f_pos)
{
    printk("%s called\n", __func__);

    return seq_read(filp, buf, count, f_pos);
}

static int sample_proc_close(struct inode *inode, struct file *file)
{
    printk("%s called\n", __func__);

    return seq_release(inode, file);
}

static struct file_operations sample_operations = {
    .owner = THIS_MODULE,
    .open = sample_proc_open,
    .write = sample_proc_write,
    .read = sample_proc_read,
    .llseek = seq_lseek,
    .release = sample_proc_close,
};

static int hello_init(void)
{
    struct proc_dir_entry *entry;

    /* add /proc */
    entry = proc_create(PROCNAME, 0666, NULL, &sample_operations);
    if (entry == NULL) {
        printk(KERN_WARNING "sample: unable to create /proc entry\n");
        return -ENOMEM;
    }

    printk(KERN_ALERT "driver loaded\n");

    return 0;
}

static void hello_exit(void)
{
    remove_proc_entry(PROCNAME, NULL);

    printk(KERN_ALERT "driver unloaded\n");
}

module_init(hello_init);
module_exit(hello_exit);
