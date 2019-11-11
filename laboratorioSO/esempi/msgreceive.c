/**
 *  invio e ricezione di un messaggio su una coda dallo stesso processo
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
    key_t chiave = 41;
    msg messaggio;

    if ((ds_coda = msgget(chiave, IPC_CREAT | IPC_EXCL | 0660)) == -1) {
        perror("msgget");
        exit(1);
    }

    // crea ed invia il messaggio
    messaggio.mtype = 1;
    strncpy(messaggio.mtext, "Hello world!", DIM_MSG);
    if (msgsnd(ds_coda, &messaggio, strlen(messaggio.mtext) + 1, IPC_NOWAIT) ==
        -1) {
        perror("msgsnd");
        exit(1);
    }

    strncpy(messaggio.mtext, "CANCELLO IL MESSAGGIO DAL BUFFER", DIM_MSG);

    // legge esso stesso il messaggio
    if (msgrcv(ds_coda, &messaggio, sizeof(messaggio) - sizeof(long), 0, 0) ==
        -1) {
        perror("msgrcv");
        exit(1);
    } else {
        printf("Messaggio letto: '%s'\n", messaggio.mtext);
    }

    // chiudo la coda
    msgctl(ds_coda, IPC_RMID, NULL);
}
