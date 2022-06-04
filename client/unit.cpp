#include "unit.hh"

std::vector<struct unit*> unit_list;

void free_unit(int id)
{
	if (unit_list[id] == NULL)
		return;
	if (unit_list[id]->id != -1)
		free_object_tree(unit_list[id]->obj);
	free(unit_list[id]);
	unit_list[id] = NULL;
}

void insert_into_unitlist(struct unit *u)
{
	if (u->id <= unit_list.size() - 1 && unit_list.size() > 0)
	{
		free_unit(u->id);
		unit_list[u->id] = u;
		return;
	}
	while (u->id > unit_list.size())
	{
	
	struct unit *bullshit = (struct unit*)malloc(sizeof(struct unit));
		bullshit->id = -1;
		unit_list.push_back(bullshit);
	}
	unit_list.push_back(u);
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
		insert_into_unitlist(u);
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
		int model_indice;
		if (strcmp(u->acount, name) == 0)
		{
            to_ret = u;
			model_indice = load_model_from_obj(pathmodel, 0);
		}
		else
			model_indice = load_model_from_obj(pathmodel, 1);
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
		unit_list[id]->lastx = unit_list[id]->obj->position[0];
		unit_list[id]->lasty = unit_list[id]->obj->position[1];
		unit_list[id]->lastz = unit_list[id]->obj->position[2];
        sscanf(str + i, "%d %d %s %s %s %s %f %f %f %f %f %f", &unit_list[id]->id, &unit_list[id]->pv, unit_list[id]->acount, unit_list[id]->name, unit_list[id]->utype, unit_list[id]->bossname, &unit_list[id]->obj->position[0], &unit_list[id]->obj->position[1], &unit_list[id]->obj->position[2], &unit_list[id]->obj->rx, &unit_list[id]->obj->ry, &unit_list[id]->obj->rz);
        while (str[i] != '\n')
            i++;
        i++;
	}
}
