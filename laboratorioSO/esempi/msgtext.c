/**
 *  Il padre crea due processi figli: uno legge stringhe e le mette in coda,
 *  l'altro legge i messaggi dalla coda e li visualizza
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include <sys/wait.h>

#define DIM_MSG 1024

typedef struct {
    long	mtype;
    char	mtext[DIM_MSG];
} msg;

// legge le stringhe da tastiera e le mette in coda
void produttore(int coda) {
    msg messaggio;

    printf("Inserire le stringhe ('quit' per finire): \n");
    do {
        fgets(messaggio.mtext, DIM_MSG, stdin); // legge una riga (compresso il ritorno a capo)

        messaggio.mtype = 1;
        if (msgsnd(coda, &messaggio, strlen(messaggio.mtext) + 1, 0) == -1) {
            perror("msgsnd");
            exit(1);
        }

        printf("Messaggio inviato: %s\n", messaggio.mtext);
    } while (strcmp(messaggio.mtext, "quit\n") != 0);

    // NB: l'ultimo messaggio con 'quit' viene mandato anche per segnalare l'EOF

    exit(0);
}

// riceve i messaggi dalla coda e li visualizza sullo standard output
void consumatore(int coda) {
    msg messaggio;

    do {
        // legge un messaggio bloccandosi se non ce ne sono
        if (msgrcv(coda, &messaggio, DIM_MSG, 0, 0) == -1) {
            perror("msgrcv");
            exit(1);
        }

        printf("Messaggio ricevuto: %s\n", messaggio.mtext);
    } while (strcmp(messaggio.mtext, "quit\n") != 0);

    exit(0);
}

int main() {
    int ds_coda;

    // crea la coda
    if ((ds_coda = msgget(IPC_PRIVATE, IPC_CREAT | 0600)) == -1) {
        perror("msgget");
        exit(1);
    }

    // crea i due processi figli: produttore e consumatore
    if (fork() != 0) {
        if (fork() != 0) {
            // corpo del padre
            wait(NULL);
            wait(NULL);
        } else {
            produttore(ds_coda);
        }
    } else {
        consumatore(ds_coda);
    }

    msgctl(ds_coda, IPC_RMID, NULL);
}
