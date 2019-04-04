/*
 * test-3.c -- Illustrating the __init, __initdata and __exit macros.
 */

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>


static int test3_data __initdata = 3;

static int __init test_3_init(void)
{
	printk(KERN_INFO "somekinda message %d\n", test3_data);
	return 0;
}

static void __exit test_3_exit(void)
{
	printk(KERN_INFO "exiting 3\n");
}


module_init(test_3_init);
module_exit(test_3_exit);