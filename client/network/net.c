#include "net.h"

int netfd;
char order[9999] = {0};

void try_connect(char *ip, char *port) // Connecter
{
    netfd = socket(AF_INET, SOCK_STREAM, 0);
    //specify an address for the socket
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(atoi(port));
    server_address.sin_addr.s_addr = inet_addr(ip); 
    if (connect(netfd, (struct sockaddr *) &server_address, sizeof(server_address)) != 0)
    	netfd = -1;
}

int try_login(char *name, char *password)
{
	char rep = 'p';
	char to_send[101] = {0};
	sprintf(to_send, "%s %s", name, password);
	send(netfd, to_send, 101, 0);
	while (rep == 'p')
		recv(netfd, &rep, 1,0);
	if (rep == 'n')
		return -1;
	return 0;	
}

char *recv_file()
{
    char *str = (char*)calloc(1, 9);
    recv(netfd, str, 8, 0);
    int nb_char = atoi(str);
    str = (char*)realloc(str, nb_char + 1);
	str[0] = 0;
    int a = 0; 
    while (a < nb_char)
        a += recv(netfd, str + a, nb_char -a , 0);
    str[nb_char] = 0;
    return str;
}
