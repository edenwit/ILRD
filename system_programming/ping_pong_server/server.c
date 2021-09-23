
#include <stdio.h>      /* printf */
#include <stdlib.h>     /* EXIT_SUCCESS, EXIT_FAILURE */
#include <strings.h>    /* bzero */
#include <string.h>     /* memset, memcpy */
#include <unistd.h>     /* read, write, close */
#include <sys/select.h> /* select, fd_set */
#include <sys/socket.h> /* accept*/
#include <netinet/in.h> /* sockaddr_in */

#include "tcp_udp_utils.h"

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
    struct sockaddr_in cliaddr = {0};
    struct sockaddr_in servaddr = {0};
    struct timeval time_out = {TIMEOUT, 0};
    char buff[MAXLINE] = {'\0'};
    ssize_t response = -1;

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

    while (1)
    {
        response = -1;
        time_out.tv_sec = TIMEOUT;

        /* clear the descriptor set */
        FD_ZERO(&rset);

        /* set server_fd and udp_fd in readset */
        FD_SET(server_fd, &rset);
        FD_SET(udp_fd, &rset);
        FD_SET(stdin_fd, &rset);

        maxfdp1 = MAX2(server_fd, udp_fd) + 1;

        /* select the ready descriptor */
        if (!select(maxfdp1, &rset, NULL, NULL, &time_out))
        {
            puts("Timed Out!");
        }

        /* if tcp socket is readable then handle */
        /* it by accepting the connection */
        else if (FD_ISSET(server_fd, &rset))
        {
            len = sizeof(cliaddr);

            tcp_fd = accept(server_fd, (struct sockaddr *)&cliaddr, &len);
            /* setsockopt(tcp_fd, SOL_SOCKET, SO_RCVTIMEO, (const char *)&time_out, sizeof time_out); */

            if (0 > tcp_fd)
            {
                close(server_fd);
                close(udp_fd);
                perror("accept failed\n");
                exit(1);
            }
            while (0 != response)
            {
                bzero(buff, MAXLINE);

                response = TCPGetMessage(tcp_fd, buff);

                if (0 > response)
                {
                    perror("recv failed\n");
                    close(tcp_fd);
                    exit(1);
                }
                else
                {
                    printf("TCP client: %s\n", buff);

                    if (-1 == TCPSendMessage(tcp_fd, "pong"))
                    {
                        perror("send failed\n");
                        close(tcp_fd);
                        exit(1);
                    }
                }
            }
            puts("TCP client closed.");
            close(tcp_fd);
        }

        /* if udp socket is readable receive the message. */
        else if (FD_ISSET(udp_fd, &rset))
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
        else if (FD_ISSET(stdin_fd, &rset))
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
        }
    }

    close(server_fd);
    close(udp_fd);

    return (0);
}