#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

#define MAX_NUM 1000

void redirect(int k, int pd[]) {
    close(k);
    dup(pd[k]);
    close(pd[0]);
    close(pd[1]);
}

void source() { // write 2~MAX_NUM to stdout
    int i;
    for (i = 2; i < MAX_NUM; ++i) {
        write(1, &i, sizeof(i));
    }
}

void cull(int p) {
    int n;
    while (read(0, &n, sizeof(n))) {
        if (n % p != 0) {
            write(1, &n, sizeof(n));
        }
    }
}

void sink() {
    int pd[2];
    int p;
    if (read(0, &p, sizeof(p))) {
        printf("prime %d\n", p);
        pipe(pd);
        if (fork() > 0) { // parent process
            redirect(0, pd);
            sink();
        } else {
            redirect(1, pd);
            cull(p);
        }
    }
}

int main() 
{
    int pd[2];
    pipe(pd);
    if (fork() > 0) { // parent process
        redirect(0, pd); // redirect pd[0] as stdin(0)
                         // pd[0] reads from pd[1]
                         // get source() output
        sink();
    } else { // child process
        redirect(1, pd); // redirect pd[1] as stdout(1)
        source();        // now source will write to pd[1]
    }
    exit(0);
}