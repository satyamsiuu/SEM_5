#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int pid = fork();

    if (pid == 0) {
        printf("Child: I am the child process. My PID = %d\n", getpid());
    } else {
        printf("Parent: My PID = %d\n", getpid());
        printf("Parent: Waiting for child to finish...\n");

        int status;
        int child_pid = wait(&status);

        printf("Parent: Child with PID %d finished.\n", child_pid);
    }

    return 0;
}
