#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Hanyang");

static int module_begin(void) {
	printk(KERN_ALERT "Hello, Wellcometo module!!\n");
	return 0;
}

static void module_end(void) {
	printk(KERN_ALERT "Goodbye, Exit module!!\n");
}

module_init(module_begin);
module_exit(module_end);
