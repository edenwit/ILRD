#include <time.h>   /* time */
#include <stdlib.h> /* rand, srand*/
#include <string.h> /* memset */
#include <netinet/in.h> /* INADDR_ANY */
#include <arpa/inet.h> /* inet_pton */

#include "tcp_udp_utils.h"

#define MAXLINE 1024

size_t GetRand(size_t from, size_t to)
{
    time_t t;

    srand((unsigned)time(&t));

    return ((rand() % (to - from) + from));
}

void SetServerAddr(struct sockaddr_in *servaddr, size_t port)
{
    memset(servaddr, 0, sizeof(*servaddr));

    /*Filling server information */
    servaddr->sin_family = AF_INET;
    servaddr->sin_port = htons(port);
    servaddr->sin_addr.s_addr = INADDR_ANY;

    return;
}

int TCPSendMessage(int socket_fd, const char *message)
{
    return (send(socket_fd, message, MAXLINE, 0));
}

int TCPGetMessage(int socket_fd, char *buffer)
{
    int num_bytes = 0;

    num_bytes = recv(socket_fd, buffer, MAXLINE, 0);

    return (num_bytes);
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