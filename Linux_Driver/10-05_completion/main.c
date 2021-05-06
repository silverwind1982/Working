#include <linux/module.h>
#include <linux/init.h>
#include <linux/sched.h>
#include <linux/completion.h>
#include <linux/sched/signal.h>
#include <linux/delay.h>
#include <linux/kthread.h>

MODULE_LICENSE("Dual BSD/GPL");

static struct task_struct *kmain_task = NULL;
//static wait_queue_head_t wait;
static struct completion comp;

static int sample_thread(void *num)
{
    printk("%s called\n", __func__);

    // daemonize("sample_thread");  // only available if KERNEL_VERSION< (3,8,0)
    allow_signal(SIGTERM);

    for (;;) {
        //sleep_on_timeout(&wait, 3 * HZ);
        ssleep(3);

        if (kthread_should_stop()) {
            break;
        }
    }

    printk("%s leaved\n", __func__);

    complete_and_exit(&comp, 0);

    return 0;
}

static int hello_init(void)
{
    printk("driver loaded\n");

    init_completion(&comp);
//    init_waitqueue_head(&wait);

    kmain_task = kthread_create(sample_thread, NULL, "sample_kthread");
    if (IS_ERR(kmain_task)) {
        return PTR_ERR(kmain_task);
    }

    wake_up_process(kmain_task);

    return 0;
}

static void hello_exit(void)
{
    printk("driver unloaded\n");

    kthread_stop(kmain_task);
    printk("after stop\n");
    printk("after stop\n");
    printk("after stop\n");
    wait_for_completion(&comp);
}

module_init(hello_init);
module_exit(hello_exit);
