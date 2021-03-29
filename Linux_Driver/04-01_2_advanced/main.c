#include <linux/module.h>
#include <linux/init.h>

MODULE_LICENSE("Dual BSD/GPL");

extern void sub(void);
extern void link_ok(void*);

void external_sub(void)
{
    link_ok(NULL);
}

static int hello_init(void)
{
    printk(KERN_ALERT "driver loaded\n");

    sub();

    return 0;
}

static void hello_exit(void)
{
    printk(KERN_ALERT "driver unloaded\n");
}

module_init(hello_init);
module_exit(hello_exit);
