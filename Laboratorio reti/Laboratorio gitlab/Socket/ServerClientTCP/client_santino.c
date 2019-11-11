#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>

#define MAX  1000

int main(int argc, char **argv){
	int sock_fd, i, pid;
	struct sockaddr_in serv_add;
	char sendline[MAX];
	char recvline[MAX];

	/* create socket */
	if((sock_fd = socket(AF_INET,SOCK_STREAM,0)) < 0){
		perror("Errore nella creazione socket");
		return 1;
	}

	/* inizzializzazione Indirizzo */ 

	memset((void *) &serv_add,0,sizeof(serv_add));
	serv_add.sin_family = AF_INET;
	serv_add.sin_port = htons(34000);
	serv_add.sin_addr.s_addr=inet_addr(argv[1]);
	
	/* Stabiliamo la connessione */
	if(connect(sock_fd,(struct sockaddr*)&serv_add, sizeof(serv_add)) < 0){
		perror("Errore nella connessione");
		return 1;
	}


	for(;;){
		pid = fork();
		if(pid == 0){
			fgets(sendline,MAX-1,stdin);
			send(sock_fd,sendline,strlen(sendline),0);
		}else if(pid > 0){
			i = recv(sock_fd,recvline,MAX-1,0);
			recvline[i] = 0;
			fputs(recvline,stdout);
			//printf("\nPid = %d: received from port %d the following:\n",getpid(),ntohs(cliaddr.sin_port));
		}else if(pid < 0){
			printf("Error\n");
			return;
		}
	}
}