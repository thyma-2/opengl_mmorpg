#pragma once
#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <netdb.h>
#include <unistd.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>

int make_socket_non_blocking (int sfd);
int create_and_bind (char *port);
