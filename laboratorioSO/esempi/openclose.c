/**
 *  apre e chiude un file
 */

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    int fd;
    const char *name = "pippo.txt";
    // const char *name = "/etc/passwd";

    if ((fd = open(name, O_RDWR)) == -1) {
        perror(name);
        exit(1);
    }

    printf("Il file %s e' stato aperto con descrittore di file %d.\n", name,
           fd);

    if (close(fd) == -1) {
        perror(name);
        exit(1);
    }
}
