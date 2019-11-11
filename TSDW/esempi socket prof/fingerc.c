	/* fingerc.c */

#include <stdio.h>
#include <unistd.h> 
#include <stdlib.h> 
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>

#define MAXHN 128 
#define MAXBUF 8*1024       // provare a variare
#define IPPORT_FINGER 79    // definito anche in netinet/in.h

int main(int argc, char * argv[])
{
    char buffer[MAXBUF];     // message buffer
    struct sockaddr_in addr; // server socket's address
    u_int16_t fport;
    int s, retcode;
    
    int mkaddr(struct sockaddr_in * skaddr, char * ipaddr, u_int16_t port);
    /* mkaddr pone in *skaddr l'indirizzo IP dato dalla coppia
     * ipaddr (una stringa, tipo "151.97.352.37") e port (p.es 79)
     * ipaddr può anche essere un nome tipo "directory.mit.edu"       */

    // analisi riga di comando
    if(argc != 3 && argc != 4) {
        fprintf(stderr, "usage: %s server_host message [port]\n\
                         e.g.:  %s directory.mit.edu smith", argv[0]);
        exit(1);
    }
    // Creazione socket
    if ((s = socket(AF_INET, SOCK_STREAM, 0)) == -1) 
        {perror("opening socket"); exit(-1);}     

    // collegamento al server host
    fport = // analisi del port
        argc==4 ? htons((uint16_t) atoi(argv[3]))
                : htons(IPPORT_FINGER);	

    mkaddr(&addr, argv[1], fport);  // costruisce l'indirizzo del server 

    if (connect(s, (struct sockaddr *) &addr, sizeof(addr))  
        == -1 ) {
            fprintf(stderr,"errno=%d\n", errno);
            perror("mentre mi connetto"); 
            exit(-2);
    }

    sprintf(buffer,"%s\n", argv[2]);  // buffer conterra` di certo una stringa
    if (write(s, buffer, strlen(buffer)) == -1)   // invia messaggio al server
        {perror("writing to socket"); exit(-3);}

    // Il seguente read(s,...) singolo e' errato (anche per grandi MAXBUF)
    // read non e` atomica rispetto a write all'altro endpoint (v. lucidi)! 

//  retcode = read(s, buffer, MAXBUF-1); 
//  printf("%d B read\n%s\n", retcode, buffer);

    // la soluzione corretta per icevere datu è il seguente 
    // while con read(s,...) ripetuti

    while ((retcode = read(s, buffer,  // lascia un byte alla fine di
            MAXBUF-1)) != 0) {         // buffer, per eventuale ASCII 0
        if (retcode == -1) 
            {perror("reading from socket"); exit(-4); }
        printf("\n----Read %d bytes----\n", retcode);
        buffer[retcode] = '\0';  // ASCII 0 oltre l'ultimo byte ricevuto
        printf("%s\n", buffer);
    }

    printf("\n>>>Exiting: server closed connection\n");

    close(s);  exit(0); 
}
