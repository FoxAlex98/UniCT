#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

#define SIZE 128
#define DEFAULTPORT 9999

void setAddr(struct sockaddr_in *server_addr, int porta);

int main(int argc, char *argv[]){
	struct sockaddr_in server_addr, client_addr;
	int sockfd, connect_sockfd, bytes_read;	
	socklen_t client_len;
	char buffer[SIZE];
	int porta = DEFAULTPORT;
	char *closemsg = "chiudi";
	
	//controlliamo gli argomenti
	if(argc>2){
		printf("la sintassi del comando è \"nomecomando [porta]\"\n");
		exit(0);
	}
	
	if(argc==2)
		porta = atoi(argv[1]);
	
	//creiamo la socket
	if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1){
		perror("apertura socket");
		exit(-1);
	}
	
	printf("socket creata con successo\n");
	
	//settiamo la server_addr
	setAddr(&server_addr, porta);
	
	//facciamo la bind della socket
	if(bind(sockfd, (struct sockaddr *) &server_addr, sizeof(server_addr)) == -1){
		perror("bind");
		exit(-1);
	}
	
	printf("bind effettuata con successo\n");
	
	//listen con valore di backlog che è identificativo
	if(listen(sockfd, 1) == -1){
		perror("listen");
		exit(-1);
	}
	
	client_len = sizeof(client_addr);	
	printf("server pronto a ricevere, premi ctrl+c per quittare\n");
	
	while(1){
		if((connect_sockfd = accept(sockfd, (struct sockaddr *) &client_addr, &client_len)) == -1){
			perror("accept");
			close(sockfd);
			exit(-1);
		}
		
		printf("\nil client %s connesso alla socket %d invia: \n", inet_ntoa(client_addr.sin_addr), connect_sockfd);
		
		while((bytes_read = read(connect_sockfd, buffer, SIZE-1)) > 0){
			buffer[bytes_read] = '\0'; //tappo
			if(strncmp(buffer,closemsg,4) == 0){
				printf("client richiede la chiusura della connessione\n");
				break;
			}
			printf("%s", buffer);
			//parte B
			write(connect_sockfd, "ricevuto\n", 9);
		}
		
		if(bytes_read == 0)
			printf("chiusa la connessione con il socket %d\n", connect_sockfd);
		else
			printf("sto leggendo\n");
			
		close(connect_sockfd);
	}
	
	
	
	
	
    printf("ciao mondo\n");
}

void setAddr(struct sockaddr_in *serveraddr, int porta){
	serveraddr->sin_family = AF_INET;
	serveraddr->sin_port = htons(porta);
	serveraddr->sin_addr.s_addr = INADDR_ANY;
}
