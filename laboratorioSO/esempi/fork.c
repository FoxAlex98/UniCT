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

    /* crea un processo figlio */
    pid = fork();

    /* il codice a seguire viene eseguito da entrambi i processi: padre e figlio
     */
    if (pid == 0) {
        printf("Sono il processo FIGLIO e la fork ha ritornato %d.\n", pid);
        // sleep(1);
        printf("Sono il processo FIGLIO [%d] e mio padre ha PID %d.\n",
               getpid(), getppid());
        printf("Sono il processo FIGLIO e la mia variabile x vale %d.\n", x);
    } else {
        printf("Sono il processo PADRE e la fork ha ritornato %d.\n", pid);
        // sleep(1);
        printf("Sono il processo PADRE [%d] e mio figlio ha PID %d.\n",
               getpid(), pid);
        x++;
        printf("Sono il processo PADRE e la mia variabile x vale %d.\n", x);
        printf("Sono sempre il padre e mio padre è %d.\n", getppid());
    }
    printf("Ok, esco!\n");
}
