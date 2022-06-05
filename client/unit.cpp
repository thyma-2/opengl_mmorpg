#include "unit.hh"

std::vector<struct unit*> unit_list;

int find_index(int id)
{
	for (int i = 0; i < unit_list.size(); i++)
		if (unit_list[i]->id == id)
			return i;
	return -1;
}

void free_unit(int id)
{
	for (int i = 0; i < unit_list.size(); i++)
        if (unit_list[i]->id == id)
			unit_list.erase(unit_list.begin() + i);
}

struct unit *init_unit_list(char *str, char *name)
{
	int i = 0;
	char pathmodel[70] = "cfiles/";
	float x,y,z,rx,ry,rz;
	struct unit *to_ret = NULL;
	while (str[i] != 0)
	{
		struct unit *u = (struct unit*)malloc(sizeof(struct unit));
		sscanf(str + i, "%d %d %s %s %s %s %f %f %f %f %f %f", &u->id, &u->pv, u->acount, u->name, u->utype, u->bossname, &x, &y, &z, &rx, &ry, &rz);
		u->lastx = x;
		u->lasty = y;
		u->lastz = z;
		unit_list.push_back(u);
		while (str[i] != '\n')
		{
			if (str[i] == 0)
			{
				return to_ret;
				free(str);
			}
			i++;
		}
		i++;
		pathmodel[7] = 0;
		strcat(pathmodel, u->utype);
		strcat(pathmodel, ".obj");
		int model_indice = load_model_from_obj(pathmodel, 1);
		if (strcmp(u->acount, name) == 0)
            to_ret = u;
		u->obj = add_object(nullptr, model_indice, x, y, z, rx,ry,rz);
	}
	return to_ret;
}

void update_unit_list(char *str)
{
	int i = 0;
    while (str[i] != 0)
    {
		int id = atoi(str + i);
		int index = find_index(id);
		unit_list[index]->lastx = unit_list[index]->obj->position[0];
		unit_list[index]->lasty = unit_list[index]->obj->position[1];
		unit_list[index]->lastz = unit_list[index]->obj->position[2];
        sscanf(str + i, "%d %d %s %s %s %s %f %f %f %f %f %f", &unit_list[index]->id, &unit_list[index]->pv, unit_list[index]->acount, unit_list[index]->name, unit_list[index]->utype, unit_list[index]->bossname, &unit_list[index]->obj->position[0], &unit_list[index]->obj->position[1], &unit_list[index]->obj->position[2], &unit_list[index]->obj->rx, &unit_list[index]->obj->ry, &unit_list[index]->obj->rz);
        while (str[i] != '\n')
            i++;
        i++;
	}
}
