#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstdio>
#include <stdlib.h>
#include <cstring>

void try_connect(char *ip, char *port);
int try_login(char *name, char *password);
char *recv_file();
