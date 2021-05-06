#include <linux/module.h>
#include <linux/init.h>

MODULE_LICENSE("Dual BSD/GPL");

int g_sample_counter __attribute__ ((unused));
const int g_sample_counter2 __attribute__ ((unused));
static int g_sample_counter3 __attribute__ ((unused));
int g_sample_counter4 __attribute__ ((unused));

EXPORT_SYMBOL(g_sample_counter4);

static int hello_init(void)
{
    printk(KERN_ALERT "driver loaded\n");
    return 0;
}

static void hello_exit(void)
{
    printk(KERN_ALERT "driver unloaded\n");
}

module_init(hello_init);
module_exit(hello_exit);
