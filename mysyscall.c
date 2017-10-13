#include<stdio.h>
#include<unistd.h>
#include<linux/unistd.h>
#include<linux/time.h>
int main(){
struct timespec time;
 syscall(326, &time);
//long long int  nano_time = time.tv_sec * (10^9) + time.tv_nsec ;
 printf("syscall return value :%ld\n", time.tv_nsec);
return 0;
}

