#include <arpa/inet.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

extern "C" {
int bindS(int sockfd, char *host_addr, int host_addrlen) {
  return bind(sockfd, (struct sockaddr *)&host_addr, (socklen_t)host_addrlen);
}
}