/* UDP Sender - Client*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(int argc, char* argv[])
{ int sockfd;
  struct sockaddr_in dest_addr;
  extern int errno;
  int i,n;
  char line[100];
  
  if(argc < 3)
  {	 printf("Use: sender IP_dest PORT_dest");
	 return 0;
  }	 
  
  if((sockfd=socket(AF_INET,SOCK_DGRAM,0)) <0)
  { printf("\nErrore nell'apertura del socket");
    return -1;
  }
  
  memset( &dest_addr, 0, sizeof(dest_addr));
  dest_addr.sin_family = AF_INET;
  dest_addr.sin_addr.s_addr = inet_addr(argv[1]);
  dest_addr.sin_port = htons(atoi(argv[2]));
  
  printf("\nInserisci un numero intero ");
  scanf("%d",&n);

  for(i=0; i<10; ++i)
  { sprintf(line,"%d",i+n);
    printf("%s",line);
    sendto(sockfd, line, strlen(line)+1, 0, &dest_addr, sizeof(dest_addr));
  }
}
