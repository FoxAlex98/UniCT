/**
 *  raccoglie e visualizza tutta una serie di informazioni su
 *  un file specificato sulla riga di comando
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

int main(int argc, char *argv[]) {
    struct stat statbuf;
    struct passwd *pw;
    struct group *gr;
    const char *username, *groupname;
    const char *type;
    mode_t modes;

    if (argc < 2) {
        fprintf(stderr, "utilizzo: %s <pathname>\n",argv[0]);
        exit(1);
    }

    // raccoglie le informazioni sul file/directory
    if (lstat(argv[1], &statbuf) == -1) {
        perror(argv[1]);
        exit(1);
    }

    // prende il nome del proprietario
    if ((pw = getpwuid(statbuf.st_uid)) == NULL)
        username = "????";
    else
        username = pw->pw_name;

    // prende il nome del gruppo
    if ((gr = getgrgid(statbuf.st_gid)) == NULL)
        groupname = "????";
    else
        groupname = gr->gr_name;

    // determina il tipo dell'oggetto su file-system
    modes = statbuf.st_mode;
    if ((modes & S_IFMT) == S_IFDIR) // if (S_ISDIR(modes)
        type = "directory";
    else if (((modes & S_IFMT) == S_IFBLK) || ((modes & S_IFMT) == S_IFCHR))
        type = "file speciale di dispositivo";
    else if ((modes & S_IFMT) == S_IFREG)
        type = "file regolare";
    else if ((modes & S_IFMT) == S_IFLNK)
        type = "link simbolico";
    else if ((modes & S_IFMT) == S_IFIFO)
        type = "file FIFO";
    else
        type = "--indefinito (!?!)--";

    // stampa alcune informazioni
    printf("filename: %s\n", argv[1]);
    printf("permissions: %o\n", modes & 0777);
    printf("type: %s\n", type);
    printf("i-number: %d\n", (int)statbuf.st_ino);
    printf("uid: %d (%s) gid: %d (%s)\n", statbuf.st_uid, username, statbuf.st_gid, groupname);
    printf("atime: %s", asctime(localtime(&(statbuf.st_atime))));
    printf("mtime: %s", asctime(localtime(&(statbuf.st_mtime))));
    printf("ctime: %s", asctime(localtime(&(statbuf.st_ctime))));
}
