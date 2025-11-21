#include "../include/bash_agent.h"

#define IP "127.0.0.0"
#define PORT 8000

int open_and_connect_socket_and_send(char *log)
{
    struct sockaddr_in sock;
    struct sockaddr *so;
    int sock_fd;
    int b;
    char buffer[1024];

    sock.sin_family = AF_INET;
    sock.sin_addr.s_addr =  inet_addr(IP);
    sock.sin_port = htons(8000);

    if((sock_fd = socket(sock.sin_family,(SOCK_STREAM) ,0)) < 0)
    {
        perror("Error socket");
        return(errno);
    }
    so = (struct sockaddr *)&sock;

    if(connect(sock_fd, so, sizeof(struct sockaddr)) < 0)
    {
        perror("Error connect");
        return(errno);
    }
    printf("Connected %d\n", sock_fd);
    if(send(sock_fd, log, strlen(log), 0) < 0)
    {
        perror("send error");
        return(errno);
    }
    if((b = recv(sock_fd , buffer, 1024 - 1 , 0)) <= 0)
    {
        printf("error accuser ceception\n");

    }
    buffer[b] = '\0';
    printf("response %s\n", buffer);
    close_socket(&sock_fd);
    return(0);
}

