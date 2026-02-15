#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {

    pid_t pid1, pid2, pid3;
    clock_t inicio, fin;

    inicio = clock();
    pid1 = fork();

    if (pid1 == 0) {

        pid2 = fork();

        if (pid2 == 0) {

            pid3 = fork();

            if (pid3 == 0) {
                // BISNIETO
                for (int i = 0; i < 1000000; i++) {
                    printf("%d\n", i);
                }

            } else {
                // NIETO
                for (int i = 0; i < 1000000; i++) {
                    printf("%d\n", i);
                }
                wait(NULL);
            }

        } else {
            // HIJO
            for (int i = 0; i < 1000000; i++) {
                printf("%d\n", i);
            }
            wait(NULL);
        }

    } else {
        // PADRE
        wait(NULL);
        fin = clock();

        double tiempo = (double)(fin - inicio);
        printf("Tiempo (ticks CPU padre): %f\n", tiempo);
    }

    return 0;
}

