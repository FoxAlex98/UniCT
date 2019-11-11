
/* Sample TCP client */

#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char**argv){
   int sockfd,n;
   struct sockaddr_in servaddr,cliaddr;
   char sendline[1000];
   char recvline[1000];

   int pid;

   if (argc != 2){
      printf("usage:  client <IP address>\n");
      return 1;
   }

   sockfd=socket(AF_INET,SOCK_STREAM,0);

   memset(&servaddr,0,sizeof(servaddr));
   servaddr.sin_family = AF_INET;
   servaddr.sin_addr.s_addr=inet_addr(argv[1]);
   servaddr.sin_port=htons(33000);

   connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));

   while (fgets(sendline,999,stdin) != NULL){
      send(sockfd,sendline,strlen(sendline),0);
      n=recv(sockfd,recvline,999,0);
      recvline[n]=0;
      fputs(recvline,stdout);
   }
}
