/* doserv.c */

/* servizio in AF_INET: converte in maiuscolo; 
 * ritardo = ASCII 1o char ricevuto - 'A';
 */
#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

extern char buffer[];   // defined in server's code

void doserv(void)
{
	int i, delay;

	// Esegue servizio maiuscole
	for (i = 0; i < strlen(buffer) ; i++)
    	buffer[i] = toupper(buffer[i]);
    // simula un ritardo 
    if ( (delay = buffer[0]-'A') < 0)    // delay 0 per A, 1 per B,...
		delay = 1000;  // very big delay
    printf("\nServer delay %d\n",delay); 
    sleep((unsigned) delay);
}
