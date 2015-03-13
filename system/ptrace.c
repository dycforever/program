#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/syscall.h>

#ifdef __x86_64__
# include <sys/reg.h> 
#else
# include <linux/user.h> 
#endif

#include "syscall2str.h"

const int long_size = sizeof(long);

void parent(int child);

void reverse(char *str)
{ 
    int i, j;
    char temp;
    for(i = 0, j = strlen(str) - 2; 
            i <= j; ++i, --j) {
        temp = str[i];
        str[i] = str[j];
        str[j] = temp;
    }
}

// dyc: copy from @addr to @str
void getdata(pid_t child, unsigned long addr, char *str, int len)
{ 
    char *laddr;
    int i, j;
    union u {
        long val;
        char chars[long_size];
    }data;

    i = 0;
    j = len / long_size;
    laddr = str;
    while(i < j) {
        data.val = ptrace(PTRACE_PEEKDATA, child, addr + i * sizeof(long), NULL);
        memcpy(laddr, data.chars, long_size);
        ++i;
        laddr += long_size;
    }
    j = len % long_size;
    if(j != 0) {
        data.val = ptrace(PTRACE_PEEKDATA, child, addr + i * sizeof(long), NULL);
        memcpy(laddr, data.chars, j);
    }
    str[len] = '\0';
    printf("str1: %s\n", str);
}

void putdata(pid_t child, unsigned long addr, char *str, int len)
{ 
    printf("str: %s\n", str);
    char *laddr;
    int i, j;
    union u {
        long val;
        char chars[long_size];
    }data;

    i = 0;
    j = len / long_size;
    laddr = str;
    while(i < j) {
        memcpy(data.chars, laddr, long_size);
        ptrace(PTRACE_POKEDATA, child, addr + i * sizeof(long), data.val);
        ++i;
        laddr += long_size;
    }
    j = len % long_size;
    if(j != 0) {
        memcpy(data.chars, laddr, j);
        ptrace(PTRACE_POKEDATA, child, addr + i * sizeof(long), data.val);
    }
}

int main() { 
    pid_t child;
    child = fork();
    if(child == 0) {
        // dyc: child will be stopped when entering/exitting a system call, or signal delivered
        ptrace(PTRACE_TRACEME, 0, NULL, NULL);
        execl("/bin/ls", "ls", NULL);
    } else {
        parent(child);
    }
    return 0;
}

// #define syscall2str(sysnum) #sysnum

#ifdef __x86_64__
void parent(int child) {
    long orig_eax;
    long params[3];
    int status;
    char *str, *laddr;
    // dyc: toggle means child is entering or exitting the system call
    int toggle = 0;
    while(1) {
        wait(&status);
        if(WIFEXITED(status))
            break;
        orig_eax = ptrace(PTRACE_PEEKUSER, child, sizeof(long) * ORIG_RAX, NULL);
        if(orig_eax == SYS_write) {
            if(toggle == 0) {
                printf("entering [%s]\n", syscall2str(orig_eax));
                // dyc: entering system call
                toggle = 1;
                // dyc: 寄存器和write()系统调用的参数之间的关系，是和系统实现强相关的.
                params[0] = ptrace(PTRACE_PEEKUSER, child, sizeof(long) * RBX, NULL);
                params[1] = ptrace(PTRACE_PEEKUSER, child, sizeof(long) * RCX, NULL);
                params[2] = ptrace(PTRACE_PEEKUSER, child, sizeof(long) * RDX, NULL);
                printf("going to printf\n");
                fflush(stdout);
                printf("origin 0: %p 1: %p 2: %p\n", (char*)params[0], (char*)params[1], (char*)params[2]);
                fflush(stdout);
                str = (char *)calloc((params[2]+1), sizeof(char));
                getdata(child, params[1], str, params[2]);
                reverse(str);
                putdata(child, params[1], str, params[2]);
            }
            else {
                toggle = 0;
            }
        }
        ptrace(PTRACE_SYSCALL, child, NULL, NULL);
    }
}
#else
void parent(int child) {
    long orig_eax;
    long params[3];
    int status;
    char *str, *laddr;
    int toggle = 0;
    while(1) {
        wait(&status);
        if(WIFEXITED(status))
            break;
        orig_eax = ptrace(PTRACE_PEEKUSER, child, sizeof(long) * ORIG_EAX, NULL);
        if(orig_eax == SYS_write) {
            if(toggle == 0) {
                toggle = 1;
                params[0] = ptrace(PTRACE_PEEKUSER, child, sizeof(long) * EBX, NULL);
                params[1] = ptrace(PTRACE_PEEKUSER, child, sizeof(long) * ECX, NULL);
                params[2] = ptrace(PTRACE_PEEKUSER, child, sizeof(long) * EDX, NULL);
                str = (char *)calloc((params[2]+1), sizeof(char));
                getdata(child, params[1], str, params[2]);
                reverse(str);
                putdata(child, params[1], str, params[2]);
            }
            else {
                toggle = 0;
            }
        }
        ptrace(PTRACE_SYSCALL, child, NULL, NULL);
    }
}
#endif