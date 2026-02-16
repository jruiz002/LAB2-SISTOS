#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <string.h>
#include <errno.h>

#define SHM_NAME "/ipc_shared_memory"
#define SHM_SIZE 4096

int main(int argc, char *argv[]) {

    if (argc != 3) {
        fprintf(stderr, "Uso: %s <n> <x>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int n = atoi(argv[1]);
    char x = argv[2][0];

    if (n <= 0) {
        fprintf(stderr, "n debe ser mayor que 0\n");
        exit(EXIT_FAILURE);
    }

    int shm_fd;
    int created = 0;

    /* Intentar crear memoria compartida */
    shm_fd = shm_open(SHM_NAME, O_CREAT | O_EXCL | O_RDWR, 0666);

    if (shm_fd >= 0) {
        created = 1;
        if (ftruncate(shm_fd, SHM_SIZE) == -1) {
            perror("ftruncate");
            exit(EXIT_FAILURE);
        }
        printf("%c: Created shared memory\n", x);
    } else {
        if (errno == EEXIST) {
            shm_fd = shm_open(SHM_NAME, O_RDWR, 0666);
            if (shm_fd == -1) {
                perror("shm_open existing");
                exit(EXIT_FAILURE);
            }
            printf("%c: Shared memory already exists\n", x);
        } else {
            perror("shm_open");
            exit(EXIT_FAILURE);
        }
    }

    /* Mapear memoria */
    char *ptr = mmap(NULL, SHM_SIZE, PROT_READ | PROT_WRITE,
                     MAP_SHARED, shm_fd, 0);

    if (ptr == MAP_FAILED) {
        perror("mmap");
        exit(EXIT_FAILURE);
    }

    /* Crear pipe para comunicación padre-hijo */
    int pipefd[2];
    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid > 0) {
        /* PROCESO PADRE */
        close(pipefd[0]);

        for (int i = 0; i < SHM_SIZE; i++) {
            if (i % n == 0) {
                if (write(pipefd[1], &x, 1) == -1) {
                    perror("write");
                    break;
                }
            }
        }

        close(pipefd[1]);
        wait(NULL);

        printf("%c: Shared memory has: %s\n", x, ptr);

        munmap(ptr, SHM_SIZE);
        close(shm_fd);

        if (created) {
            shm_unlink(SHM_NAME);
        }

    } else {
        /* PROCESO HIJO */
        close(pipefd[1]);

        char c;
        int index = 0;

        while (read(pipefd[0], &c, 1) > 0) {
            if (index < SHM_SIZE - 1) {
                ptr[index++] = c;
            }
        }

        ptr[index] = '\0';

        close(pipefd[0]);
        munmap(ptr, SHM_SIZE);
        close(shm_fd);
        exit(EXIT_SUCCESS);
    }

    return 0;
}

