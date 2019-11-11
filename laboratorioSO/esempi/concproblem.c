/**
 *  Un esempio di corsa critica: entrambi i figli incrementano la
 *  variabile condivisa, controllandone i risultati finali
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    int id_shm;
    int *conto;
    int temp, versamento = 1000;

    if ((id_shm = shmget(IPC_PRIVATE, sizeof(int),
                         IPC_CREAT | IPC_EXCL | 0600)) == -1) {
        perror("shmget");
        exit(1);
    }

    conto =
        (int *)shmat(id_shm, NULL, 0); // i figli erediteranno l'area condivisa
    *conto = 0;                        // p[0]=0;

    if (fork() == 0) { // primo figlio
        for (; versamento > 0; versamento--) {
            // (*conto)++;
            temp = *conto;
            printf("P1: letto=%d\t scritto=%d\n", temp, temp + 1);
            *conto = temp + 1;
            usleep(rand() % 500);
        }
        exit(0);
    } else if (fork() == 0) { // secondo figlio
        for (; versamento > 0; versamento--) {
            // (*conto)++;
            temp = *conto;
            printf("P2: letto=%d\t scritto=%d\n", temp, temp + 1);
            *conto = temp + 1;
            usleep(rand() % 500);
        }
        exit(0);
    }

    // aspetta che finiscano entrambi i figli
    wait(NULL);
    wait(NULL);

    printf("Padre: valore finale=%d\n", *conto);

    shmctl(id_shm, IPC_RMID, NULL);
    exit(0);
}
