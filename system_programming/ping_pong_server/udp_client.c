#include <stdio.h>      /* printf */
#include <unistd.h>     /* close, sleep */
#include <string.h>     /* memset, strlen*/
#include <netinet/in.h> /* AF_INET, SOCK_DGRAM, MSG_CONFIRM, MSG_WAITALL*/

#include "tcp_udp_utils.h"

#define PORT 5000
#define MAXLINE 1024

int main()
{
    int sockfd = 0;
    char buffer[MAXLINE] = {0};
    char *message = "ping";
    struct sockaddr_in servaddr = {0};
    size_t n = 0;
    socklen_t len = 0;
    size_t i = 0;
    size_t loops = GetRand(RAND_FROM, RAND_TO);

    /*Creating socket file descriptor*/
    if (0 > (sockfd = socket(AF_INET, SOCK_DGRAM, 0)))
    {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    SetServerAddr(&servaddr, PORT);

    printf("Running for %ld times.\n", loops);

    for (i = 0; i < loops; ++i)
    {
        sendto(sockfd, (const char *)message, strlen(message),
               MSG_CONFIRM, (const struct sockaddr *)&servaddr,
               sizeof(servaddr));

        n = recvfrom(sockfd, (char *)buffer, MAXLINE,
                     MSG_WAITALL, (struct sockaddr *)&servaddr,
                     &len);
        buffer[n] = '\0';

        printf("UDP server: %s\n", buffer);

        if (loops != (i + 1))
        {
            sleep(GetRand(RAND_FROM, RAND_TO));
        }
    }

    close(sockfd);

    return (0);
}
