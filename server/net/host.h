#pragma once
#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <netinet/in.h>

static int make_socket_non_blocking (int sfd);
static int create_and_bind (char *port);
