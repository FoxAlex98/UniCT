/*
    Homework n.1

    Scrivere un programma in linguaggio C che permetta di copiare un numero
    arbitrario di file regolari su una directory di destinazione preesistente.

    Il programma dovra' accettare una sintassi del tipo:
     $ homework-1 file1.txt path/file2.txt "nome con spazi.pdf" directory-destinazione
*/

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

#define BUFSIZE 4096
#define MODE 0660

int main(int argc, char *argv[]) {
    int sd, dd, size, i;
    char buffer[BUFSIZE];
    char *p1, *p2;

    // controlla di avere almeno 2 parametri effettivi
    if (argc < 3) {
        printf("utilizzo: %s [<sorgente>...] <directory destinazione>\n", argv[0]);
        exit(1);
    }

    for (i = 1; i < argc-1; i++) {
        // apre il file sorgente di turno in sola lettura
        printf("%s\t--> ", argv[i]);
        if ((sd = open(argv[i], O_RDONLY)) == -1) {
            perror(argv[i]);
            exit(1);
        }

        /* prepara in 'buffer' il nome del file di destinazione:
           <directory destinazione>/<sorgente>                    */
        strncpy(buffer, argv[argc-1], BUFSIZE);
        size = strlen(buffer);
        strncpy(buffer + size, "/", BUFSIZE - size);
        size++;

        /* isola nel pathname sorgente la parte finale del filename;
           in alternativa si poteva usare basename()                */
        p1 = p2 = argv[i];
        while (*p2 != '\0') {
            if (*p2 == '/') p1 = p2+1;
            p2++;
        }
        strncpy(buffer + size, p1, BUFSIZE - size);

        // apre il file destinazione in sola scrittura, con troncamento e creazione
        printf("%s\n", buffer);
        if ((dd = open(buffer, O_WRONLY|O_CREAT|O_TRUNC, MODE)) == -1) {
            perror(buffer);
            exit(1);
        }

        // copia i dati dalla sorgente alla destinazione
        do {
            // legge fino ad un massimo di BUFSIZE byte dalla sorgente
            if ((size = read(sd, buffer, BUFSIZE)) == -1) {
                perror(argv[1]);
                exit(1);
            }
            // scrive i byte letti
            if (write(dd, buffer, size) == -1) {
                perror(argv[2]);
                exit(1);
            }
        } while (size == BUFSIZE);

        // chiude i file attualmente aperti
        close(sd);
        close(dd);
    }
}
