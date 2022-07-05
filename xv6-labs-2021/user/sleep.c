#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int 
main(int argc, char* argv[])
{
    int nums;
    nums = 0;

    // If the user forgets to pass an argument, 
    // sleep should print an error message.
    if (argc != 2) {
        fprintf(2, "usage: sleep nums\n");
        exit(1);
    }

    // convert command-line argument to an integer 
    nums = atoi(argv[1]);
    // Use the system call sleep.
    sleep(nums);

    // main calls exit() in order to exit your program.
    exit(0);
}