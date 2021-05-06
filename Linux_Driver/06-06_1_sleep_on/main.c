#include <linux/module.h>
#include <linux/init.h>
#include <linux/sched.h>

MODULE_LICENSE("Dual BSD/GPL");

static wait_queue_head_t wait;

static int hello_init(void)
{
    printk(KERN_ALERT "driver loaded\n");

    init_waitqueue_head(&wait);
    sleep_on(wait);

    return 0;
}

static void hello_exit(void)
{
    printk(KERN_ALERT "driver unloaded\n");
}

module_init(hello_init);
module_exit(hello_exit);
