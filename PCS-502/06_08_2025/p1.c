#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>

int main()
{
    printf("Satyam Singh Rawat(C) - 61\n");
    int cpid;
    cpid = fork();
    if(cpid>0)
    {
        printf("This parent process with PID: %d with Child PID: %d\n",getpid(),cpid);
        printf("Terminating parent process\n");
        exit(0);
    }
    else if(cpid==0)
    {
        sleep(5);
        printf("This is the orphan child with PID: %d and Parent pid: %d\n",getpid(),getppid());
    }
    else
    {
        printf("Forking failed\n");
    }
    return 0;
}
