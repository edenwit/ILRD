#include <stdio.h>      /* printf */
#include <unistd.h>     /* close, sleep */
#include <string.h>     /* memset, strlen*/
#include <netinet/in.h> /* AF_INET, SOCK_DGRAM, MSG_CONFIRM, MSG_WAITALL*/
#include <stdlib.h>     /* EXIT_SUCCESS, EXIT_FAILURE */
#include <strings.h> /* bzero */

#include "tcp_udp_utils.h"

#define PORT 5000
#define MAXLINE 1024

int main()
{
    struct sockaddr_in serv_addr = {0};
    size_t i = 0;
    size_t loops = GetRand(RAND_FROM, RAND_TO);
    char *message = "ping";
    char buffer[MAXLINE] = {0};
    int sock_fd = 0;

    if ((sock_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Socket creation error \n");
        return (EXIT_FAILURE);
    }

    SetServerAddr(&serv_addr, PORT);

    if (connect(sock_fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("\nConnection Failed \n");

        return (EXIT_FAILURE);
    }

    printf("Running for %ld times.\n", loops);

    for (i = 0; i < loops; ++i)
    {
        memcpy(buffer, message, strlen(message));

        if (-1 == TCPSendMessage(sock_fd, message))
        {
            perror("send failed\n");

            return (EXIT_FAILURE);
        }

        bzero(buffer, sizeof(buffer));

        if (-1 == TCPGetMessage(sock_fd, buffer))
        {
            perror("recv failed\n");

            return (EXIT_FAILURE);
        }

        printf("Tcp server: %s\n", buffer);

        if (loops != (i + 1))
        {
            sleep(GetRand(RAND_FROM, RAND_TO));
        }
    }

    close(sock_fd);

    return (EXIT_SUCCESS);
}
