#include<linux/init.h>
#include<linux/module.h>

int hello_init(void){
	printk(KERN_ALERT "\n__________________________Inside the %s funtion________________________________\n",__FUNCTION__);
	printk(KERN_ALERT ".............................Hello from Kernel....................................\n");
return 0;
}

void hello_exit(void){
	printk(KERN_ALERT "\n__________________________Inside the %s funtion________________________________\n",__FUNCTION__);
	printk(KERN_ALERT ".............................Exiting from Kernel....................................\n");
}

module_init(hello_init);
module_exit(hello_exit);
