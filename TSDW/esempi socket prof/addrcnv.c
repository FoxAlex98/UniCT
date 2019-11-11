/* addrcnv.c */

#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <string.h>
 
int main(int argc, char * argv[])
{
	struct in_addr sa, sa1;
	char *p, saved_dotted[16];
	char * res;

	if (argc != 2) {
		fprintf(stderr, "Usage: %s X.Y.Z.W\n", argv[0]);
		fprintf(stderr, "\tconverte da X.Y.Z.W (dotted quad) a ");
		fprintf(stderr, "binary IP addr e indietro\n");
		exit(1);
	}
    printf("\ncalling inet_aton(\"%s\", &sa)\n", 
           argv[1]);
	if (inet_aton(argv[1], &sa) == 0) {      // inet_aton converte la 
		fprintf(stderr,"inet_aton errore\n");// stringa argv[1] nella
		exit(2);                             // struct sa
	}
    printf("calling inet_ntoa(sa)... \n"); 
	p = inet_ntoa(sa);          // inet_ntoa(sa) converte struct sa in p

	res = strcmp(argv[1],p) ?                // le stringhe di partenza,
            "diverse" : "uguali";            // argv[1] e di arrivo,
	printf("stringa di partenza e di ");     // p, devono risultare  
    printf("arrivo, p, sono %s\n", res);     // uguali (res==0)

	strcpy(saved_dotted, p);               // copia la stringa p perche'  
    printf("stringa p = %s\n\n", p);       // e` in memoria statica e 
	inet_aton("255.255.255.255", &sa1);    // una successiva ulteriore 
	printf("chiamo inet_ntoa()... ");      // chiamata alla funzione
    inet_ntoa(sa1);                        // inet_ntoa() la
    printf("stringa p sovrascritta\n");    // sovrascrivera`
	printf("ora  vale: %s\n", p);          // come si vede qui
    printf("prima era: %s\n\n", 
           saved_dotted);
	exit(0);
}
