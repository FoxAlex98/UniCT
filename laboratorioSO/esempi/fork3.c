/**
 *  il processo padre crea una figlio che a sua volta ne crea un altro
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    pid_t pid;

    printf("PID del processo iniziale: %d\n", getpid());

    /* crea un processo figlio */
    pid = fork();

    /* il codice a seguire viene eseguito da entrambi i processi: padre e figlio
     */
    if (pid == 0) {
        printf("Sono il processo FIGLIO [%d] e mio padre ha PID %d.\n",
               getpid(), getppid());
        pid = fork();
        if (pid == 0) {
            printf("Sono il processo NIPOTE [%d] e mio padre ha PID %d.\n",
                   getpid(), getppid());
            exit(0);
        } else {
            printf("Sono il processo FIGLIO [%d] e termino.\n", getpid());
            exit(0);
        }
    } else {
        printf("Sono il processo PADRE [%d] e mio figlio ha PID %d.\n",
               getpid(), pid);
        printf("Sono sempre il padre e mio padre è %d.\n", getppid());
        exit(0);
    }
}
