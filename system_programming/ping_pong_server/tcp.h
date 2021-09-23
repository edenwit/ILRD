#ifndef _RD_102_TCP_H_
#define _RD_102_TCP_H_

#include <arpa/inet.h>
#include <netinet/in.h>

int TCPChatWithClient(int socket_fd, const char *message, int print_message);
int TCPChatWithServer(int socket_fd, const char *message);
void TCPFillServerInfo(struct sockaddr_in *server, int port, int domain,
                    const char *ip_address);

#endif /* _RD_102_TCP_H_ */