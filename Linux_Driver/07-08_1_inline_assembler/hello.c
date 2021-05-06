#include <linux/module.h>
#include <linux/init.h>
#include <linux/interrupt.h>

MODULE_LICENSE("Dual BSD/GPL");

void do_asm(void)
{
    u16 cx = 0, dx = 0;
    u16 ax = 0x0200;

    asm("int $0x1a"
            : "+a" (ax), "=c" (cx), "=d" (dx)
            :
            : "ebx", "esi", "edi");

    printk("ax = %x, cx = %x, dx = %x\n", ax, cx, dx);
}

static int hello_init(void)
{
    printk(KERN_ALERT "driver loaded\n");

    do_asm();

    return 0;
}

static void hello_exit(void)
{
    printk(KERN_ALERT "driver unloaded\n");
}

module_init(hello_init);
module_exit(hello_exit);
