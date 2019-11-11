/**
 * copia un file sorgente su uno destinazione usando gli stream
 */

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    FILE *in, *out;
    int c;

    if (argc < 3) {
        printf("utilizzo: %s sorgente destinazione\n", argv[0]);
        exit(1);
    }
    // apre lo stream sorgente in sola lettura
    if ((in = fopen(argv[1], "r")) == NULL) {
        perror(argv[1]);
        exit(1);
    }

    // apre/crea lo stream destinazione in sola scrittura (con troncamento)
    if ((out = fopen(argv[2], "w")) == NULL) {
        perror(argv[2]);
        exit(1);
    }

    // copia i dati dalla sorgente alla destinazione carattere per carattere
    while ((c = fgetc(in)) != EOF)
        fputc(c, out);

    // chiude gli stream
    fclose(in);
    fclose(out);
}
