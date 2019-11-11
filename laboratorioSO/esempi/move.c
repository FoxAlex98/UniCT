/**
 *  reimplementazione del comando 'mv':
 *  limitato al caso di file sullo stesso file-system
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "utilizzo: %s <file-esistente> <nuovo-nome-e-o-posizione>\n", argv[0]);
        exit(1);
    }

    /* crea un hard-link a partire dal file esistente */
    if (link(argv[1], argv[2]) == -1) {
        perror(argv[2]);
        exit(1);
    }

    /* rimuove il vecchio riferimento al file */
    if (unlink(argv[1]) == -1) {
        perror(argv[1]);
        exit(1);
    }

    /* il file è stato spostato e/o rinominato istantaneamente (a prescindere dalla sua dimensione) */
}
