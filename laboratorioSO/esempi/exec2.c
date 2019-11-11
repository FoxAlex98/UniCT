/**
 *  usa execvp per eseguire un comando il cui nome e i parametri
 *  (in numero arbitrario) sono accettati da terminale interattivamente
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define MAX_ARGS 20
#define BUFSIZE 2048

int main(int argc, char *argv[]) {
    char buffer[BUFSIZE];
    char *args[MAX_ARGS];
    int len, i=0;

    printf("comando da eseguire (senza parametri): ");
    fgets(buffer, BUFSIZE, stdin);
    len = strlen(buffer);
    if (buffer[len-1] == '\n') // elimina il carattere di 'ritorno a capo' finale
        buffer[--len] = '\0';

    args[i] = strdup(buffer);
    i++;

    do {
        printf("parametro successivo: ");
        fgets(buffer, BUFSIZE, stdin);
        len = strlen(buffer);
        if (buffer[len-1] == '\n')
            buffer[--len] = '\0';
        if (len == 0)
            break;
        args[i] = strdup(buffer);
        i++;
    } while (i < (MAX_ARGS-1));

    args[i] = NULL; // marca la fine della lista di argomenti

    execvp(args[0], args); // eseguo il comando con i parametri specificati

    printf("L'invocazione di '%s' e' fallita!\n", args[0]);
    exit(1);
}
