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

#include <signal.h>

void catchSigPipe(int);   // segnalera` se la chiusura della connessione 
                          // si e` manifestata con errore EPIPE
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

	signal(SIGPIPE,catchSigPipe);
	
	// apertura del socket del server
	if ( (server_socket = socket(AF_INET,SOCK_STREAM,0)) == -1)
		{perror("opening server socket"); exit(-1);} 

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
	retcode = listen(server_socket, 1);
	if(retcode == -1)
		{perror("error listening"); exit(-1);}
	printf("Server ready (CTRL-C quits)\n");

	// ciclo che accetta le connessioni
	client_addr_len = sizeof(client_addr);
	while ( 1 ) {
		if ((connect_socket = 		// diversa da server_socket!
	         accept(server_socket,
	                (struct sockaddr *) & client_addr, // type cast
	                &client_addr_len)) == -1) {
			perror("accepting");
			close(server_socket);
			exit(-1);
		}
		printf("\nClient@%s connects on socket %d; sends:\n",
		       inet_ntoa(client_addr.sin_addr),connect_socket);

		// cycle: process data from accepted connection
		while ((retcode = read(connect_socket, buffer, MAXBUF-1))
		       > 0) {               // leave a byte for NULL in buffer[]
			buffer[retcode] = '\0';	// buffer must be a string
			printf("%s\n...serving...\n", buffer);
			doserv();       // esegue servizio operando su buffer[], che 
			if ((nw = write(connect_socket,      // invia al cliente collegato
			                buffer,strlen(buffer)+1)) < 0) {
				perror("replying to client");  // error check incompleto
			}
			printf("written %d bytes\n", nw);
		}
		if (retcode == 0 || errno == EPIPE)	// read returned 0 or -1
			printf("Client closed connection on socket %d\n",
			       connect_socket);
		else // retcode == -1 && (errno != EPIPE)
			perror(">>reading from connection");
		close(connect_socket);// prossima connect_socket riutilizza fd
		                      // grazie a questo close()
	} // end while(1) (never gets here)
}


void catchSigPipe(int signo)
{
	printf("Caught signal %d (SIGPIPE)\n", signo);
}
