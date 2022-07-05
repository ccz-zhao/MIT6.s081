#include "kernel/param.h"
#include "kernel/types.h"
#include "user/user.h"
#include "kernel/fs.h"

// readline from stdin
int readline(char* argv[MAXARG], int curr_argc) {
    char buf[1024];
    int n = 0;

    // read until '\n'
    while (read(0, buf+n, sizeof(char))) {
        if (n == 1023) {
            fprintf(2, "Error: too much arguments\n");
            exit(1);
        }
        if (buf[n] == '\n') {
            break;
        }
        n++;
    }
    buf[n] = 0;
    if (n == 0) return 0;

    // move to argv
    int offset;
    offset = 0;
    while (offset < n) {
        argv[curr_argc++] = buf+offset; // start
        while (buf[offset] != ' ' && offset < n) {
            offset++;
        }
        if (offset < n) { // means buf[offset] == ' ' 
            buf[offset++] = 0;
        }
    }

    return curr_argc;
}

int main(int argc, char* argv[]) 
{
    if (argc < 2) {
        fprintf(2, "Usage: xargs command [argv...]\n");
        exit(1);
    }

    // argv[1]
    char* command = malloc(strlen(argv[1])+1);
    strcpy(command, argv[1]);
    char* new_argv[MAXARG];

    new_argv[0] = command;

    // argv[2]...
    for (int i=2; i < argc; i++) {
        new_argv[i-1] = malloc(strlen(argv[i])+1);
        strcpy(new_argv[i-1], argv[i]);
    }
    

    // fork and exec
    int curr_argc;
    while ((curr_argc = readline(new_argv, argc-1))) {
        // end of argv
        new_argv[curr_argc] = 0;
        if (fork() == 0) {
            exec(command, new_argv);
            fprintf(2, "exec fails\n");
            exit(1);
        }
        wait(0);
    }
    exit(0);
}