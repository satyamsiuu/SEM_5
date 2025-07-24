//SINGLE FORK 
#include<stdio.h> 
#include<unistd.h> 
int main()
{
	pid_t pid;
	pid = fork();
	printf("\nLINUX\n%d\n",pid);
	return 0;
}

