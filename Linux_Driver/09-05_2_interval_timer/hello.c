#include <linux/module.h>
#include <linux/init.h>
#include <linux/timer.h>

MODULE_LICENSE("Dual BSD/GPL");

#define TIMEOUT_VALUE (3*HZ)

static struct timer_list tickfn;

static void sample_timeout(struct timer_list *timer)
{
    struct timer_list *ptr = timer;

    mod_timer(ptr, jiffies + TIMEOUT_VALUE);
    printk("ptr %p (%s), jiffies: %lu\n", ptr, __func__, jiffies);
}

static int hello_init(void)
{
    printk("driver loaded: %p\n", &tickfn);

    timer_setup(&tickfn, sample_timeout, 0);

    mod_timer(&tickfn, jiffies + TIMEOUT_VALUE);

    return 0;
}

static void hello_exit(void)
{
    int ret;

    ret = del_timer_sync(&tickfn);

    printk("driver unloaded\n");
}

module_init(hello_init);
module_exit(hello_exit);
