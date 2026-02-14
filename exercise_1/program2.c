#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {

    for(int i = 0; i < 4; i++) {
        fork();
    }

    printf("Proceso final -> PID: %d, PPID: %d\n", getpid(), getppid());
    return 0;
}


