/* byname.c */ 
/* test gethostbyname(), gethostbyaddr() */

#include <stdio.h>
#include <netdb.h>
#include <stdlib.h>

void printaddr(struct hostent *);

int main(int argc, char * argv[]) 
{
	struct hostent *hp;
   
	if (argc != 2) {
		fprintf(stderr, "Usage: %s name\n", argv[0]);
		exit(1);
	}
	// \t argv[1] is IP name: DNS lookup
	printf("\n>>>>DNS lookup for name %s\n\n", argv[1]);
	if ((hp = gethostbyname(argv[1])) == NULL) 
		{herror("Resolver query"); exit(2);}
	printaddr(hp);
	exit(0);
}