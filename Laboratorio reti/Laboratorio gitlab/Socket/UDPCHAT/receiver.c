/* Alessandro Maggio X81000134 */
/* Receiver */
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>

#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>

#define RECV_PORT 7561

#define RECV_PORT2 7561
#define RECV_IP2 "192.168.1.111"

int pid;

int main(){ 

	pid = fork();

	if(pid > 0){
		
		printf("Pid > 0\n");

		int sockfd;
		struct sockaddr_in recv_addr, send_addr;
		socklen_t l = sizeof(send_addr);
		char line[100];

		if((sockfd=socket(AF_INET,SOCK_DGRAM,0)) <0) { 
			printf("\nErrore nell'apertura del socket");
			return -1;
		}

		memset((char *) &recv_addr,0,sizeof(recv_addr));
		recv_addr.sin_family = AF_INET;
		recv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
		recv_addr.sin_port = htons(RECV_PORT);

		if(bind(sockfd, (struct sockaddr *) &recv_addr, sizeof(send_addr))<0){ 
			printf("\nErrore nel binding. Forse un altro server attivo.\n Errore %d \n",errno);
			return -1;
		}
		
		printf("%s\n", "Sono il processo che riceve, pronto per entrare nel listener:");
		printf("%s\n", "Sto per entrare nel for:");

		for(;;){
			printf("%s\n", "Sono nel for prima di recvfrom . . . .");	
			recvfrom(sockfd, line, 99,0, (struct sockaddr *)&send_addr,&l);
			printf("%s\n", "Hai ricevuto un new message: ");
			printf("Ricevuto: %s \n",line);
		}
	}
	else if(pid == 0){

		printf("Pid = 0\n");
	
		int sockfd2;
		struct sockaddr_in recv_addr2;
		extern int errno;
		char line2[100];
	
		if((sockfd2=socket(AF_INET,SOCK_DGRAM,0)) <0){ 
			printf("\nErrore nell'apertura del socket");
			return -1;
		}
			
		memset( &recv_addr2,0, sizeof(recv_addr2));
		recv_addr2.sin_family = AF_INET;
		recv_addr2.sin_addr.s_addr = inet_addr(RECV_IP2);
		recv_addr2.sin_port = htons(RECV_PORT2);
		
		printf("Sono il sender sto inviando a %s sulla porta %d\n", RECV_IP2, RECV_PORT2);

		sprintf(line2,"%s", "Ciao");
		sendto(sockfd2, line2, strlen(line2)+1, 0, (struct sockaddr *)&recv_addr2, sizeof(recv_addr2));
		printf("Superato il sendto .... Messaggio inviato! %s\n", line2);

	}
	else{
		printf("Errore nel fork");
		exit(1);
	}
	
	return 0;

}
