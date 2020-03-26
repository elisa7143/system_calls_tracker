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

int main()
{
    debug_without_step();
    return 0;
}

void debug_with_step(){
    pid_t child;
    long orig_eax, eax;
    long params[3];
    int status;
    int insyscall = 0;
    int Tpid, stat, res;
    int signo = 0;
    child = fork();
    if (child == 0)
    {
        ptrace(PTRACE_TRACEME, 0, NULL, NULL);
        execl("/bin/ls", "ls", NULL);
    }
    else
    {
        int status;
        wait(&status);
        struct user_regs_struct regs;
        res = waitpid(child, &stat, WUNTRACED);
        if ((res != child) || !(WIFSTOPPED(stat)) ) {
            printf("Unexpected wait result res %d stat %x\n",res,stat);
            exit(1);
        }
        while (1)
        {
            ptrace(PTRACE_GETREGS, child, NULL, &regs);
            printf("eip: %x\n", (unsigned int) regs.rcx);
            if ((res = ptrace(PTRACE_SINGLESTEP, child, 0, signo)) < 0) {
			perror("Ptrace singlestep error");
			exit(1);
		}
		res = wait(&stat);
        if ((signo = WSTOPSIG(stat)) == SIGTRAP) {
			signo = 0;
		}
        if ((signo == SIGHUP) || (signo == SIGINT)) {
			ptrace(PTRACE_CONT, child, 0, signo);
			printf("Child took a SIGHUP or SIGINT. We are done\n");
			break;
		}
            //waitpid(child, &status, 0);
            if(WIFEXITED(status)) break;
            /*
		    res = wait(&stat);
            if (WIFEXITED(stat))
                break;
            orig_eax = ptrace(PTRACE_PEEKUSER,
                              child, 8 * ORIG_RAX, NULL);

            if (insyscall == 0)
            {
                /* Syscall entry */
                /*insyscall = 1;
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
            { 
                eax = ptrace(PTRACE_PEEKUSER,
                             child, 8 * ORIG_RAX, NULL);
                insyscall = 0;
            }
            ptrace(PTRACE_SYSCALL,
                   child, NULL, NULL);*/
        }
    }
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