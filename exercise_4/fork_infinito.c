#include <stdio.h>
#include <unistd.h>

int main() {

    pid_t pid = fork();

    if (pid == 0) {
        // HIJO
        for (int i = 1; i <= 4000000; i++) {
            printf("%d\n", i);
        }
    } else {
        // PADRE
        while (1) {
        }
    }

    return 0;
}

