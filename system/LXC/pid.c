#define _GNU_SOURCE
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <sched.h>
#include <signal.h>
#include <unistd.h>
 
#define STACK_SIZE (1024 * 1024)
 
// sync primitive
int checkpoint[2];

static char child_stack[STACK_SIZE];
char* const child_args[] = {
    "/bin/bash",
    NULL
};

int child_main(void* arg)
{
    char c;

    // init sync primitive
    close(checkpoint[1]);
    // wait...
    read(checkpoint[0], &c, 1);

    printf(" - [%5d] World !\n", getpid());
    sethostname("In Namespace", 12);
    execv(child_args[0], child_args);
    printf("Ooops\n");
    return 1;
}

// dyc: this isolation does not work for ps/top 
//      because these commands read process info from /proc,
//      which is not (yet) isolated

int main()
{
    pipe(checkpoint);
    printf(" - [%5d] Hello ?\n", getpid());

    // The low byte of flags contains the number of the termination signal sent to the parent when the child dies.
    // By CLONE_NEWIPC, child's ipcs won't see parent's ipc objects
    int child_pid = clone(child_main, child_stack+STACK_SIZE,
            CLONE_NEWUTS | CLONE_NEWIPC | CLONE_NEWPID | SIGCHLD, NULL);
    if (child_pid == -1) {
        perror("clone failed:");
        return -1;
    }

    // signal "done"
    close(checkpoint[1]);
    waitpid(child_pid, NULL, 0);
    printf("container exit\n");
    return 0;
}
