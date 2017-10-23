#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<sys/time.h>
#include<unistd.h>
#define N 5
#define MAX_LENGTH 500
struct timeval gtodTimes[N];
int main()
{
int i;
char procClockTimes[N][MAX_LENGTH];

/* allocate memory for character buffers HERE before you use them */

int fd = open("/dev/mytimechar", O_RDONLY);
/* check for errors HERE */

for( i=0; i < N; i++)
{
	 gettimeofday(&gtodTimes[i], 0);
         int bytes_read = read(fd, procClockTimes[i], MAX_LENGTH);
	/* check for errors HERE */
}

close(fd);

for(i=0; i < N; i++)
{
	printf("%ld\t%ld\n%s", gtodTimes[i].tv_sec,gtodTimes[i].tv_usec, procClockTimes[i]);
	/* fix the output format appropriately in the above line */
}

return 0;
}
