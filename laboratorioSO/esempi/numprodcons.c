/**
 *  Programma che puo' istanziare tre ruoli:
 *  - un trasmettitore che genera e invia numeri di 2 tipi (A o B)
 *    attraverso una coda di messaggi;
 *  - un ricevitore di tipo A o di tipo B che estraggono dalla coda
 *    solo i messaggi del tipo corrispondente
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>

#define TYPE_A 1
#define TYPE_B 2
#define EOF_NUM -1
#define QUANTITY 4000

typedef long numtype; // trasportiamo degli interi

typedef struct {
    long mtype;
    numtype mcontent;
} msg;

void trasmittente(int ds_coda) {
    int i;
    msg messaggio;
    numtype numero;
    unsigned long sommaA, sommaB;
    char tipo;

    sommaA = sommaB = 0;
    printf("Genero %d numeri interi:\n", QUANTITY);
    for (i = 1; i <= QUANTITY; i++) {
        numero = (rand() % 300); // genera un numero a caso
        tipo =
            (rand() % 2) + TYPE_A; // genera un tipo a caso tra TYPE_A e TYPE_B
        messaggio.mcontent = numero;
        messaggio.mtype = tipo;

        // invia il messaggio (bloccandosi se la coda e' piena)
        if (msgsnd(ds_coda, &messaggio, sizeof(messaggio)-sizeof(long), 0) == -1) {
            perror("msgsnd");
            exit(1);
        }
        if (tipo == TYPE_A)
            sommaA += numero;
        else
            sommaB += numero;

        printf(
            "Messaggio n.%5d: numero=%3lu, tipo=%c, sommaA=%8lu, sommaB=%8lu\n",
            i, numero, (tipo == TYPE_A ? 'A' : 'B'), sommaA, sommaB);
        usleep(1000 + (rand() % 4000));
    }

    // invia un numero speciale EOF_NUM ad ognuno dei riceventi
    messaggio.mcontent = EOF_NUM;
    messaggio.mtype = TYPE_A;
    msgsnd(ds_coda, &messaggio, sizeof(numtype), 0);
    messaggio.mtype = TYPE_B;
    msgsnd(ds_coda, &messaggio, sizeof(numtype), 0);

    /* attendo una conferma per marcare la coda per la distruzione
     * (i dati non si perdono se i ricevitori sono gia' collegati alla coda) */
    printf("Premere un tasto per rimuovere la coda...");
    fgetc(stdin);
    msgctl(ds_coda, IPC_RMID, NULL);

    exit(0);
}

void ricevente(int ds_coda, char tipo) {
    int i;
    msg messaggio;
    unsigned long somma;

    // NB: il ricevitore non sa a priori quanti messaggi ricevera'

    i = 1;
    somma = 0;
    tipo = (tipo - 'A') + TYPE_A;
    while (1) {
        // legge un messaggio specificandone il tipo (bloccandosi se non ce ne
        // sono)
        if (msgrcv(ds_coda, &messaggio, sizeof(numtype), tipo, 0) == -1) {
            perror("msgrcv");
            exit(1);
        }

        if (messaggio.mcontent == EOF_NUM) // siamo arrivati alla fine?
            break;
        somma += messaggio.mcontent;

        printf("Messaggio n.%5d: numero=%3lu, tipo=%c, somma=%8lu\n", i,
               messaggio.mcontent, (messaggio.mtype == TYPE_A ? 'A' : 'B'),
               somma);
        i++;
    }

    exit(0);
}

int main(int argc, char *argv[]) {
    int ds_coda;
    key_t chiave = 155;

    if (argc < 2) {
        fprintf(stderr, "uso: %s T|A|B\n", argv[0]);
        exit(1);
    }

    // apre la coda (eventualmente creandola se il produttore non e' ancora
    // partito)
    if ((ds_coda = msgget(chiave, IPC_CREAT | 0600)) == -1) {
        perror("msgget");
        exit(1);
    }

    if (argv[1][0] == 'T') {
        trasmittente(ds_coda);
    } else if ((argv[1][0] == 'A') || (argv[1][0] == 'B')) {
        ricevente(ds_coda, argv[1][0]);
    } else {
        fprintf(stderr, "parametro non atteso!\n");
        exit(1);
    }
}
