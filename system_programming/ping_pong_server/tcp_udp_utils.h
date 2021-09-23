#ifndef _RD_102_UTILS_H_
#define _RD_102_UTILS_H_

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define RAND_FROM 3
#define RAND_TO 10

size_t GetRand(size_t from, size_t to);
void SetServerAddr(struct sockaddr_in *servaddr, size_t port);
int TCPSendMessage(int socket_fd, const char *message);
int TCPGetMessage(int socket_fd, char *buffer);
void TCPFillServerInfo(struct sockaddr_in *server, int port, int domain,
                    const char *ip_address);
                    
#endif /* _RD_102_UTILS_H_ */