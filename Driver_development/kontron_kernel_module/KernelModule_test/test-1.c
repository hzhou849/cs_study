/* 
 * test-1.c simple kernel module.
 * **Extensions need to be *.c 
 */

 #include <linux/module.h>  /* needed by all modules. */ 
 #include <linux/kernel.h>  /* Nedded for KERN_INFO */
 #include <linux/init.h>	/* Needed for the macros */

int init_module(void)
{
	/* Grep with dmesg to see the  message*/
	printk(KERN_INFO "testing 1.\n"); 

	/* A non 0 return means init_module failed; module can't be loaded. */
	return 0;
}

void cleanup_module(void)
{
	printk(KERN_INFO "Bye. Cleanup executed.\n");
}
