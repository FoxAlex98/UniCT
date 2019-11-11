/* Effettua la manipolazione dei canali standard output ed error */

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define STDIN 0
#define STDOUT 1
#define STDERR 2

#define DEVNULL "file.log"

int main() {
    int fd;

    printf("messaggio n.1 sullo standard output\n");
    perror("errore n.1 simulato");

    if ((fd = open(DEVNULL, O_WRONLY | O_CREAT | O_TRUNC, 0600)) == -1) {
        perror(DEVNULL);
        exit(1);
    }
    close(STDOUT);
    dup(fd);
    printf("messaggio n.2 sullo standard output\n");
    perror("errore n.2 simulato");

    close(STDERR);
    dup(fd);
    printf("messaggio n.3 sullo standard output\n");
    perror("errore n.3 simulato");
}
