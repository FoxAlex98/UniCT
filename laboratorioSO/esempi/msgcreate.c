/**
 *  esempio base di creazione e rimozione di una coda di messaggi
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>

int main() {
    int ds_coda;
    key_t chiave = 40;  // scelgo una chiave arbitraria (sperando che sia libera...)

    printf("Creo la coda di messaggi di chiave %d... ", chiave);
    if ((ds_coda = msgget(chiave, IPC_CREAT | IPC_EXCL | 0660)) == -1) {
        perror("msgget");
        exit(1);
    }
    printf("creata (descrittore %d)\n", ds_coda);

    sleep(5);

    printf("Chiudo la coda.\n");
    msgctl(ds_coda, IPC_RMID, NULL);
}
