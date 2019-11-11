/**
 *  crea un semplice file 'pippo.txt'
 */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

int main() {
    int fd;

    if ((fd = creat("pippo.txt", 0600)) == -1) {
        // alternativa: creat("pippo.txt", S_IRUSR | S_IWUSR);
        printf("Errore nella chiamata creat\n");
        exit(1);
    }

    printf("File creato con successo con descrittore di file %d.\n", fd);
}
