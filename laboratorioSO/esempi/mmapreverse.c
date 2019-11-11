/**
 *  prende un file (arbitrariamente grande) e ne inverte il contenuto
 *  byte-per-byte usando la mappatura in memoria come metodo d'accesso
 */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    struct stat sb;
    int i;
    char *p;
    long fd;
    char temp;

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

    if ((p = (char *)mmap(NULL, sb.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0)) == MAP_FAILED) {
        perror("mmap");
        exit(1);
    }
    if (close(fd) == -1) {
        perror("close");
        exit(1);
    }

    for (i = 0; i < (sb.st_size / 2); i++) {
        /* scambia p[i] con p[size-i-1] */
        temp = p[sb.st_size - i - 1];
        p[sb.st_size - i - 1] = p[i];
        p[i] = temp;
    }

    printf("File '%s' invertito!\n", argv[1]);

    if (munmap(p, sb.st_size) == -1) {
        perror("munmap");
        exit(1);
    }
}
