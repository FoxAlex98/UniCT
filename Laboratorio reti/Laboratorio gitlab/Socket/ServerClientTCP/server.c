
/* Sample TCP server */

#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char**argv){

	int listenfd,connfdA,connfdB,n;
	struct sockaddr_in servaddr,cliaddr;
	socklen_t clilen;
	char mesg[1000];

	listenfd = socket(AF_INET,SOCK_STREAM,0);

	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(34000);
	bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr));

	listen(listenfd,5);
	int pid;

	for(;;){
		clilen = sizeof(cliaddr);
		connfdA = accept(listenfd, (struct sockaddr *)&cliaddr, &clilen);
		connfdB = accept(listenfd, (struct sockaddr *)&cliaddr, &clilen);

		if (fork() == 0){
			close (listenfd);
			pid = fork();
			if(pid == 0){
				for(;;){
					n = recv(connfdB, mesg, 1000, 0);	
					send(connfdA, mesg, n, 0);
				}
			}else if(pid > 0){
				for(;;){
					n = recv(connfdA, mesg, 1000, 0);	
					send(connfdB, mesg, n, 0);
				}
			}else if(pid == -1){
				printf("Errore\n");
			}
		}

		close(connfdA);
		close(connfdB);
	}
}
<!--stackedit_data:
eyJoaXN0b3J5IjpbLTExMjI1MjUwMzJdfQ==
-->