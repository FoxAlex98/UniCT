/**
 *  usa execlp per eseguire un comando indicato sulla riga
 *  di comando (niente parametri)
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc == 1) {
        printf("utilizzo: %s comando\n", argv[0]);
        exit(1);
    }

    printf("Esegui il comando '%s'...\n", argv[1]);
    // printf("il mio pid è %d\n", getpid());
    execlp(argv[1], argv[1],
           NULL); // eseguo il comando passato come primo parametro

    // non e' necessario controllare se e' fallita...
    printf("L'invocazione di '%s' e' fallita!\n",
           argv[1]); // ... lo e' di sicuro...
    // ... visto che il flusso di esecuzione e' arrivato fin qui.
    exit(1);
}
