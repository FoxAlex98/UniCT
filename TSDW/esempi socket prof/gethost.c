/* gethost.c */ 
/* test gethostbyname(), gethostbyaddr() */

#include <stdio.h>
#include <ctype.h>
#include <netdb.h>
#include <stdlib.h>

void printaddr(struct hostent *);

int main(int argc, char * argv[]) 
{
	struct hostent * hp, *hq;
    
	if (argc != 2) {
	    fprintf(stderr, "Usage: %s [address|name]\n", argv[0]); 
	    exit(-1);
	}
	if (isalpha(argv[1][0])) // argv[1] is name to lookup
		printf("\n>>>>Querying DNS for name %s\n\n", argv[1]);
	else { // argv[1] is IP quad dotted address
		printf("\n>>>>Making hostent for IP addr %s ",argv[1]);
		printf("(no query for it)\n\n");
	}
    if ((hp = gethostbyname(argv[1])) == NULL) {
        fprintf(stderr, "Errore %d\n", h_errno);
        herror("Resolver");		// herror() obsolete
        exit(h_errno); 
    }
	printaddr(hp);  putchar('\n');

	if (!isdigit(argv[1][0]))	// arg is not IP addr
		exit(0);				// probably was name
	
	// arg is IP addr: reverse DNS lookup	 
	printf("\n>>>>DNS reverse lookup for hostent\n\n");
	hq = gethostbyaddr(hp->h_addr_list[0], 
	                   hp->h_length, AF_INET);
	if (hq == NULL) {
	    fprintf(stderr, "Errore %d / ", h_errno); 
		herror("Resolver");
	    exit(h_errno);
	}
	printaddr(hq);  putchar('\n');
	exit(0);
}