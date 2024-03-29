/* Sample UDP server */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>

int main(int argc, char**argv)
{
  int sockfd, n;
  extern int errno;
  struct sockaddr_in local_addr, remote_addr;
  socklen_t len = sizeof(remote_addr);
  char mesg[1000];
   
  if(argc < 2)
  { printf("Use: server listening_PORT");
	return 0;
  }	 

  if((sockfd=socket(AF_INET,SOCK_DGRAM,0)) <0)
  { printf("\nErrore nell'apertura del socket");
    return -1;
  }

  memset(&local_addr,0,sizeof(local_addr));
  local_addr.sin_family = AF_INET;
  local_addr.sin_addr.s_addr=htonl(INADDR_ANY);
  local_addr.sin_port=htons(atoi(argv[1]));
  if(bind(sockfd, (struct sockaddr *) &local_addr, sizeof(local_addr))<0)
  { printf("\nErrore nel binding. Errore %d \n",errno);
    return -1;
  }

  for (;;)
  { n = recvfrom(sockfd,mesg,1000,0,(struct sockaddr *)&remote_addr,&len);
    mesg[n] = 0;
	printf("From IP:%s Port:%d msg:%s \n", inet_ntoa(remote_addr.sin_addr),  ntohs(remote_addr.sin_port), mesg);
	sendto(sockfd,mesg,n,0,(struct sockaddr *)&remote_addr,len);
  }
}
