#include "send.h"

extern struct unit *unitlist;

void send_file(int socket,char *map, size_t size_map)
{
    char *str_nb = calloc(sizeof(char), 9);
    sprintf(str_nb, "%ld", size_map);
    send(socket, str_nb, 8, MSG_NOSIGNAL);
    send(socket, map, size_map, MSG_NOSIGNAL);
    free(str_nb);
}

void send_unit_list(int socket)
{
	char order[100020] = {0};
	char *ordre = &order[8];
    for (struct unit *u = unitlist; u != NULL; u = u->next)
	{
		sprintf (ordre + strlen(ordre), "%d %d %s %s %s %f %f %f %f %f %f\n", u->id, u->pv, u->acount, u->name, u->utype, u->x, u->y, u->z, u->rx, u->ry, u->rz);
	}
	int s = strlen(ordre);
	if (s > 0)
	{
		sprintf (order, "%d", s);
		send(socket, order, s+ 8, MSG_NOSIGNAL);
	}
}

int generate_order(char *order)
{
	return 0;
}
