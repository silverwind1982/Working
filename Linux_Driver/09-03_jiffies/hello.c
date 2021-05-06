#include <linux/module.h>
#include <linux/init.h>
#include <linux/time.h>
#include <linux/delay.h>

MODULE_LICENSE("Dual BSD/GPL");

static int hello_init(void)
{
    printk("driver loaded, jiffies = %lu, HZ = %d\n", jiffies, HZ);

    return 0;
}

static void hello_exit(void)
{
    printk("driver unloaded\n");
}

module_init(hello_init);
module_exit(hello_exit);
