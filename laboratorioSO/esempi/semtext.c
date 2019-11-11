/**
 *  Crea due processi figli: uno legge da tastiera stringhe e
 *  le manda al secondo.
 *  I due processi usano memoria condivisa e semafori per comunicare.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/wait.h>
#include <unistd.h>

#define DIM_MSG 1024

// legge le stringhe da tastiera e le scrive sulla memoria condivisa
void produttore(int shm, int sem) {
    char *p;
    struct sembuf SIGNAL[1] = { { 0, +1, 0 } };

    // attacca la memoria condivisia al suo spazio di indirizzamento
    if ((p = (char *)shmat(shm, NULL, 0)) == (char *)-1) {
        perror("shmat");
        exit(1);
    }

    printf("Inserire le stringhe da copiare sulla memoria condivisa ('quit' per finire): \n");
    do {
        fgets(p, DIM_MSG, stdin); // legge una riga e la scrive direttamente sulla shm

        printf("Messaggio scritto: %s", p);

        semop(sem, SIGNAL, 1);  // invoca SIGNAL sul semaforo
    } while (strcmp(p, "quit\n") != 0);

    // NB: viene inviato anche l'ultimo messaggio con "quit"

    exit(0);
}

// legge i messaggi dalla memoria condivisa e li visualizza sullo standard output
void consumatore(int shm, int sem) {
    char *p;
    struct sembuf WAIT[1] = { { 0, -1, 0 } };

    // attacca (in sola lettura) la memoria condivisia al suo spazio di indirizzamento
    if ((p = (char *)shmat(shm, NULL, SHM_RDONLY)) == (char *)-1) {
        perror("shmat");
        exit(1);
    }

    do {
        semop(sem, WAIT, 1);                // invoca WAIT sul semaforo mettendosi in attesa
        printf("Messaggio letto: %s", p);   // legge e stampa il messaggio
    } while (strcmp(p, "quit\n") != 0);

    exit(0);
}

int main() {
    int id_shm, id_sem;

    // crea l'area di memoria condivisa
    if ((id_shm = shmget(IPC_PRIVATE, DIM_MSG, IPC_CREAT | 0600)) == -1) {
        perror("shmget");
        exit(1);
    }

    // crea il semaforo per segnalare da disponibilita' di messaggi
    if ((id_sem = semget(IPC_PRIVATE, 1, IPC_CREAT | 0600)) == -1) {
        perror("semget");
        exit(1);
    }

    // imposta il valore iniziale del semaforo ad 0
    if (semctl(id_sem, 0, SETVAL, 0) == -1) {
        perror("semctl");
        exit(1);
    }

    // crea i due processi figli: produttore e consumatore
    if (fork() != 0) {
        if (fork() != 0) {
            // corpo del padre
            wait(NULL);
            wait(NULL);
        } else {
            produttore(id_shm, id_sem);
        }
    } else {
        consumatore(id_shm, id_sem);
    }

    // distrugge memoria condivisa e semaforo
    shmctl(id_shm, IPC_RMID, NULL);
    semctl(id_sem, 0, IPC_RMID, 0);

    exit(0);
}
