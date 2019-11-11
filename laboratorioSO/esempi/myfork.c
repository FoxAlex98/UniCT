/**
 *  il processo lanciato usa fork () per crea un processo figlio
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    pid_t pid;
    int x = 5;

    printf("PID del processo iniziale: %d\n", getpid());
    printf("inizio\n");

    /* crea un processo figlio */
    pid = fork();

    /* il codice a seguire viene eseguito da entrambi i processi: padre e figlio
     */
    if (pid == 0) {
        printf("Sono il processo FIGLIO e la fork ha ritornato %d.\n", pid);
        printf("figlio\n");
    } else {
        printf("Sono il processo PADRE e la fork ha ritornato %d.\n", pid);
        printf("padre\n");
    }
    printf("Ok, esco!\n");
}
