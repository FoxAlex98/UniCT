/*
    Homework n.6

    Scrivere un programma che crei un processo figlio con cui scambiera' dati
    tramite una coda di messaggi. Tale coda sara' creata dal padre e distrutta,
    a fine lavori, dal figlio.

    Il processo padre dovra' accettare comandi inseriti da tastiera (per semplicita'
    senza parametri) e questi dovranno essere inviati al figlio che li eseguira'
    di volta in volta creando dei processi nipoti: uno per ogni comando.

    Il tutto si dovra' arrestare correttamente all'inserimento del comando
    'exit' sul padre.

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include <sys/wait.h>

#define DIM_MSG 1024

typedef struct {
    long mtype;
    char mtext[DIM_MSG];
} msg;

/* si occupa di leggere i comandi dal prompt e di inviarli sulla coda dei messaggi */
void gestore_terminale(int coda) {
    msg comando;
    int len;

    do {
        printf("> ");
        fgets(comando.mtext, DIM_MSG, stdin);
        len = strlen(comando.mtext);
        if (comando.mtext[len-1] == '\n')
            comando.mtext[len-1] = '\0';

        comando.mtype = 1;
        if ( msgsnd(coda, &comando, strlen(comando.mtext)+1, IPC_NOWAIT) == -1 ) {
            perror("msgsnd");
            exit(1);
        }

        sleep(1);
    } while ( strcmp(comando.mtext, "exit") != 0 );

    exit(0);
}

/* si occupa di ricevere i comandi dalla coda e di eseguirli tramite dei processi figli */
void esecutore(int coda) {
    msg comando;

    while (1) {
        if ( msgrcv(coda, &comando, DIM_MSG, 0, 0) == -1 ) {
            perror("msgrcv");
            exit(1);
        }
        
        if ( strcmp(comando.mtext, "exit") == 0 )
            break;

        if ( fork() == 0 ) {
            execlp(comando.mtext, comando.mtext, NULL);
            fprintf(stderr, "Errore nell'esecuzione di '%s'\n", comando.mtext);
            exit(2);
        } else
            wait(NULL);
    }
    
    msgctl(coda, IPC_RMID, NULL);
    
    exit(0);
}

int main() {
    int ds_coda;
    key_t chiave = IPC_PRIVATE;

    if ( (ds_coda = msgget(chiave, IPC_CREAT|IPC_EXCL|0600)) == -1 ) {
        perror("msgget");
        exit(1);
    }

    if ( fork() != 0 )
        gestore_terminale(ds_coda);
    else
        esecutore(ds_coda);
}

