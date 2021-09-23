#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <strings.h>        /* bzero */

#include "tcp.h"

#define MAX (1024)

int TCPChatWithClient(int socket_fd, const char *message, int print_message)
{
    char buff[MAX] = {'\0'};
    ssize_t response = 0;

    bzero(buff, MAX);

    response = recv(socket_fd, buff, sizeof(buff), 0);
    if (-1 == response)
    {
        perror("recv failed\n");

        return (EXIT_FAILURE);
    }

    else if (0 == response)
    {
        puts("Tcp client closed.");
        close(socket_fd);

        return (EXIT_SUCCESS);
    }

    if (print_message)
    {
        printf("%s\n", buff);
    }

    bzero(buff, MAX);
    memcpy(buff, message, strlen(message));

    if (-1 == send(socket_fd, buff, sizeof(buff), 0))
    {
        perror("send failed\n");

        return (EXIT_FAILURE);
    }

    return (EXIT_SUCCESS);
}

int TCPChatWithServer(int socket_fd, const char *message)
{
    char buff[MAX] = {'\0'};

    memcpy(buff, message, strlen(message));

    if (-1 == send(socket_fd, buff, sizeof(buff), 0))
    {
        perror("send failed\n");

        return (EXIT_FAILURE);
    }

    bzero(buff, sizeof(buff));

    if (-1 == recv(socket_fd, buff, sizeof(buff), 0))
    {
        perror("recv failed\n");

        return (EXIT_FAILURE);
    }

    printf("Tcp server: %s\n", buff);

    return (EXIT_SUCCESS);
}

void TCPFillServerInfo(struct sockaddr_in *server, int port, int domain,
                    const char *ip_address)
{
    if (NULL == ip_address)
    {
        server->sin_addr.s_addr = htonl(INADDR_ANY);
    }
    else
    {
        inet_pton(AF_INET, ip_address, &(server->sin_addr));
    }

    server->sin_family = domain;
    server->sin_port = htons(port);

    return;
}
