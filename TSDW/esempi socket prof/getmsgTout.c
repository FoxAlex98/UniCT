/* getmsgTout.c */  // will be #include'd in getmsg.c

// vedere "man 2 select_tut" per tutorial su select()

#include <sys/select.h>
#include <stdio.h>
#include <sys/socket.h>

#define TOUTS 5			// timeout (seconds) for non-blocking reads
#define TOUTUS 5		// timeout (microseconds) for non-blocking reads

void getmsg_max(int);

void getmsg_tout(int sock) // attende messaggio entro timeout
{
	struct timeval tout;   //definisci e inizializza valori di timeout
	tout.tv_sec = TOUTS;
	tout.tv_usec = TOUTUS;
	
	// select permette di sapere se una socket (in gen. file descriptor)
	// sara` disponibile in lettura entro un determinato timeout

	fd_set fds;	        // set (contenitore) di descrittori di socket
	FD_ZERO(&fds); 	    // fds diviene insieme di descrittori vuoto;
	FD_SET(sock, &fds); // aggiunge al set fds la socket sock

	int ret = select(sock+1, &fds, NULL, NULL, &tout);
	// non attende eventi write/exception (NULL/NULL), 
	// in fds c'e` solo sock, il 1° arg dev'essere 1+max(fds)

	printf("select() ha visto eventi su "); 
	printf("n.%d file descriptors\n", ret);

	// select(_,fdr,fdw,fde,&tout) esce appena scade tout, ovvero accade 
	// almeno un evento sui descrittori nei set osservati fdr,fdw,fde; 
	// restituisce il n.di eventi accaduti, cancellando da fdr,fdw,fde 
	// i descrittori che non hanno avuto eventi
	switch (ret) {
	case -1: // errore
		perror("Error occurred");
		break;
	case 0:  // nessun descrittore ha avuto eventi
		printf("Timeout occurred.\n");
		break;
    default: // qui ret>0, anzi ret==1 perche' in fds c'e` solo sock
		if (FD_ISSET(sock,   // -> di certo TRUE, ma in generale si usa
		             &fds)   // FD_ISSET(x,&fds) per vedere se x e` in fds
		   )                 // (cioe` x ha avuto eventi)
		   getmsg_max(sock); // ok anche get_msg_blk(sock) che blocca,
	}                        // dato che comunque sock avra` dati, visto che
}                            // select(_,fds,...) che ha restituito 1

