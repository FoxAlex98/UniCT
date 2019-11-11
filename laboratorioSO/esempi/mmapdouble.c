/**
 * duplica il contenuto di un file specificato, concatenandone
 * una copia del precedente contenuto
 */

/* necessario per utilizzare la funzionalita' non-POSIX mremap: */
#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    struct stat sb;
    char *p;
    int fd, size, i;

    if (argc < 2) {
        fprintf(stderr, "uso: %s <file>\n", argv[0]);
        exit(1);
    }
    if ((fd = open(argv[1], O_RDWR)) == -1) {
        perror(argv[1]);
        exit(1);
    }

    if (fstat(fd, &sb) == -1) {
        perror("fstat");
        exit(1);
    }
    if (!S_ISREG(sb.st_mode)) {
        fprintf(stderr, "%s non è un file\n", argv[1]);
        exit(1);
    }

    /* mappa il contenuto originale del file */
    size = sb.st_size;
    if ((p = (char *)mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0)) == MAP_FAILED) {
        perror("mmap");
        exit(1);
    }

    /* raddoppia la dimensione del file */
    if (ftruncate(fd, size * 2) == -1) {
        perror("ftruncate");
        exit(1);
    }
    /* estende la mappatura alla nuova dimensione */
    if ((p = (char *)mremap(p, size, size * 2, MREMAP_MAYMOVE)) == MAP_FAILED) {
        perror("mremap");
        exit(1);
    }

    /* duplica il precedene contenuto sulla seconda parte */
    for (i = 0; i < size; i++)
        p[i + size] = p[i];
    size *= 2;
    printf("File '%s' duplicato!\n", argv[1]);

    if (close(fd) == -1) {
        perror("close");
        exit(1);
    }
    if (munmap(p, size) == -1) {
        perror("munmap");
        exit(1);
    }
}
