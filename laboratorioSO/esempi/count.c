/**
 *  conteggia il numero di byte contenuti in un file specificato
 *  sulla riga di comando
 */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFSIZE 1024

int main(int argc, char *argv[]) {
    int fd, size;
    int total = 0;
    char buffer[BUFSIZE];

    if (argc < 2) {
        printf("utilizzo: %s <file>\n", argv[0]);
        exit(1);
    }

    // apre il file sorgente in sola lettura
    if ((fd = open(argv[1], O_RDONLY)) == -1) {
        perror(argv[1]);
        exit(1);
    }

    // copia tutti i dati in memoria per conteggiare la dimensione
    do {
        if ((size = read(fd, buffer, BUFSIZE)) == -1) {
            perror(argv[1]);
            exit(1);
        }
        total += size;
        printf("ho letto %d byte\n", size);
    } while (size > 0);

    printf("La dimensione totale e' di %d byte\n", total);

    close(fd);
}
