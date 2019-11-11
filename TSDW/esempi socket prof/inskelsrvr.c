/* insrvr.c */


#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>   // vedi "man 7" ip, non "man ip"!
#include <string.h>


#define MAXBUF 16

#define SERVERPORT 3002
#define SERVERNAME "localhost"

char buffer[MAXBUF];   // global, so doserv() can access it
void doserv(void);     // esegue servizio elaborando dati in buffer[]
int mkaddr(struct sockaddr_in *, const char *, u_int16_t);


int main(int argc, char * argv[])
{
	int server_socket, connect_socket;
	socklen_t client_addr_len;
	int retcode, nw;
	struct sockaddr_in client_addr, server_addr;
	
	// apertura del socket del server
	server_socket = socket(AF_INET,SOCK_STREAM,0);

	// preparazione indirizzo locale (server) per il socket
	mkaddr(&server_addr, SERVERNAME, htons(SERVERPORT));
////
	// pubblicazione socket / listen
	retcode = 
	bind(server_socket,
	     (struct sockaddr *) &server_addr, //NB: type cast
	     sizeof(server_addr) );
	if(retcode == -1)
		{perror("error binding socket"); exit(-1);}
    listen(server_socket, 1);
	printf("Server ready (CTRL-C quits)\n");

	// ciclo che accetta le connessioni
	client_addr_len = sizeof(client_addr);
	while ( 1 ) {
        connect_socket = 
            accept(server_socket, (struct sockaddr *) & client_addr,
                   &client_addr_len);
		printf("\nClient@%s connects on socket %d; sends:\n",
		       inet_ntoa(client_addr.sin_addr),connect_socket);

		// cycle: process data from accepted connection
		while ((retcode = read(connect_socket, buffer, MAXBUF-1)) > 0) 
        {     // MAXBUF-1 per lasciare un byte per ASCII NULL in buffer[]
			buffer[retcode] = '\0';	// buffer conterra' cosi' una stringa
			printf("%s\n...serving...\n", buffer);
			doserv();       // esegue servizio operando su buffer[], che 
			nw = write(connect_socket, buffer, strlen(buffer)+1); 
			printf("written %d bytes\n", nw);
		}
		if (retcode == 0)	// read returned 0
			printf("Client closed connection on socket %d\n",
			       connect_socket);
		else // retcode == -1
			perror(">>reading from connection");
		close(connect_socket);// prossima connect_socket riutilizza fd
		                      // grazie a questo close()
	} // end while(1) (never gets here)
}
