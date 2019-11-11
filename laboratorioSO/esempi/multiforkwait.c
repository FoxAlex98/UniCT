/**
 *  il padre crea 2 figli ma attende la terminazione solo di uno specifico di essi
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid1, pid2;
    int i;

    pid1 = fork();      // creo un primo figlio

    if (pid1 == 0) {    // processo figlio (lento)
        for (i = 0; i < 15; i++) {
            sleep(rand() % 4);
            printf("Sono il FIGLIO LENTO [%d].\n", getpid());
        }
        printf("Sono il FIGLIO LENTO [%d] e ho finito.\n", getpid());
        exit(0);
    }

    sleep(2);           // gli diamo un po' di vantaggio

    pid2 = fork();      // creo un secondo figlio

    if (pid2 == 0) {    // processo figlio (veloce)
        for (i = 0; i < 20; i++) {
            sleep(rand() % 2);
            printf("Sono il FIGLIO VELOCE [%d].\n", getpid());
        }
        printf("Sono il FIGLIO VELOCE [%d] e ho finito.\n", getpid());
        exit(0);
    }

    // processo padre
    sleep(rand() % 2);
    printf("Sono il processo PADRE e mi metto in attesa del figlio veloce [%d]...\n", pid2);
    waitpid(pid2, NULL, 0);
    printf("Sono il processo PADRE e ho terminato il mio lavoro.\n");
    exit(0);
}
