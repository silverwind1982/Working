#include <linux/module.h>
#include <linux/init.h>
#include <linux/sched.h>
#include <linux/timer.h>

MODULE_LICENSE("Dual BSD/GPL");

#define SLEEP_TIMEOUT   (5 * HZ)
#define WAKEUP_TIMEOUT  (2 * HZ)

static struct timer_list tickfn;
static wait_queue_head_t wait;
static int condition = 0;

static void sample_timeout(struct timer_list *timer)
{
    printk("%s called (jiffies = %ld)\n", __func__, jiffies);
#if 1  // test condition
    condition = 1;
#endif
    wake_up(&wait);
}

static int sample_init(void)
{
    long ret;

    printk("driver loaded: %p, HZ = %d\n", &tickfn, HZ);

    init_waitqueue_head(&wait);

    timer_setup(&tickfn, sample_timeout, 0);

#if 1  // trigger by add_timer
    tickfn.expires = jiffies + WAKEUP_TIMEOUT;
    add_timer(&tickfn);
#else  // trigger by mod_timer
    ret = mod_timer(&tickfn, jiffies + WAKEUP_TIMEOUT);
    if (ret) {
        printk("Timer firing failed. (%s)\n", __func__);
    }
#endif

    condition = 0;
    //ret = wait_event_timeout(wait, condition, SLEEP_TIMEOUT);
    ret = wait_event_timeout(wait, condition == 1, SLEEP_TIMEOUT);
    if (ret == 0) {  // timeout
        printk("wait_event timeout occured. (%s)\n", __func__);
    }

    return 0;
}

static void sample_exit(void)
{
    del_timer_sync(&tickfn);

    printk(KERN_ALERT "driver unloaded\n");
}

module_init(sample_init);
module_exit(sample_exit);
