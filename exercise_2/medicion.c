#include <stdio.h>
#include <time.h>

int main() {
    clock_t inicio, fin;

    inicio = clock();

    for(int i = 0; i < 1000000; i++) {
    }

    for(int i = 0; i < 1000000; i++) {
    }

    for(int i = 0; i < 1000000; i++) {
    }

    fin = clock();

    double tiempo = (double)(fin - inicio);

    printf("%f\n", tiempo);

    return 0;
}

