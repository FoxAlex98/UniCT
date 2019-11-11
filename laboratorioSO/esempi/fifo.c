/**
 *  un programma, lanciato due volte come trasmittente e ricevente,
 *  comunica tramite una pipe con nome sul file-system (FIFO);
 *
 * da invocare come:
 *  - trasmittente: fifo T
 *  - ricevente: fifo R
 *
 *  si scambiano messaggi di dimensione fissa
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
    const char *static_message = "Hello!";

    if (argc < 2) {
        fprintf(stderr, "uso: %s T|R\n", argv[0]);
        exit(1);
    }

    if (argv[1][0] == 'T') { // trasmittente
        if (mkfifo(pathname, 0700) == -1) {
            perror(pathname);
            // exit(1);
        }
        if ((fd = open(pathname, O_WRONLY)) == -1) {
            perror(pathname);
            unlink(pathname);
            exit(1);
        }

        for (i = 0; i < NUM_MSG; i++) {
            write(fd, static_message, strlen(static_message) + 1);
            printf("messaggio n.%d inviato: '%s'\n", i, static_message);
        }
        exit(0);
    } else if (argv[1][0] == 'R') { // ricevente
        if ((fd = open(pathname, O_RDONLY)) == -1) {
            perror(pathname);
            unlink(pathname);
            exit(1);
        }

        for (i = 0; i < NUM_MSG; i++) {
            len = read(fd, buffer, strlen(static_message) + 1);
            // notare la specifica dell'esatta dimensione attesa del messaggio
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
