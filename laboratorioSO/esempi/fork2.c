/**
 *  il padre crea un figlio ed entrambi visualizzano
 *  una serie di messaggi sul terminale
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    pid_t pid;
    int i;

    pid = fork();

    if (pid == 0) {
        // processo figlio
        for (i = 0; i < 200; i++)
            printf("Sono il FIGLIO (%d).\n", i);

        exit(0);
    }

    // processo padre
    for (i = 0; i < 200; i++)
        printf("Sono il PADRE (%d).\n", i);

    exit(0);
}
