#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
int main()
{
	pid_t pid;
	printf("For LINUX:\n");
	printf("PID of current process before fork: %d\n",getpid());
	pid = fork();
	printf("PID of current process after fork : %d\n",getpid());
	printf("LINUX: %d\n",pid);
	
	printf("For UNIX:\n");
	printf("PID of current process before fork: %d\n",getpid());
	pid = fork();
	printf("PID of current process after fork: %d\n",getpid());
	printf("UNIX: %d\n",pid);
	
	printf("For MAC:\n");
	printf("PID of current process before fork: %d\n",getpid());
	pid = fork();
	printf("PID of current process after fork: %d\n",getpid());
	printf("MAC: %d\n",pid);
	
	return 0;
}
