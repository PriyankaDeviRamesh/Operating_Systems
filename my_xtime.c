
#include  <linux/linkage.h>
#include  <linux/export.h>
#include  <linux/time.h>
#include  <asm/uaccess.h>
#include  <linux/printk.h>
#include  <linux/slab.h>
asmlinkage int sys_xtime(struct timespec *current_time){

 struct timespec time =  current_kernel_time();

 if( !access_ok( VERIFY_WRITE, current_time, sizeof(current_time)))
     return -EFAULT;
 copy_to_user(current_time, &time, sizeof(time));  
 printk("%ld", time.tv_nsec);  
   return 0;
}

EXPORT_SYMBOL(sys_xtime);
