/**
 *  copia il contenuto di un file sorgente su un file di destinazione
 */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFSIZE 1024

int main(int argc, char *argv[]) {
    int sd, dd, size, result;
    char buffer[BUFSIZE];

    // controlla il numero di parametri
    if (argc != 3) {
        printf("utilizzo: %s <sorgente> <destinazione>\n", argv[0]);
        exit(1);
    }

    // apre il file sorgente in sola lettura
    if ((sd = open(argv[1], O_RDONLY)) == -1) {
        perror(argv[1]);
        exit(1);
    }

    // apre il file destinazione in sola scrittura, con troncamento e creazione
    if ((dd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0660)) == -1) {
        perror(argv[2]);
        exit(1);
    }

    // copia i dati dalla sorgente alla destinazione
    do {
        // legge fino ad un massimo di BUFSIZE byte dalla sorgente
        if ((size = read(sd, buffer, BUFSIZE)) == -1) {
            perror(argv[1]);
            exit(1);
        }
        // scrive i byte letti
        if ((result = write(dd, buffer, size)) == -1) {
            perror(argv[2]);
            exit(1);
        }
    } while (size == BUFSIZE);

    // chiude i file prima di uscire
    close(sd);
    close(dd);
}
