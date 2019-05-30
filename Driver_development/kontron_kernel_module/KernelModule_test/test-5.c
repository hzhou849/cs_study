/*
* test module 5 - Command line argument passing to a module.
*/
#include <linux/module.h>
// Step 1
#include <linux/moduleparam.h>  /* Required for passing parameters */
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/stat.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR ("Howard Zhou");

static short int myshort = 1;
static int myint = 420;
static long int mylong = 9999;
static char *mystring = "blah";
static int myintArray[2] = { -1, -1 };
static int arr_argc = 0;

/*
 * Parameters have 3 arguments
 * module_param(name_var, data_type, permissions_bit)
 * 
 * S_IRUSR - Reading 
 * S_IWUSR - Writing
 * S_IXUSR - Execution
 * S_IWGRP
 * S_IRGRP 
 * 
 * S_IRUSR
 */

