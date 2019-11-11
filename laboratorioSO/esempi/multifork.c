/**
 *  un padre che crea 2 processi figli
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    pid_t pid;
    int i;

    pid = fork();       // creo un primo figlio

    if (pid == 0) {
        // processo figlio n.1
        for (i = 0; i < 20; i++) {
            sleep(rand() % 2);
            printf("Sono il FIGLIO 1.\n");
        }
        exit(0);
    }

    pid = fork();       // creo un secondo figlio

    if (pid == 0) {
        // processo figlio n.2
        for (i = 0; i < 20; i++) {
            sleep(rand() % 2);
            printf("Sono il FIGLIO 2.\n");
        }
        exit(0);
    }

    // processo padre
    for (i = 0; i < 20; i++) {
        sleep(rand() % 2);
        printf("Sono il PADRE.\n");
    }
    exit(0);
}
