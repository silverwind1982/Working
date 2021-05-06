#include <linux/module.h>
#include <linux/init.h>
#include <linux/tty.h>
#include <linux/sched/signal.h>

MODULE_LICENSE("Dual BSD/GPL");

static void hook_tty_console(char *msg)
{
    struct tty_struct *tty;

    tty = current->signal->tty;

    if (tty != NULL) {
        ((tty->ops)->write)(tty, msg, strlen(msg));
        ((tty->ops)->write)(tty, "\r\n", 2);
    }
}

static int hello_init(void)
{
    printk(KERN_ALERT "driver loaded\n");

    hook_tty_console("this message is written by sample driver\n");

    return 0;
}

static void hello_exit(void)
{
    printk(KERN_ALERT "driver unloaded\n");
}

module_init(hello_init);
module_exit(hello_exit);
