/**
 *  reimplementa il comando 'cat': legge un file di testo specificato
 *  (o, altrimenti, lo standard input) e lo manda sullo standard output
 */

#include <stdio.h>
#include <stdlib.h>

#define BUFSIZE 2048

int main(int argc, char *argv[]) {
    FILE *in;
    char buffer[BUFSIZE];

    if (argc >= 2) {    // e' stato specificato almeno un parametro
        if ((in = fopen(argv[1], "r")) == NULL) {
            perror(argv[1]);
            exit(1);
        }
    } else {           // legge dallo standard input
        in = stdin;
    }

    // copia i dati dalla sorgente alla destinazione carattere per carattere
    while ((fgets(buffer, BUFSIZE, in)) != NULL)
        printf("%s", buffer);  // fputs(buffer, stdout);

    // chiude gli stream
    fclose(in);
}
