/* sndrcvClessSrvr.c */
/* Datagram socket based connectionless server */

#include <stdio.h> 
#include <unistd.h> 
#include <stdlib.h> 
#include <string.h> 
#include <ctype.h>
#include <sys/types.h> 
#include <sys/socket.h> 
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h> 
#include <signal.h>

#define MAXBUF 1024
#define SERVERPORT 3002
#define SERVERNAME "localhost"

void terminate(int); 
int terminated = 0;
int server_socket;		// global so all functions see it

int mkaddr(struct sockaddr_in *, const char *, u_int16_t);

int main(int argc, char * argv[])
{
	int retcode, i; 
	struct sockaddr_in client_addr, server_addr; 
	socklen_t c_addr_l = sizeof(client_addr);
	char buffer[MAXBUF];

	// installazione gestore SIGINT
	signal(SIGINT, terminate); 

	// apertura del socket del server 
	if ( (server_socket = socket(AF_INET, SOCK_DGRAM, 0))
	     == -1)
		{perror("opening server socket"); exit(-1);} 

	// preparazione indirizzo locale (server) per il socket
	mkaddr(&server_addr, SERVERNAME, htons(SERVERPORT));
////
	retcode = 	// NB: senza \t bind() i recvfrom del client falliscono
	bind(server_socket,
	     (struct sockaddr *) &server_addr, //NB: type cast
	     sizeof(server_addr)
	); 
	if(retcode == -1)
		{perror("binding socket"); exit(-1);}
	printf("Server ready (uscire con CTRL-C)\n");

	while (1) {
		// riceve richiesta da client
		retcode = 
		recvfrom( server_socket, buffer, MAXBUF, 0,
		          (struct sockaddr *) &client_addr, 
		          &c_addr_l ); 
		if (retcode == -1) {	// recvfrom può fallire perché
			if (terminated)		// terminate() ha chiuso la socket
				break;			// quindi si esce normalmente
			perror("receiving");// o per altre cause
			exit(-1); 
		}
		printf("\n\n%d bytes from client %s:\nReplying...\n",
		       retcode, inet_ntoa(client_addr.sin_addr)); 
		buffer[retcode] = 0;	// buffer deve essere una stringa

		// Esegue servizio maiuscole e risponde al client
		for (i = 0; i < strlen(buffer); i++)
			buffer[i] = toupper(buffer[i]);
		retcode = 
		sendto(server_socket, buffer, strlen(buffer)+1, 0, 
		       (struct sockaddr *) &client_addr, c_addr_l);
		if (retcode == -1)
			{ perror("sending"); exit(-1); }
		printf("Sent %d bytes back\n", retcode);
	}
	
	printf("\nServer terminated (by CTRL-C) \n"); 
	exit(0); 
}


void terminate(int signo)
{
	// termina facendo fallire recvfrom e terminare il main loop
	if (close(server_socket) == -1) 
		{perror("closing socket"); exit(-1); }
	terminated = 1;
}
