#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/syscall.h> /* For SYS_write etc */
#include <sys/user.h>
#include <sys/reg.h>
#include "sys_call_table/sys_call_table.h"
#include "sys_call_table/sys_call_table.c"
#include <sys/signal.h>
#include <stdio.h>

int main()
{
    debug_with_step();
    return 0;
}

void debug_with_step(){
 pid_t child;
    const int long_size = sizeof(long);
    child = fork();
    if(child == 0) {
        ptrace(PTRACE_TRACEME, 0, NULL, NULL);
        execl("/bin/ls", "ls", NULL);
    }
    else {
        int status;
        union u {
            long val;
            char chars[long_size];
        }data;
        struct user_regs_struct regs;
        int start = 0;
        long ins;
        char ch;
        while(1) {
            wait(&status);
            if(WIFEXITED(status))
                break;
            ptrace(PTRACE_GETREGS,
                   child, NULL, &regs);
       
                ins = ptrace(PTRACE_PEEKTEXT,
                             child, regs.rip,
                             NULL);
                char *syscall = get_sys_call_name(regs.orig_rax);
                printf("System call: %s     RBX: %ld    RCX: %ld    RDX: %ld\n",
                       syscall,
                       regs.rbx,
                       regs.rcx,
                       regs.rdx);
            
          
                ptrace(PTRACE_SINGLESTEP, child,
                       NULL, NULL);
          
                
                //printf("Enter any character: ");
                //read a single character
                ch=fgetc(stdin);
                
                if(ch==0x0A)
                {
                    ptrace(PTRACE_SYSCALL, child,
                       NULL, NULL);
                }
                //read dummy character to clear
                //input buffer, which inserts after character input
             
            
        }
    }
    return 0;
}

void debug_without_step(){
    pid_t child;
    long orig_eax, eax;
    long params[3];
    int status;
    int insyscall = 0;
    child = fork();
    if (child == 0)
    {
        ptrace(PTRACE_TRACEME, 0, NULL, NULL);
        execl("/bin/ls", "ls", NULL);
    }
    else
    {
        while (1)
        {
            wait(&status);
            if (WIFEXITED(status))
                break;
            orig_eax = ptrace(PTRACE_PEEKUSER,
                              child, 8 * ORIG_RAX, NULL);

            if (insyscall == 0)
            {
                /* Syscall entry */
                insyscall = 1;
                params[0] = ptrace(PTRACE_PEEKUSER,
                                   child, 8 * RBX,
                                   NULL);
                params[1] = ptrace(PTRACE_PEEKUSER,
                                   child, 8 * RCX,
                                   NULL);
                params[2] = ptrace(PTRACE_PEEKUSER,
                                   child, 8 * RDX,
                                   NULL);
                char *syscall = get_sys_call_name(orig_eax);
                printf("System call: %s     RBX: %ld    RCX: %ld    RDX: %ld\n",
                       syscall,
                       params[0],
                       params[1],
                       params[2]);
            }
            else
            { /* Syscall exit */
                eax = ptrace(PTRACE_PEEKUSER,
                             child, 8 * ORIG_RAX, NULL);
                insyscall = 0;
            }
            ptrace(PTRACE_SYSCALL,
                   child, NULL, NULL);
        }
    }
}