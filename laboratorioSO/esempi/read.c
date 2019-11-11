/**
 *  legge i primi 10 byte del file 'pippo.txt'
 */

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define DIM_BUFFER 1024

int main() {
    int fd, n;
    const char *name = "pippo.txt";
    char buffer[DIM_BUFFER];

    if ((fd = open(name, O_RDONLY)) == -1) {
        perror(name);
        exit(1);
    }

    if ((n = read(fd, buffer, DIM_BUFFER - 1)) == -1) {
        perror(name);
        exit(1);
    }
    buffer[n] = '\0'; // buffer[n] = 0;

    printf("ho letto: %s \n", buffer);

    close(fd);
}
