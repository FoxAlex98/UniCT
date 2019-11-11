/**
 *  Crea un processo figlio che legge numeri da tastiera e li deposita
 *  in un'area di memoria condivisa; poi ne crea un altro che li rilegge.
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <unistd.h>

#define MAX_NUMBERS 30

/* legge numeri da tastiera mettendoli nella memoria condivisa */
void scrittore(int id) {
    int *p;
    int numero, q = 0;

    printf("\nProcesso Scrittore:\n");

    // collega la memoria condivisa con lo spazio di indirizzamento (in
    // lettura/scrittura)
    if ((p = (int *)shmat(id, NULL, 0)) == (int *)-1) {
        perror("shmat");
        exit(1);
    }
    do {
        printf("\nNumero da inserire ('0' per finire): ");
        scanf("%d", &numero);
        if (numero == 0)
            break;

        p[++q] =
            numero; // scrive nella memoria (lasciando il primo slot libero)

        printf("Numero inserito: %d\n", numero);
    } while (q < MAX_NUMBERS);

    p[0] = q; // scrive nel primo slot, la quantita' di numeri depositati

    exit(0);
}

/* prende i numeri dalla memoria condivisa e li stampa a video  */
void lettore(int id) {
    int *p;
    int i, q = 0;

    printf("\nProcesso Lettore:\n");

    // collega la memoria condivisa con lo spazio di indirizzamento (in sola
    // lettura)
    if ((p = (int *)shmat(id, NULL, SHM_RDONLY)) == (int *)-1) {
        perror("shmat");
        exit(1);
    }

    q = p[0]; // legge quanti numeri ci sono nell'area condivisa
    printf("n.%d numeri depositati: ", q);

    for (i = 1; i <= q; i++)
        printf("%d ", p[i]);
    printf("\n");

    // p[0] = -1; // tento di scrivere nel segmento: il figlio va in segfault
    //            // (guardate all'output di 'dmesg')
    // printf("ho modificato il segmento condiviso!!\n");

    exit(0);
}

int main() {
    int id_shm;

    // crea l'area di memoria condivisa
    id_shm =
        shmget(IPC_PRIVATE, sizeof(int) * (MAX_NUMBERS + 1), IPC_CREAT | 0600);
    if (id_shm == -1) {
        perror("shmget");
        exit(1);
    }

    // crea un primo processo figlio che scrive nella memoria condivisa
    if (fork() != 0)
        wait(NULL);
    else
        scrittore(id_shm);

    // dopo che il primo figlio e' uscito, il secondo legge dalla memoria
    // condivisa
    if (fork() != 0)
        wait(NULL);
    else
        lettore(id_shm);

    // distrugge l'area di memoria condivisa
    shmctl(id_shm, IPC_RMID, NULL);

    exit(0);
}
