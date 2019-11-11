/**
 *  duplica un file utilizzando 'mmap' per operare sui file
 */

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    int fdin, fdout;
    char *src, *dst;
    struct stat sb;

    if (argc < 3) {
        fprintf(stderr, "uso: %s <file-sorgente> <file-destinazione>\n",
                argv[0]);
        exit(1);
    }

    /* apre il file sorgente in lettura */
    if ((fdin = open(argv[1], O_RDONLY)) == -1) {
        perror(argv[1]);
        exit(1);
    }

    /* recupera le informazioni sul file sorgente */
    if (fstat(fdin, &sb) < 0) {
        perror(argv[1]);
        exit(1);
    }

    /* apre il file destinazione troncandolo o creandolo */
    if ((fdout = open(argv[2], O_RDWR | O_CREAT | O_TRUNC,
                      (sb.st_mode & 0777))) == -1) {
        perror(argv[2]);
        exit(1);
    }

    /* controlla se il file sorgente è vuoto: creerebbe problemi sia con lseek
     * che con mmap */
    if (sb.st_size == 0)
        exit(0);

    /* espande il file destinazione alla dimensione voluta prima di mapparlo:
     * utilizza 'ftruncate' */
    if (ftruncate(fdout, sb.st_size) == -1) {
        perror("ftruncate su destinazione");
        exit(1);
    }
    /* si poteva usare anche un 'lseek' (alla posizione 'sb.st_size -1') e un
     * 'write' per un solo byte */

    /* mappa il file sorgente */
    if ((src = (char *)mmap(NULL, sb.st_size, PROT_READ, MAP_SHARED, fdin,
                            0)) == MAP_FAILED) {
        perror("mmap su sorgente");
        exit(1);
    }

    /* mmap il file destinazione */
    if ((dst = (char *)mmap(NULL, sb.st_size, PROT_WRITE, MAP_SHARED, fdout,
                            0)) == MAP_FAILED) {
        perror("mmap su destinazione");
        exit(1);
    }

    /* copia il contenuto della sorgente sulla destinazione: usa 'memcpy' per
     * maggiore efficienza */
    memcpy(dst, src, sb.st_size);

    /* operazioni di chiusura non indispensabili... */
    munmap(src, sb.st_size);
    munmap(dst, sb.st_size);
    close(fdin);
    close(fdout);
}
