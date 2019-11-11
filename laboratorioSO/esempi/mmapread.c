/**
 *  legge il contenuto di un file utilizzando il meccanismo di
 *  mappatura dei file in memoria
 */

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    struct stat sb;
    off_t i;
    char *p;
    int fd;

    if (argc < 2) {
        fprintf(stderr, "uso: %s <file>\n", argv[0]);
        exit(1);
    }
    if ((fd = open(argv[1], O_RDONLY)) == -1) {
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

    if ((p = (char*) mmap(NULL, sb.st_size, PROT_READ, MAP_SHARED, fd, 0)) == MAP_FAILED) {
        perror("mmap");
        exit(1);
    }
    if (close(fd) == -1) {
        perror("close");
        exit(1);
    }

    // printf("puntatore: %p\n", p);
    // p[4]=55; // tentativo di modificare una pagina su una mappatura in sola lettura
    
    for (i = 0; i < sb.st_size; i++)
        putchar(p[i]);

    if (munmap(p, sb.st_size) == -1) {
        perror("munmap");
        exit(1);
    }
}
