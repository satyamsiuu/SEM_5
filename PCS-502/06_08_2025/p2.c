#include<stdio.h>
#include<sys/types.h>
#include<stdlib.h>
#include<unistd.h>

int main()
{
    printf("Satyam Singh Rawat(C) - 61\n");
    int cpid;
    cpid = fork();
    if(cpid>0)
    {
        printf("This is the parent process PID: %d and child process PID: %d\n",getpid(),cpid);
        sleep(5);
    }
    else if(cpid==0)
    {
        printf("This is the zombie child with PID: %d and Parent pid: %d\n",getpid(),getppid());
        exit(0);
    }
    else
    {
        printf("Forking failed\n");
    }

    return 0;
}
