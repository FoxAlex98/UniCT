/**
 *  L'esempio del problema con i versamenti concorrenti
 *  corretto usando un semaforo.
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    int id_shm, id_sem;
    int *conto;
    int temp, versamento = 1000;
    struct sembuf WAIT[1] = {{0, -1, 0}};
    struct sembuf SIGNAL[1] = {{0, +1, 0}};

    if ((id_shm = shmget(IPC_PRIVATE, sizeof(int),
                         IPC_CREAT | IPC_EXCL | 0600)) == -1) {
        perror("shmget");
        exit(1);
    }
    conto =
        (int *)shmat(id_shm, NULL, 0); // i figli erediteranno l'area condivisa
    *conto = 0;

    if ((id_sem = semget(IPC_PRIVATE, 1, IPC_CREAT | IPC_EXCL | 0600)) == -1) {
        perror("semget");
        exit(1);
    }

    // imposta il valore iniziale del semaforo ad 1 (semaforo mutex)
    if (semctl(id_sem, 0, SETVAL, 1) == -1) {
        perror("semctl");
        exit(1);
    }

    if (fork() == 0) { // primo figlio
        for (; versamento > 0; versamento--) {
            semop(id_sem, WAIT, 1); // inizio sezione critica: WAIT
            temp = *conto;
            printf("P1: letto=%d\t scritto=%d\n", temp, temp + 1);
            *conto = temp + 1;
            semop(id_sem, SIGNAL, 1); // fine sezione critica: SIGNAL
            usleep(rand() % 500);
        }
        exit(0);
    } else if (fork() == 0) { // secondo figlio
        for (; versamento > 0; versamento--) {
            semop(id_sem, WAIT, 1); // inizio sezione critica: WAIT
            temp = *conto;
            printf("P2: letto=%d\t scritto=%d\n", temp, temp + 1);
            *conto = temp + 1;
            semop(id_sem, SIGNAL, 1); // fine sezione critica: SIGNAL
            usleep(rand() % 500);
        }
        exit(0);
    }

    // aspetta che finiscano entrambi i figli
    wait(NULL);
    wait(NULL);

    printf("Padre: valore finale=%d\n", *conto);

    shmctl(id_shm, IPC_RMID, NULL);
    semctl(id_sem, 0, IPC_RMID, 0);

    exit(0);
}
