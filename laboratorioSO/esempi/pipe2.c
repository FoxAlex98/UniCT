/**
 *  il padre ed il figlio ricreano l'invocazione "seq 50 | sort -R"
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main(int argc, char *argv[]) {
    int pipefd[2];

    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(1);
    }

    if (fork() == 0) {      // figlio
        close(1);           // chiude lo standard output
        dup(pipefd[1]);     // copia il canale di scrittura della pipe sullo standard output
        close(pipefd[0]);   // chiudiamo per sicurezza il canale della pipe che non usiamo
        execlp("seq", "seq", "50", NULL);
        perror("execlp");
        exit(1);
    } else {                                // padre
        close(0);                           // chiude lo standard input
        dup(pipefd[0]);                     // copia il canale di lettura della pipe sullo standard input
        close(pipefd[1]);                   // come sopra, qui creebbe problemi... non fa pervenire l'EOF al lettore (se stesso): provate a disabilitarlo!
        execlp("sort", "sort", "-R", NULL); // sort aspetta l'EOF prima di elaborare
        //execlp("grep", "grep", "1", NULL);    // in alternativa al sort precedente: grep elabora riga-per-riga ma aspetta comunque l'EOF finale
        perror("execlp");
        exit(1);
    }
}
