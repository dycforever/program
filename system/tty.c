
#define _XOPEN_SOURCE 600
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/ioctl.h>
#include <sys/select.h>

#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <termios.h>

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

void parent(int fdm, int);
void child(int);

int main(int ac, char *av[])
{
    int fdm, fds;
    int rc;
    fdm = posix_openpt(O_RDWR);
    if (fdm < 0) {
        fprintf(stderr, "Error %d on posix_openpt()\n", errno);
        return 1;
    }

    rc = grantpt(fdm);
    if (rc != 0) {
        fprintf(stderr, "Error %d on grantpt()\n", errno);
        return 1;
    }

    rc = unlockpt(fdm);
    if (rc != 0) {
        fprintf(stderr, "Error %d on unlockpt()\n", errno);
        return 1;
    }

    int childpid = fork();
    if (childpid) {
        parent(fdm, childpid);
    } else {
        child(fdm);
    }
    return 0;
}

void child(int fdm) {
    char input[150];
    int rc;
    int fds;

    // to be a session leader
    setsid();
    ioctl(0, TIOCSCTTY, 1);

    // attach to a new tty/pts
    fds = open(ptsname(fdm), O_RDWR);


    struct termios slave_orig_term_settings; // Saved terminal settings
    struct termios new_term_settings; // Current terminal settings

    // Save the defaults parameters of the slave side of the PTY
    rc = tcgetattr(fds, &slave_orig_term_settings);

    // Set RAW mode on slave side of PTY
    new_term_settings = slave_orig_term_settings;
    cfmakeraw (&new_term_settings);

    // this make no \n instead of \r\n as line delimitor
    tcsetattr (fds, TCSANOW, &new_term_settings);

//    close(0); // Close standard input (current terminal)
//    close(1); // Close standard output (current terminal)
//    close(2); // Close standard error (current terminal)
//
//    dup(fds); // PTY becomes standard input (0)
//    dup(fds); // PTY becomes standard output (1)
//    dup(fds); // PTY becomes standard error (2)

    char* str = "I am ready\n";
    rc = write(fds, str, strlen(str));
    printf("child write %d bytes\n", rc);


    memset(input, 0, sizeof(input));
    rc = read(fds, input, sizeof(input));
    printf("child read %d bytes: %s\n", rc, input);

    str = "OK\n";
    write(fds, str, strlen(str));
    printf("child exit\n");
    exit(0);
}

void parent(int fdm, int childpid) {
    char input[150];
    int i;

    sigset_t sigmask, sigmask_select;
    sigemptyset(&sigmask_select);
    sigemptyset(&sigmask);
    sigaddset(&sigmask, SIGCHLD);
    int wait_id;
    int status=0;

    do {
        fd_set readfd;
        FD_ZERO(&readfd);
        FD_SET(fdm, &readfd);
        int selret=pselect( fdm+1, &readfd, NULL, NULL, NULL, &sigmask_select );
        // can also listem stdin if necessary
        if( selret>0 && FD_ISSET( fdm, &readfd ) ) {
            memset(input, 0, sizeof(input));
            int rc = read(fdm, input, sizeof(input));
            printf("parent read %d bytes: %s*\n", rc, input);
            if (rc < 0)
                wait_id=waitpid( childpid, &status, WNOHANG );

            char* str = "I am ready\n";
            if (memcmp(input, str, strlen(str)) == 0) {
                write(fdm, "req", 3);
                write(fdm, "\n", 1);
            }
        }
    } while( wait_id==0 || (!WIFEXITED( status ) && !WIFSIGNALED( status )) );
}
