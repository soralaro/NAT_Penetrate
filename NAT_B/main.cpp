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

#define SER "45.62.126.40"
#define PORT 8888

typedef struct
{
    struct in_addr ip;
    int port;
}IP; //ip与端口

typedef struct sockaddr SA;
typedef struct sockaddr_in SA_IN;

void echo_cli(int sockfd)
{
    char buf[1024];

    while(1)
    {
        bzero(buf,sizeof(buf));
        printf(">");
        fflush(stdout);
        fgets(buf,sizeof(buf)-1,stdin);
        send(sockfd,buf,strlen(buf),0);

        bzero(buf,sizeof(buf));
        recv(sockfd,buf,sizeof(buf)-1,0);
        printf("%s",buf);
        buf[strlen(buf)-1]='\0';
        if(strcmp(buf,"exit") == 0)
            break;
    }
}

int main(int argc,char **argv)
{
    int sockfd,sockfd2;
    SA_IN server,addr;
    IP ip;
    socklen_t addrlen=sizeof(SA_IN);

    sockfd=socket(AF_INET,SOCK_STREAM,0);

    bzero(&server,sizeof(SA_IN));
    server.sin_family=AF_INET;
    server.sin_addr.s_addr=inet_addr(SER);
    server.sin_port=htons(PORT);

    struct sockaddr_in client_addr;
    client_addr.sin_family = AF_INET;
    client_addr.sin_addr.s_addr = htons(INADDR_ANY);
    client_addr.sin_port = htons(20011);    //指定端口
    //把客户机的socket和客户机的socket地址结构联系起来
    if( bind(sockfd,(struct sockaddr*)&client_addr,sizeof(client_addr))){
        printf("Client Bind Port Failed!\n");
        exit(1);
    }

    connect(sockfd,(SA *)&server,sizeof(SA_IN));
    recv(sockfd,&ip,sizeof(IP),0);
    printf("%s\t%d OK\n",inet_ntoa(ip.ip),ntohs(ip.port));
    close(sockfd);

    sockfd2=socket(AF_INET,SOCK_STREAM,0);
    server.sin_addr=ip.ip;
    server.sin_port=ip.port;
    while(connect(sockfd2,(SA *)&server,sizeof(SA_IN)) == -1)
        perror("connect");
    printf("connect A suc\n");
    echo_cli(sockfd2);

    close(sockfd2);
    return 0;
}
