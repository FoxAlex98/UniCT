/**
 *  prova di invio di un messaggi in una coda (senza ricezione)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define DIM_MSG 1024

typedef struct {
    long mtype;
    char mtext[DIM_MSG];
} msg;

int main() {
    int ds_coda;
    key_t chiave = 40;
    msg messaggio;

    // crea la coda
    if ((ds_coda = msgget(chiave, IPC_CREAT | IPC_EXCL | 0660)) == -1) {
        perror("msgget");
        exit(1);
    }

    // crea ed inserisce il messaggio
    messaggio.mtype = 1;
    strncpy(messaggio.mtext, "Hello world!", DIM_MSG);
    // if (msgsnd(ds_coda, &messaggio, sizeof(messaggio)-sizeof(long),
    // IPC_NOWAIT) == -1 ) {
    if (msgsnd(ds_coda, &messaggio, strlen(messaggio.mtext) + 1, IPC_NOWAIT) ==
        -1) {
        printf("Errore durante l'inserimento del messaggio.\n");
        exit(1);
    }

    msgctl(ds_coda, IPC_RMID, NULL);
}
