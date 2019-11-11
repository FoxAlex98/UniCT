/* getmsg.c */ 

/* await/display message: three waiting styles: blocking, 
 * non-blocking with max retry count, blocking with timeout
 */

#include <stdio.h>
#include <unistd.h> 
#include <stdlib.h> 
#include <sys/socket.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>

#define MAXRETRIES 10	// upper bound for non-blocking 
                        // reads in getmsg_max()
#define MAXBUF 1024

static char buf[MAXBUF];


void getmsg_blk(int sock) // ricezione bloccante di un messaggio su sock
{
	int retcode;
	
	retcode = read(sock,buf,MAXBUF);
	// NB: un singolo read() in generale non e` corretto
	if (retcode == -1) {
		printf("proc %d on read: %s\n", getpid(), 
		       strerror(errno));
		exit(-1);
	}
	printf(">>>got %d bytes\n", retcode);
	write(fileno(stdout), buf, retcode);
	printf("\n>>>end\n");
}

////
void getmsg_max(int sock)
// ricezione non bloccante ripetuta un n. max di volte
{
	int retry = 0;
	int retcode;

	fcntl(sock, F_SETFL, O_NONBLOCK);  //la read non deve essere bloccante.
	do {
		printf("N. retry = %d ", retry);
		retcode = read(sock,buf,MAXBUF);
		if (retcode == -1) {
			if (errno != EAGAIN) {
				perror("Error occurred");
				exit(1);
			} // errno was EAGAIN: retry!
			retry++;
			printf("delaying...\n");
			sleep(1); //tra un tentativo ed un altro inserisco un intervallo
		}
	} while((retcode < 0) && (retry < MAXRETRIES));
	if (retcode <= 0) {
		printf("No data read after %d retries \n", MAXRETRIES);
		exit(-1);
	}
	printf(">>>got %d bytes\n", retcode);
	write(fileno(stdout), buf, retcode);
	printf("\n>>>end\n");
}
