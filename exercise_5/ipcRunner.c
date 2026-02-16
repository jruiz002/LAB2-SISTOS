#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {

    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        /* Hijo ejecuta ipc con símbolo 'a' */
        execl("./ipc", "ipc", "5", "a", NULL);
        perror("execl a");
        exit(EXIT_FAILURE);
    } else {
        /* Padre ejecuta ipc con símbolo 'b' */
        execl("./ipc", "ipc", "7", "b", NULL);
        perror("execl b");
        exit(EXIT_FAILURE);
    }

    return 0;
}

