#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

#define PORT 8080
#define LOOPS 100

enum exit_status
{
    FAIL = -1,
    SUCCESS
} ;

int main()
{
    int sock = 0;
    struct sockaddr_in serv_addr;
    char *hello = "Ping";
    char buffer[1024] = {0};
    size_t i = 0;

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Socket creation error \n");
        return (FAIL);
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    /* Convert IPv4 and IPv6 addresses from text to binary form */
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0)
    {
        printf("\nInvalid address/ Address not supported \n");
        return (FAIL);
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("\nConnection Failed \n");

        return (FAIL);
    }

    for (i = 0; i < LOOPS; ++i)
    {
        send(sock, hello, strlen(hello), 0);
        read(sock, buffer, 1024);
        printf("%s %ld\n", buffer, i);
        sleep(1);
    }

    return (SUCCESS);
}