#include <stdio.h>
#include <time.h>

int main() {

    clock_t inicio, fin;

    inicio = clock();

    for(int i = 0; i < 1000000; i++) {
        printf("%d\n", i);
    }

    for(int i = 0; i < 1000000; i++) {
        printf("%d\n", i);
    }

    for(int i = 0; i < 1000000; i++) {
        printf("%d\n", i);
    }

    fin = clock();

    double tiempo = (double)(fin - inicio);
    printf("Tiempo (ticks CPU): %f\n", tiempo);

    return 0;
}

