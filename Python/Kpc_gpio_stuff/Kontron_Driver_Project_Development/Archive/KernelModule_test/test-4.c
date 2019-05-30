/*
 * Test Module Kernel 4
 */
#include <linux/module.h>		/* Required for all modules */
#include <linux/kernel.h>		/* Required for KERN_INFO */
#include <linux/init.h>			/* Required for macros */

#define DRIVER_AUTHOR 			"Howard Zhou"
#define DRIVER_DESC				"Test 4 - Kernel Module"


static int __init init_test_4 (void) 
{
	printk(KERN_INFO "Testing, version 4\n");
	return 0;
}

static void __exit cleanup_test_4(void)
{
	printk(KERN_INFO "Goodbye, version 4\n");
}

module_init(init_test_4);
module_exit(cleanup_test_4);

MODULE_LICENSE("GPL");

MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_SUPPORTED_DEVICE("test device");