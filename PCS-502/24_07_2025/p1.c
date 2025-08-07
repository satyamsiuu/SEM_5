#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>

int main()
{
	printf("Satyam Singh Rawat(C) - 61\n");
	
	pid_t child_pid;
	
	child_pid = fork();
	
	if(child_pid == 0)
		printf("Child process: PID=%d\n:",getpid());
	else if(child_pid>0)
		printf("Parent Process: PID=%d, Child PID=%d\n",getpid(),child_pid);
	else
		perror("Fork failed\n");	
	return 0;
}
		
