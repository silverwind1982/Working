#include <linux/module.h>
#include <linux/init.h>

MODULE_LICENSE("Dual BSD/GPL");

atomic_t counter = ATOMIC_INIT(3);

static int hello_init(void)
{
    int n;

    atomic_inc(&counter);
    n = atomic_read(&counter);

    printk("n = %d\n", n);

    if (atomic_dec_and_test(&counter)) {
        printk("atomic_dec_and_test() TRUE\n");
    } else {
        printk("atomic_dec_and_test() FALSE\n");
    }

    return 0;
}

static void hello_exit(void)
{
    printk("sample driver unloaded\n");
}

module_init(hello_init);
module_exit(hello_exit);
