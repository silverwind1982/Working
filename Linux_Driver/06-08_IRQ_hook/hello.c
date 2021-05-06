#include <linux/module.h>
#include <linux/init.h>
#include <linux/interrupt.h>

MODULE_LICENSE("Dual BSD/GPL");

const int IRQ_NUM = 16;
void *irq_dev_id = (void *) &IRQ_NUM;

static irqreturn_t sample_intr(int irq, void *dev_id)
{
    printk("irq %d dev_id %p (%s)\n", irq, dev_id, __func__);

    return IRQ_NONE;
}

static int hello_init(void)
{
    printk(KERN_ALERT "driver loaded\n");

    if (request_irq(IRQ_NUM,
                    sample_intr,
                    IRQF_SHARED,
                    "sample_intr_name",
                    (void *)irq_dev_id)) {
    }

    return 0;
}

static void hello_exit(void)
{
    free_irq(IRQ_NUM, (void *)irq_dev_id);
    printk(KERN_ALERT "driver unloaded\n");
}

module_init(hello_init);
module_exit(hello_exit);
