#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {

    fork();
    fork();
    fork();
    fork();

    printf("PID: %d\n", getpid());
    return 0;
}

