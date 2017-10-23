#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/fs.h>
#include<linux/cdev.h>
#include<asm/uaccess.h>
#include<linux/proc_fs.h>
#include<linux/miscdevice.h>
//#define  DEVICE_NAME "mytimechar"   
//#define  CLASS_NAME  "mytime"  

static int my_open(struct inode *inode, struct file *filep);
static ssize_t my_read(struct file *filep,char *buffer,size_t len,loff_t *offset);
static int my_close(struct inode *inodep,struct file *filep);

static int majorNumber;
//static char messages[256] ={0};
//static struct class* mytimecharClass = NULL;
//static struct device* mytimecharDevice = NULL;
static struct file_operations my_fops = {
        .owner = THIS_MODULE,
        .open = my_open,
        .release = my_close,
        .read = my_read
};


 static struct miscdevice my_misc_device = {
        .minor = MISC_DYNAMIC_MINOR,
        .name = "mytimechar",
        .fops = &my_fops
}; 


static int my_open(struct inode *inode, struct file *filep)
{
        printk(KERN_INFO "MYTIME: Device has been opened");
        return 0;
}
static int __init my_module_init(void)
{ 
       printk(KERN_INFO "MYTIME: Initialising the mytimechar LKM\n");
    //   majorNumber = register_chrdev(90, DEVICE_NAME, &my_fops);
	 majorNumber = misc_register(&my_misc_device);
       if(majorNumber < 0)
        {
                printk(KERN_ALERT "MYTIME failed to register a major number");
                return majorNumber;
        }
        //printk(KERN_INFO "MYTIME: registered correctly with major number %d\n", majorNumber);

      //majorNumber = misc_register(&my_misc_device);
        /*mytimecharClass = class_create(THIS_MODULE, CLASS_NAME); 
       if (IS_ERR(mytimecharClass)){              
        unregister_chrdev(majorNumber, DEVICE_NAME);
        printk(KERN_ALERT "Failed to register device class\n");
        return PTR_ERR(mytimecharClass);          
   }
   printk(KERN_INFO "MYTIMECHAR: device class registered correctly\n");
 
   // Register the device driver
   mytimecharDevice = device_create(mytimecharClass, NULL, MKDEV(majorNumber, 0), NULL, DEVICE_NAME);
   if (IS_ERR(mytimecharDevice)){              
      class_destroy(mytimecharClass);           
      unregister_chrdev(majorNumber, DEVICE_NAME);
      printk(KERN_ALERT "Failed to create the device\n");
      return PTR_ERR(mytimecharDevice);
   }*/
   printk(KERN_INFO "MYTIMECHAR: device class created correctly\n"); 
   return 0;
}

static ssize_t my_read(struct file *filep,char *buffer,size_t len,loff_t *offset)
{       
        struct timespec time =  current_kernel_time();
        struct timespec xtime;
	char str[500];
	int error_count=0;
	size_t num;
	getnstimeofday(&xtime);
        num = sprintf(str, "%ld,%ld,%ld,%ld", time.tv_sec ,time.tv_nsec, xtime.tv_sec, xtime.tv_nsec);
        error_count=copy_to_user(buffer,str,sizeof(str));

        if(error_count==0)
        {
		printk(KERN_INFO "MYTIME: Sent characters to the user");
                return 0;

        }
        
	else
        {
                printk(KERN_INFO "MYTIME: Failed to send  %d characters to the user",error_count);
                return -EFAULT;
        }
   return num;
}
static int my_close(struct inode *inodep,struct file *filep)
{
        printk(KERN_INFO "MYTIME: Device successfully closed");
        return 0;
}

static void __exit my_exit(void)
{

        misc_deregister(&my_misc_device);
   //     device_destroy(mytimecharClass, MKDEV(majorNumber, 0));    
     //   class_unregister(mytimecharClass);                         
     //   class_destroy(mytimecharClass);                             
      //  unregister_chrdev(90, DEVICE_NAME);            
        printk(KERN_INFO "mytimeChar: Goodbye from the LKM!\n"); 
}

module_init(my_module_init);
module_exit(my_exit);


