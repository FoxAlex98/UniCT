/* byaddr.c */ 
/* test gethostbyname(), gethostbyaddr() */

#include <stdio.h>
#include <netdb.h>
#include <arpa/inet.h> 
#include <stdlib.h>

void printaddr(struct hostent *);	// displays hostent

int main(int argc, char * argv[]) 
{
	struct hostent *hp;
	struct in_addr sa;	// ha il solo member sa.s_addr (u_int32_t)

	if (argc != 2) {
		fprintf(stderr, "Usage: %s X.Y.Z.W\n", argv[0]);
		exit(1);
	}
	// \t argv[1] is IP addr: reverse DNS lookup
	printf("\n>>>>DNS reverse lookup for IP addr %s\n\n", 
	       argv[1]);
	inet_aton(argv[1], &sa);
	hp = gethostbyaddr((void *) &(sa.s_addr), 
	                   sizeof(sa) , AF_INET  );
	if (hp == NULL) {herror("Resolver query");	exit(2);}
	printaddr(hp);
	exit(0);
}
