/**
 *  il padre crea un processo figlio e ne attende la terminazione
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid, pid2;
    int i, exitstatus;

    pid = fork();

    if (pid == 0) {
        // processo figlio
        for (i = 0; i < 10; i++) {
            sleep(rand() % 2);
            printf("Sono il FIGLIO.\n");
        }
        exit(11);
    }

    sleep(rand() % 2);

    // processo padre
    printf("Sono il processo PADRE e mi metto in attesa...\n");
    pid2 = wait(&exitstatus);
    printf("Sono il processo PADRE, il figlio [%d] è appena terminato con exit status %d e io ho terminato il mio lavoro.\n", pid2, WEXITSTATUS(exitstatus));
    exit(0);
}
