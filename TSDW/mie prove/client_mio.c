//da completare

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netinet/in.h>
#include <errno.h>

#define DEFAULT_ADDR "127.0.0.1"
#define DEFAULT_PORT "9999"

void setAddr(struct sockaddr_in *server_addr);


int main(int argc, char *argv[]){
    int sockfd;
    struct sockaddr_in server_addr;

    if(argc > 1){
        printf("please stop");
        exit(0);
    }

    if((sockfd = socket(AF_INET,SOCK_STREAM,0)) == -1){
            perror("socket");
            exit(-1);
    }

    setAddr(&server_addr);

    if(connect() == -1){
        perror("connect");
        exit(-1);
    }
}

void setAddr(struct sockaddr_in *server_addr){
    server_addr->sin_family = AF_INET;
    server_addr->sin_port = htons((uint32_t) atoi(DEFAULT_PORT));
    server_addr->sin_addr.s_addr = inet_addr(DEFAULT_ADDR);
}
