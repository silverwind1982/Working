#include <linux/module.h>
#include <linux/init.h>
#include <linux/time.h>
#include <linux/delay.h>

MODULE_LICENSE("Dual BSD/GPL");

static int hello_init(void)
{
    struct timeval now;
    suseconds_t diff;
    volatile int i;

    printk(KERN_ALERT "driver loaded\n");

    do_gettimeofday(&now);
    diff = now.tv_usec;  // microsecond

    printk("Current UTC: %lu (%lu)\n", now.tv_sec, now.tv_usec);

    for (i = 0; i < 9999; ++i) {
        do_gettimeofday(&now);
        diff = now.tv_usec - diff;
    }

    printk(KERN_ALERT "Elapsed time: %lu\n", diff);

    return 0;
}

static void hello_exit(void)
{
    printk(KERN_ALERT "driver unloaded\n");
}

module_init(hello_init);
module_exit(hello_exit);
