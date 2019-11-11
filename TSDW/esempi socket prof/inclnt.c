/* inclnt.c */

/* client request/reply: spedisce 1o arg al server 
 * e, se ha il 2o arg, aspetta/stampa la risposta */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>     //  serve per chiamare strerror()
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h> // attenti a man ip!

#include "getmsg.h"		// per getmsg_xxx()

#define MAXBUF 1024
#define SERVERPORT 3002
#define SERVERNAME "localhost"

void prnerrmsg(char * progname)
{
	fprintf(stderr, "Usage: %s msg [r|t|w]\n", progname);
	fprintf(stderr, "\tsends msg to server ");
	fprintf(stderr, "(msg[0]-'A'==server delay)\n");
	fprintf(stderr, "\tif 3rd arg is present, ");
	fprintf(stderr, "tries to receive reply:\n");
	fprintf(stderr, "\t\tr => retry for given times\n");
	fprintf(stderr, "\t\tt => retry until timeout expires\n");
	fprintf(stderr, "\t\tw => wait reply indefinitely\n");
}

int main(int argc, char * argv[])
////
{
	pid_t my_pid;
	int client_socket;
	int retcode; size_t msglen;
	struct sockaddr_in server_addr;
	char msg[MAXBUF];
	void prnerrmsg(char *);
	int mkaddr(struct sockaddr_in *, const char *, u_int16_t);

	if (argc != 2 && argc != 3)
		{prnerrmsg(argv[0]); exit(-1);} 
	
	printf("proc %u ready\n", my_pid = getpid());

	// apertura del socket del client
	client_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (client_socket == -1)
		{perror("creating client socket"); exit(1);}

	// preparazione indirizzo su cui connettere il socket
	mkaddr(&server_addr, SERVERNAME, htons(SERVERPORT));

	// connessione al socket del server
	if (connect( client_socket, (struct sockaddr *)&server_addr, 
		         sizeof(server_addr) ) == -1) {
		printf("proc %u on connect: %s\n", my_pid, strerror(errno));
		exit(2);
	}
	printf("proc %u connected, ", my_pid);
	
	// scrittura del messaggio sul socket
	strcpy(msg, argv[1]); 
	msglen = strlen(msg)+1;		// msg e` una stringa
	retcode = write(client_socket, msg, msglen); 
	printf("sent %d (%u request) bytes on socket %d\n", 
		   retcode, (unsigned) msglen, client_socket);

	if (argc == 3) {
 		switch (argv[2][0]) {
 		case 'r': getmsg_max(client_socket); break;
 		case 't': getmsg_tout(client_socket); break;
 		case 'w':
 		default:  getmsg_blk(client_socket);  // default means any 3rd option
 	}	}

	close(client_socket);  // chiusura connessione
	exit(0);
}
