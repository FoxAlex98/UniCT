/**
 *  un programma, lanciato due volte come trasmittente e ricevente,
 *  comunica tramite una pipe con nome sul file-system (FIFO);
 *  da invocare come:
 *   - trasmittente: fifo T
 *   - ricevente: fifo R
 *
 *    tentano di scambiarsi messaggi di dimensione variabile
 *    (dimostrando i limiti delle pipe/fifo)
 */

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define BUFSIZE 1024
#define NUM_MSG 20

int main(int argc, char *argv[]) {
    int i, fd, len;
    char buffer[BUFSIZE];
    const char *pathname = "/tmp/fifo";

    if (argc < 2) {
        fprintf(stderr, "uso: %s T|R\n", argv[0]);
        exit(1);
    }

    if (argv[1][0] == 'T') { // trasmittente
        if (mkfifo(pathname, 0777) == -1) {
            perror(pathname);
            exit(1);
        }
        if ((fd = open(pathname, O_WRONLY)) == -1) {
            perror(pathname);
            unlink(pathname);
            exit(1);
        }

        for (i = 0; i < NUM_MSG; i++) {
            snprintf(buffer, BUFSIZE, "msg-%d: Hello!", i);
            write(fd, buffer, strlen(buffer) + 1);

            sleep(1); // senza questa pausa ci sono dei problemi: perche'?

            printf("messaggio n.%d inviato: '%s'\n", i, buffer);
        }
        exit(0);
    } else if (argv[1][0] == 'R') { // ricevente
        if ((fd = open(pathname, O_RDONLY)) == -1) {
            perror(pathname);
            unlink(pathname);
            exit(1);
        }

        for (i = 0; i < NUM_MSG; i++) {
            buffer[0] = '\0'; // azzero la stringa residua del buffer
            len = read(fd, buffer, BUFSIZE);
            // qui non specifico la dimensione del messaggio ma la capienza del
            // buffer

            printf("messaggio ricevuto (%d byte): %s\n", len, buffer);
        }
        unlink(pathname);
        exit(0);
    } else {
        fprintf(stderr, "parametro non atteso!\n");
        unlink(pathname);
        exit(1);
    }
}
