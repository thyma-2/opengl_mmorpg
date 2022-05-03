#include "unit.h"

struct unit *unitlist = NULL;

int find_smalest_available_id(int from)
{
    for (struct unit *u = unitlist; u != NULL; u = u->next)
    {
        if (u->id == from)
            return find_smalest_available_id(from + 1);
    }
    return from;
}



char acount_have_unit(char *name)
{
	for (struct unit *u = unitlist; u != NULL; u=u->next)
	{
		if (strcmp(u->acount, name) == 0)
			return 1;
	}
	return 0;
}

void init_unit_list(char *path)
{
	char *str = load_file(path);
	int i = 0;
	while (str[i] != 0)
	{
		struct unit *u = malloc(sizeof(struct unit));
		u->next = unitlist;
		unitlist = u;
		sscanf (str, "%d,%d,%s,%s,%s,%f,%f,%f,%f,%f,%f", &u->id, &u->pv, u->acount, u->name, u->utype, &u->x, &u->y, &u->z, &u->rx, &u->ry, &u->rz);
		while (str[i] != '\n')
		{
			if (str[i] == 0)
			{
				return;
				free(str);
			}
			i++;
		}
		i++;
	}
	free(str);
}

void create_new_char(char *name, char *acount)
{
	struct unit *u = malloc(sizeof(struct unit));
    u->next = unitlist;
    unitlist = u;
	strcpy(u->acount, acount);
	strcpy(u->name, name);
	u->x = 0;
	u->y = 0;
	u->z = 0;
	u->rx = 0;
	u->ry = 0;
	u->rz = 0;
	strcpy(u->utype, "man");
	u->pv = 10;
	u->id = find_smalest_available_id(0);
}
