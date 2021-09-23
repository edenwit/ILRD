
#include <stdio.h>      /* printf */
#include <stdlib.h>     /* EXIT_SUCCESS, EXIT_FAILURE */
#include <strings.h>    /* bzero */
#include <string.h>     /* memset, memcpy */
#include <unistd.h>     /* read, write, close */
#include <sys/select.h> /* fd_set */

#include "tcp.h"

#define PORT 5000
#define MAXLINE 1024
#define TIMEOUT 7

#define MAX2(X, Y) (((X) > (Y)) ? (X) : (Y))

int main()
{
    int server_fd = 0;
    int tcp_fd = 0;
    int udp_fd = 0;
    int stdin_fd = STDIN_FILENO;

    int maxfdp1 = 0;
    char buffer[MAXLINE];

    fd_set rset = {0};
    socklen_t len;

    struct sockaddr_in cliaddr, servaddr;
    struct timeval time_out = {TIMEOUT, 0};

    char buff[MAXLINE] = {'\0'};
    ssize_t response = 0;

    memset(&servaddr, 0, sizeof(servaddr));
    memset(&cliaddr, 0, sizeof(cliaddr));

    /* create listening TCP socket */
    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    if (-1 == server_fd)
    {
        perror("socket creation failed\n");

        return (EXIT_FAILURE);
    }

    TCPFillServerInfo(&servaddr, PORT, AF_INET, NULL);

    /* binding server addr structure to server_fd */
    if (-1 == bind(server_fd, (struct sockaddr *)&servaddr, sizeof(servaddr)))
    {
        close(server_fd);
        perror("bind failed\n");
    }

    if (-1 == listen(server_fd, 10))
    {
        close(server_fd);
        printf("Listen failed'n");

        return (EXIT_FAILURE);
    }

    /* create UDP socket */
    udp_fd = socket(AF_INET, SOCK_DGRAM, 0);

    if (-1 == udp_fd)
    {
        close(server_fd);
        perror("udp socket creation failed\n");

        return (EXIT_FAILURE);
    }

    /* binding server addr structure to udp sockfd */
    if (-1 == bind(udp_fd, (struct sockaddr *)&servaddr, sizeof(servaddr)))
    {
        close(server_fd);
        close(udp_fd);

        return (EXIT_FAILURE);
    }

    /* clear the descriptor set */
    FD_ZERO(&rset);

    /* get maxfd */

    maxfdp1 = MAX2(MAX2(server_fd, udp_fd), stdin_fd) + 1;

    while (1)
    {

        time_out.tv_sec = TIMEOUT;

        FD_ZERO(&rset);

        /* set server_fd and udp_fd in readset */
        FD_SET(server_fd, &rset);
        FD_SET(udp_fd, &rset);
        FD_SET(stdin_fd, &rset);
        /* FD_SET(tcp_fd, &rset); */

        /* select the ready descriptor */
        if (!select(maxfdp1, &rset, NULL, NULL, &time_out))
        {
            puts("Timed Out!");
        }

        /* if tcp socket is readable then handle */
        /* it by accepting the connection */

        if (FD_ISSET(server_fd, &rset))
        {
            puts("inside serverfd");
            len = sizeof(cliaddr);

            if (0 == response)
            {
                tcp_fd = accept(server_fd, (struct sockaddr *)&cliaddr, &len);
            }

            if (0 > tcp_fd)
            {
                close(server_fd);
                close(udp_fd);
                perror("accept failed\n");
                exit(1);
            }
            else if (0 < tcp_fd)
            {
                bzero(buff, MAXLINE);
                response = recv(tcp_fd, buff, sizeof(buff), 0);

                if (0 == response)
                {
                    puts("TCP client closed.");
                    close(tcp_fd);
                }
                else if (-1 == response)
                {
                    perror("recv failed\n");
                    close(tcp_fd);
                    exit(1);
                }
                else
                {
                    printf("TCP client: %s\n", buff);

                    if (-1 == send(tcp_fd, "pong", 4, 0))
                    {
                        perror("send failed\n");
                        close(tcp_fd);
                    }
                }
            }
        }
        /* if (FD_ISSET(tcp_fd, &rset)) */

        /* if udp socket is readable receive the message. */
        if (FD_ISSET(udp_fd, &rset))
        {
            len = sizeof(cliaddr);
            bzero(buffer, sizeof(buffer));
            printf("UDP client: ");
            recvfrom(udp_fd, buffer, sizeof(buffer), 0,
                     (struct sockaddr *)&cliaddr, &len);

            puts(buffer);
            if (-1 == sendto(udp_fd, "pong", sizeof(buffer), 0,
                             (struct sockaddr *)&cliaddr, sizeof(cliaddr)))
            {
                perror("sendto fail");
            }
        }
        if (FD_ISSET(stdin_fd, &rset))
        {
            bzero(buffer, sizeof(buffer));
            read(stdin_fd, buffer, sizeof(buffer));

            if (0 == strncmp(buffer, "quit\n", 5))
            {
                puts("I quit!");

                exit(0);
            }
            else if (0 == strncmp(buffer, "ping\n", 5))
            {
                puts("stdin pong!");
            }

            /*close(stdin_fd);*/
            /*close(server_fd); */
        }
    }

    return (0);
}