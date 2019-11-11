/**
 *  un abbozzo di funzionamento di una mini-shell (niente parametri)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#define LEN_BUFFER 1024

int main(int argc, char *argv[]) {
    char comando[LEN_BUFFER];
    int pid, len;

    while (1) {
        printf("Digitare un comando da eseguire ('quit' per uscire): ");
        fgets(comando, LEN_BUFFER, stdin);
        len = strlen(comando);
        if (comando[len - 1] == '\n')
            comando[len - 1] = '\0';

        if (strcmp(comando, "quit") == 0)
            break;

        pid = fork();

        if (pid == -1) {
            perror("fork");
            exit(1);
        }
        if (pid == 0) {
            execlp(comando, comando, NULL);
            fprintf(stderr, "Errore nell'esecuzione di '%s'\n", comando);
            exit(2);
        } else {
            wait(NULL);
        }
    }
    exit(0);
}
