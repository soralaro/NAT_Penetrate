//
// Created by deepglint on 19-1-29.
//

#include "main.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <stdio.h>
#include <string>
#include <algorithm>
#include <iostream>

typedef struct sockaddr SA;
typedef struct sockaddr_in SA_IN;

typedef struct
{
    struct in_addr ip;
    int port;
}IP; //记录ip与端口

int main(int argc,char **argv)
{
    SA_IN server,addr;
    int sockfd;
    IP ip;
    IP ip2;
    char s;
    socklen_t addrlen=sizeof(SA_IN);

    sockfd=socket(AF_INET,SOCK_STREAM,0);
    if(sockfd == -1)
    {
        perror("socket");
        return -1;
    }
    bzero(&server,sizeof(SA_IN));
    server.sin_port=htons(8888);
    server.sin_family=AF_INET;
    server.sin_addr.s_addr=INADDR_ANY;
    if(bind(sockfd,(SA *)&server,sizeof(SA_IN)) == -1)
    {
        perror("bind");
        return -1;
    }
    if(listen(sockfd,20) == -1)
    {
        perror("listen");
        return -1;
    }

    while(1)
    {
        int newfd[2];

        newfd[0]=accept(sockfd,(SA *)&addr,&addrlen);
//接收两个心跳包
        recv(newfd[0],&s,sizeof(char),0);
        memcpy(&ip.ip,&addr.sin_addr,sizeof(struct in_addr));
        ip.port=addr.sin_port;
        printf("ip1:%s\t%d OK\n",inet_ntoa(ip.ip),ntohs(ip.port));

        newfd[1]=accept(sockfd,(SA *)&addr,&addrlen);
        memcpy(&ip2.ip,&addr.sin_addr,sizeof(struct in_addr));
        ip2.port=addr.sin_port;
        printf("ip2::%s\t%d OK\n",inet_ntoa(ip2.ip),ntohs(ip2.port));

        send(newfd[0],&ip2,sizeof(IP),0);
        send(newfd[1],&ip,sizeof(IP),0);

        close(newfd[0]);
        close(newfd[1]);
    }

    return 0;
}