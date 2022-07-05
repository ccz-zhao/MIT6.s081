#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char* argv[])
{
    int p1[2]; // child read, parent write
    int p2[2]; // parent read, child write

    // create a pipe
    pipe(p1);
    pipe(p2);

    char buf[] = {"X"};
    int length = sizeof(buf);

    // use fork to create a chile
    if (fork() == 0) { // child
        // close unused fd
        close(p1[1]);
        close(p2[0]);

        if (read(p1[0], buf, length) != length) {
            fprintf(2, "child reads error\n");
            exit(1);
        }

        printf("%d: received ping\n", getpid());
        
        if (write(p2[1], buf, length) != length) {
            fprintf(2, "child writes error\n");
            exit(1);
        }
        
        // release fds
        close(p1[0]);
        close(p2[1]);
        exit(0);

    } 
    else { // parent
        // close unused fd
        close(p1[0]);
        close(p2[1]);

        if (write(p1[1], buf, length) != length) {
            fprintf(2, "parent writes error\n");
            exit(1);
        }
        if (read(p2[0], buf, length) != length) {
            fprintf(2, "parent reads error\n");
            exit(1);
        }
        printf("%d: received pong\n", getpid());
        
        // wait for childs
        wait(0);
        
        // release fds
        close(p1[1]);
        close(p2[0]);
        exit(0);
    }
    exit(0);
}