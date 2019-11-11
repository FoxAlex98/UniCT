/* sndrcvConnClnt.c */

/* client like the connectionless clessclnt.c; 
 * but ... uses connect() with send() and recv()
 */

#include <stdio.h>
#include <unistd.h> 
#include <stdlib.h> 
#include <string.h>
#include <sys/types.h>

#include <sys/socket.h>
#include <netdb.h> 
#include <netinet/in.h> 
#include <arpa/inet.h>

#define MAXBUF 1024
#define SERVERPORT 3002
#define SERVERNAME "localhost" 

int mkaddr(struct sockaddr_in *, const char *, u_int16_t);


int main(int argc, char * argv[])
{
	int client_socket, retcode, s_addr_len; 
	struct sockaddr_in server_addr;
	char msg[MAXBUF]; 

	// apertura del socket del client
	client_socket = socket(AF_INET, SOCK_DGRAM, 0); 
	if (client_socket == -1)
		{perror("opening client socket"); exit(-1);}

	// preparazione indirizzo del server remoto
	mkaddr(&server_addr, SERVERNAME, htons(SERVERPORT));
	
	retcode = connect(client_socket, 	     // not in sndrcvClessClnt.c
	        (struct sockaddr *) &server_addr, 
	        s_addr_len = sizeof(server_addr) ); 
	if (retcode == -1) 
		{perror("connecting socket"); exit(-1);}

////
	// invio del messaggio al server
	strcpy(msg, argc > 1 ? argv[1] : "<>");		// msg must be a string
	retcode = send( client_socket, msg, strlen(msg)+1, 0);
	if (retcode == -1) 
		{perror("sending"); exit(-1); }

	// should not overwrite server_addr here (clessclnt.c does)
//	memset(&server_addr, 0, s_addr_len);

	// riceve risposta dal server
	retcode = recv( client_socket, msg, strlen(msg)+1, 0);
	if (retcode == -1) 
		{perror("receiving"); exit(-1); }
	msg[retcode] = '\0';		// msg must be a string
	printf( "\nServer %s replies %d bytes:\n%s\n\n",
	        inet_ntoa(server_addr.sin_addr), 
	        retcode, msg );
		
	close(client_socket); 
	exit(0); 
}
