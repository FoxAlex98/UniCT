/**
 *  crea una pipe di comunicazione tra un padre ed il figlio:
 *  questi poi la usano per una forma di "conversazione bidirezionale"
 *  un po' atipica: e' infatti sconsigliato usare la stessa pipe
 *  in entrambi i versi
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#define BUFSIZE 1024

int main(int argc, char *argv[]) {
    int pipefd[2];
    char buffer[BUFSIZE];

    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(1);
    }

    if (fork() == 0) { // figlio
        if (read(pipefd[0], buffer, BUFSIZE) == -1) {
            perror("pipe");
            exit(1);
        }
        printf("Figlio - messaggio ricevuto: '%s'\n", buffer);

        strncpy(buffer, "Crepi il lupo!!!", BUFSIZE);
        printf("Figlio - messaggio inviato: '%s'\n", buffer);
        if (write(pipefd[1], buffer, strlen(buffer) + 1) == -1) {
            perror("pipe");
            exit(1);
        }

        exit(0);
    } else { // padre
        strncpy(buffer, "In bocca al lupo!", BUFSIZE);
        printf("Padre - messaggio inviato: '%s'\n", buffer);
        if (write(pipefd[1], buffer, strlen(buffer) + 1) == -1) {
            perror("pipe");
            exit(1);
        }

        sleep(1); // aspetta un po', altrimenti il padre  rileggerebbe il
                  // proprio messaggio

        if (read(pipefd[0], buffer, BUFSIZE) == -1) {
            perror("pipe");
            exit(1);
        }
        printf("Padre - messaggio ricevuto: '%s'\n", buffer);

        wait(NULL); // in realta' il figlio avra' gia' finito e questa non
                    // diventa bloccante
        exit(0);
    }
}
