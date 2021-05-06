#include <linux/module.h>
#include <linux/init.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>

MODULE_LICENSE("Dual BSD/GPL");

#define PROCNAME "driver/sample"

int sample_proc_read(char *page, char **start, off_t off, int count, int *eof, void *data)
{
    int len;

    printk(KERN_INFO "%s called\n", __func__);

    if (off > 0) {
        len = 0;
    } else {
        len = sprintf(page, "%d\n", sample_flag);
    }

    return (len);
}

int sample_proc_write(struct file *filp, const char *buffer, unsigned long count, void *data)
{
/*    int len;

    printk("page = %p, *start = %p, off = %d, count = %d, *eof = %d, data = %p\n",
            page, *start, (int)off, count, *eof, data);

    len = DUMMY_BUFSIZ;
    if (len > PAGE_SIZE) {
        return -ENOBUFS;
    }

    memcpy(page, dummy, len);
    *eof = 1;

    printk("len = %d (%s)\n", len, __func__);
    return (len);*/
    return 8;
}

static int hello_init(void)
{
    struct proc_dir_entry *entry;
    int i;

    /* add /proc */
    entry = create_proc_entry(PROCNAME, 0666, NULL);
    if (entry == NULL) {
        printk(KERN_WARNING "sample: unable to create /proc entry\n");
        return -ENOMEM;
    }

    entry->read_proc = sample_proc_read;
    entry->write_proc = sample_proc_write;
    entry->owner = sample_proc_read;

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
