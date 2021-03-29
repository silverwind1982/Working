#include <linux/module.h>
#include <linux/init.h>
#include <linux/slab.h>

MODULE_LICENSE("Dual BSD/GPL");

struct sample_data {
    // lock, file, wait are not used in this file
    // But if they are removed, "Segmentation fault" would occur while insmod.
    spinlock_t lock;
    struct file *file;
    wait_queue_head_t wait;

    // list_head is a double linked list
    struct list_head list;
    int no;
};

struct sample_data head;

void free_struct(void)
{
    struct list_head *listptr;
    struct sample_data *entry;

    list_for_each(listptr, &head.list) {
        entry = list_entry(listptr, struct sample_data, list);
        printk("Free: no = %d (list %p, next %p, next %p)\n",
                entry->no, &entry->list, entry->list.next, entry->list.prev);

        kfree(entry);
    }
}

void show_struct(void)
{
    struct list_head *listptr;
    struct sample_data *entry;

    printk("======================================\n");
    printk("no = %d (list %p, next %p, next %p)\n",
            head.no, &head.list, head.list.next, head.list.prev);

    list_for_each(listptr, &head.list) {
        entry = list_entry(listptr, struct sample_data, list);
        printk("no = %d (list %p, next %p, next %p)\n",
                entry->no, &entry->list, entry->list.next, entry->list.prev);
    }
}

void remove_struct(struct sample_data *entry)
{
    printk("Free: no = %d (list %p, next %p, next %p)\n",
            entry->no, &entry->list, entry->list.next, entry->list.prev);

    list_del(&entry->list);
    kfree(entry);
}

struct sample_data *add_struct(int no)
{
    struct sample_data *ptr;

    ptr = kmalloc(sizeof(struct sample_data), GFP_KERNEL);
    if (ptr) {
        ptr->no = no;
#if 0  // Stack: FILO
        list_add(&ptr->list, &head.list);
#else  // Queue: FIFO
        list_add_tail(&ptr->list, &head.list);
#endif
    }

    return ptr;
}

static int sample_init(void)
{
    struct sample_data *p;

    memset(&head, 0, sizeof(head));
    INIT_LIST_HEAD(&head.list);
    show_struct();

    add_struct(1);
    show_struct();

    p = add_struct(2);
    show_struct();

    add_struct(3);
    show_struct();

    if (p) {
        remove_struct(p);
        show_struct();
    }

    free_struct();

    printk(KERN_ALERT "sample driver loaded\n");

    return 0;
}

static void sample_exit(void)
{
    printk(KERN_ALERT "sample driver unloaded\n");
}

module_init(sample_init);
module_exit(sample_exit);
