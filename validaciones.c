#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <semaphore.h>
#include <stdbool.h>
#include <unistd.h>
#include <getopt.h>
#include <sys/types.h>
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

    //These lines of code permit to run programs that need one or many parameters
    while (argv[i] != NULL){
        if (i == 2){
            program =  strdup(argv[i]);
        } else if (i > 2) {
            program = strcat(program, " ");
            program = strcat(program, strdup(argv[i]));
        }
        i++;
    }

    printf("Program to be run: %s \n", program);
    printf("------------------------------------------------\n");

    //These lines of code are to select between the two possible options.
    while ((opt = getopt(argc, argv, "if:vV")) != -1)
    {
        switch (opt){
            case 'v':
                system(program);
                _exit(EXIT_SUCCESS);
            case 'V':
                system(program);
                exit(EXIT_SUCCESS);
            default:
                fprintf(stderr, "Usage: %s [-v or -V program name]\n",
                        argv[0]);
                exit(EXIT_FAILURE);
        }
    }
}