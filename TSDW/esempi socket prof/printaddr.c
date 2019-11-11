/* printaddr.c */

/* Displays an IP struct hostent (see man gethostbyname) */

#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>

void printaddr(struct hostent * hp)
{
	char * *p, *ap;
	uint32_t addr;
	int al, n;

    printf(    "  Official name:   %s\n", hp->h_name);
    for (p = hp->h_aliases; *p != NULL; p++) {
        printf("  Alias:           %s\n", *p);
    }
    
    al = hp->h_length;

    for (p = hp->h_addr_list; (ap = *p) != NULL; p++) {
        printf("  Displaying IP addresses\n");
        printf("\t     byte by byte: ");
    	for (n = al; n > 0; n--)
        	printf("%u.", (unsigned char) *ap++);

        addr = * ( (uint32_t *) * p);
        printf( "\n\t\t    32bit: (net) %x / (host, via ntohl) %x\n", 
               addr, ntohl(addr) );
        
        printf(  "    32bit div 256 (0x100): ");
        for (n = al; n > 0; n--) {
            printf("%u%c", addr % 0x100, n == 1 ? '\n' : '.');
            addr /= 0x100;
        }
    }
}
