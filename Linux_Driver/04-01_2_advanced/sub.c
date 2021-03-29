#include <linux/module.h>
#include <linux/init.h>

void sub_1(void)
{
    printk("%s: sub() called\n", __func__);
}
