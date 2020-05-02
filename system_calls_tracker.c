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
#include <sys/mman.h>
#include <stdbool.h>
#include <getopt.h>
#include <errno.h>


/*
 * Check if a file exist using fopen() function
 * return 1 if the file exist otherwise return 0
*/

//This method validate if the program the user is trying to run exists!
int ifcommandexists(const char * fname){
    if (system(("which %s > /dev/null 2>&1\n", fname))) {
        // Command doesn't exist...
        exit(EXIT_FAILURE);
    } else {
        // Command does exist, do something with it...
        printf("------------------------------------------------\n");
        printf("The program introduced exists\n");
        printf("------------------------------------------------\n");
    }
}

int main(int argc, char *argv[])
{
    int opt, val, i;
    char *program;
    char *pseudo_program;
    i = 0;
    if(argc > 6){
        printf("Expected less than 5 arguments.\n");
        exit(EXIT_FAILURE);
    }
    //these lines of code are placed to validate if there are any parameters
    if (optind >= argc){
        printf("argc %d", argc);
        fprintf(stderr, "Expected argument after main %s [-v or -V program name]\n"
                        "ex. ./main -v soffice -writer\n"
                        "    ./main -V soffice -draw\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    //This two lines of code validate if the program exists
    pseudo_program = strcat(strdup(argv[2]), " --help");
    ifcommandexists(pseudo_program);

    char * args0[2] = {"",NULL};
    char * args1[3] = {"","", NULL};
    char * args2[4] = {"", "", "", NULL};
    char * args3[5] = {"", "", "", "", NULL};
    //These lines of code permit to run programs that need one or many parameters
    while (argv[i] != NULL){
        if (i == 2){
            program =  strdup(argv[i]);
        } else if (i > 2) {
            program = strcat(program, " ");
            program = strcat(program, strdup(argv[i]));
        }
        if (i == 2){
            args0[0] =  strdup(argv[i]);
            args1[0] =  strdup(argv[i]);
            args2[0] =  strdup(argv[i]);
            args3[0] =  strdup(argv[i]);
        } else if (i > 2) {
            args0[i-2] =  strdup(argv[i]);
            args1[i-2] =  strdup(argv[i]);
            args2[i-2] =  strdup(argv[i]);
            args3[i-2] =  strdup(argv[i]);
        }
        i++;
    }

    printf("Program to be run: %s \n", program);
    printf("------------------------------------------------\n");

    char * path = "/bin/ls";
    char * args = "ls";
    //These lines of code are to select between the two possible options.
    while ((opt = getopt(argc, argv, "if:vV")) != -1)
    {
        switch (opt){
            case 'v':
                if(argc == 3){
                    debug_without_step(args0[0],args0);
                }else if(argc == 4){
                    debug_without_step(args0[0],args1);
                }else if(argc == 5){
                    debug_without_step(args0[0],args2);
                }else if(argc == 6){
                    debug_without_step(args0[0],args3);
                }
                _exit(EXIT_SUCCESS);
            case 'V':
                if(argc == 3){
                    debug_with_step(args0[0],args0);
                }else if(argc == 4){
                    debug_with_step(args0[0],args1);
                }else if(argc == 5){
                    debug_with_step(args0[0],args2);
                }else if(argc == 6){
                    debug_with_step(args0[0],args3);
                }
                exit(EXIT_SUCCESS);
            default:
                fprintf(stderr, "Usage: %s [-v or -V program name]\n",
                        argv[0]);
                exit(EXIT_FAILURE);
        }
    }
}

/*int main()
{
    char * path = "/bin/ls";
    char * args = "ls";
    if(1)
    {  
        debug_with_step(path,args);
    }
    else
    {
        debug_without_step(path,args);
    }
    
    return 0;
}*/

void debug_with_step(char * path,char * args[]){
    pid_t child;
    const int long_size = sizeof(long);
    child = fork();
    if(child == 0) {
        ptrace(PTRACE_TRACEME, 0, NULL, NULL);
        execv(path, args);
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

void debug_without_step(char * path,char * args[]){
    pid_t child;
    long orig_eax, eax;
    long params[3];
    int status;
    int insyscall = 0;
    child = fork();
    if (child == 0)
    {
        ptrace(PTRACE_TRACEME, 0, NULL, NULL);
        execv(path, args);
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