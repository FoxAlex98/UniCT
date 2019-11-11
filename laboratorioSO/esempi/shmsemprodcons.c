/**
 *  Due figli: un produttore ed un consumatori di numeri generati a
 *  random. I due processi usano una area di memoria condivisa che
 *  contiene piu' elementi e 3 semafori per coordinarsi.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

#define DIM_BUFFER 10
#define HOW_MANY 200
#define S_MUTEX 0
#define S_EMPTY 1
#define S_FULL 2

int WAIT(int sem_des, int num_semaforo) {
    struct sembuf operazioni[1] = {{num_semaforo, -1, 0}};
    return semop(sem_des, operazioni, 1);
}

int SIGNAL(int sem_des, int num_semaforo) {
    struct sembuf operazioni[1] = {{num_semaforo, +1, 0}};
    return semop(sem_des, operazioni, 1);
}

// produce numeri random e li scrive nella memoria condivisa
void produttore(int shm, int sems) {
    int *p, *in, *out;
    int i, number, len;
    long tot = 0;

    srand(time(NULL)); // randomizza il generatore di numeri pseudo-causali

    if ((p = (int *)shmat(shm, NULL, 0)) ==
        (int *)-1) { // attacca la memoria condivisia
        perror("shmat");
        exit(1);
    }

    in = p + DIM_BUFFER; // la penultima posizione conterra' l'indice
                         // dell'inizio coda
    out = p + DIM_BUFFER +
          1; // l'ultima posizione conterra' l'indice della fine della coda
    *in = 0;
    *out = 0;
    for (i = 0; i < HOW_MANY; i++) {
        number = rand() % 500;

        WAIT(sems, S_EMPTY); // diminuisce le posizioni vuote
        WAIT(sems, S_MUTEX); // entra nella sezione critica

        p[*in] = number; // scrive il numero nella coda
        *in =
            (*in + 1) % DIM_BUFFER; // sposta l'indice in avanti (ciclicamente)
        len = (*in > *out ? (*in - *out)
                          : (DIM_BUFFER -
                             (*out - *in))); // calcola in # di elementi in coda
        printf("Produttore: %d  \t(in=%d out=%d len=%d)\n", number, *in, *out,
               len);
        tot += number;

        SIGNAL(sems, S_MUTEX); // esce dalla sezione critica
        SIGNAL(sems, S_FULL);  // incrementa le posizioni piene

        usleep(rand() % 40000);
    }

    printf("Produttore: totale finale=%ld\n", tot);

    exit(0);
}

// legge i numeri dalla coda e li stampa a video
void consumatore(int shm, int sems) {
    int *p, *in, *out;
    int i, number, len;
    long tot = 0;

    if ((p = (int *)shmat(shm, NULL, 0)) ==
        (int *)-1) { // attacca la memoria condivisia
        perror("shmat");
        exit(1);
    }

    in = p + DIM_BUFFER; // la penultima posizione conterra' l'indice
                         // dell'inizio coda
    out = p + DIM_BUFFER +
          1; // l'ultima posizione conterra' l'indice della fine della coda

    for (i = 0; i < HOW_MANY; i++) {
        WAIT(sems, S_FULL);  // diminuisce le posizioni piene
        WAIT(sems, S_MUTEX); // entra nella sezione critica

        number = p[*out]; // legge il numero dalla coda
        *out =
            (*out + 1) % DIM_BUFFER; // sposta l'indice in avanti (ciclicamente)
        len =
            (*in >= *out ? (*in - *out)
                         : (DIM_BUFFER -
                            (*out - *in))); // calcola in # di elementi in coda
        printf("Consumatore: %d  \t(in=%d out=%d len=%d)\n", number, *in, *out,
               len);
        tot += number;

        SIGNAL(sems, S_MUTEX); // esce dalla sezione critica
        SIGNAL(sems, S_EMPTY); // incrementa le posizioni vuote

        usleep(rand() % 40000);
    }

    printf("Consumatore: totale finale=%ld\n", tot);

    exit(0);
}

int main() {
    int id_shm, id_sems;

    // crea l'area di memoria condivisa per i DIM_BUFFER numeri e due variabili
    // aggiuntive
    if ((id_shm = shmget(IPC_PRIVATE, (DIM_BUFFER + 2) * sizeof(int),
                         IPC_CREAT | 0600)) == -1) {
        perror("shmget");
        exit(1);
    }

    // crea i 3 semafori (S_MUTEX, S_EMPTY, S_FULL)
    if ((id_sems = semget(IPC_PRIVATE, 3, IPC_CREAT | 0600)) == -1) {
        perror("semget");
        exit(1);
    }

    // imposta i valori iniziali dei semafori
    semctl(id_sems, S_MUTEX, SETVAL, 1);
    semctl(id_sems, S_EMPTY, SETVAL, DIM_BUFFER);
    semctl(id_sems, S_FULL, SETVAL, 0);
    // semctl(id_sems, 0, SETALL, {1, DIM_BUFFER, 0});

    // crea i due processi figli: produttore e consumatore
    if (fork() != 0) {
        if (fork() != 0) {
            // corpo del padre
            wait(NULL);
            wait(NULL);
        } else {
            produttore(id_shm, id_sems);
        }
    } else {
        consumatore(id_shm, id_sems);
    }

    // distrugge memoria condivisa e semaforo
    shmctl(id_shm, IPC_RMID, NULL);
    semctl(id_sems, 0, IPC_RMID, 0);

    exit(0);
}
