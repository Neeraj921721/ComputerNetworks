#include<linux/init.h>
#include<linux/module.h>
#include<linux/kernel.h>
MODULE_LICENSE("GPL");
MODULE_AUTHOR("KRSir");
static int hello_init(void){
	printk(KERN_ALERT ".......................Enterng the module ............\n");
	printk(KERN_ALERT "Hello World from Kernel !\n");
	return 0;
}
static void hello_exit(void){
	printk(KERN_ALERT "Good bye ! exiting module.............................. \n");
}
module_init(hello_init);
module_exit(hello_exit);

