/**
 *  lista ricorsivamente il contenuto di una directory
 */

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

// funzione per listare ricordivamente una directory 'dir' a profondità 'depth'
void printdir(const char *dir, int depth) {
    DIR *dp;
    struct dirent *entry;
    struct stat statbuf;

    // apre	la directory
    if ((dp = opendir(dir)) == NULL) {
        perror(dir);
        return;
    }

    // cambia la directory corrente
    if (chdir(dir) == -1) {
        perror(dir);
        return;
    }

    // legge le varie voci
    while ((entry = readdir(dp)) != NULL) {
        // prende le informazioni sull'oggetto
        lstat(entry->d_name, &statbuf);

        if (S_ISDIR(statbuf.st_mode)) {         // controlla se e' una sottocartella
            // scarto le directory virtuali '.' e '..' altrimenti vado in loop
            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
                continue;
            printf("%*s", depth * 4, " ");      // indenta
            printf("%s/\n", entry->d_name);     // stampa il nome della sottocartella

            // chiama ricorsivamente la funzione sulla sottocartella
            printdir(entry->d_name, depth + 1);
        } else {                            // e' un file
            printf("%*s", depth * 4, " ");  // indenta
            printf("%s\n", entry->d_name);  // stampa il nome della sottocartella
        }
    }
    chdir("..");
    
    closedir(dp);
}

int main(int argc, const char *argv[]) {
    const char *topdir;

    if (argc >= 2)      // e' stato specificato almeno un parametro
        topdir = argv[1];
    else                // parte dalla cartella corrente
        topdir = ".";

    printf("Scansione della directory '%s' ...\n", topdir);
    printdir(topdir, 0);
}
