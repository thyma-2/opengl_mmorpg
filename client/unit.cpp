#include "unit.hh"

std::vector<struct unit> unit_list;

void init_unit_list(char *str)
{
	int i = 0;
	char pathmodel[70] = "cfiles/";
	float x,y,z,rx,ry,rz;
	while (str[i] != 0)
	{
		struct unit *u = (struct unit*)malloc(sizeof(struct unit));
		sscanf(str + i, "%d %d %s %s %s %f %f %f %f %f %f", &u->id, &u->pv, u->acount, u->name, u->utype, &x, &y, &z, &rx, &ry, &rz);
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
		pathmodel[7] = 0;
		strcat(pathmodel, u->utype);
		strcat(pathmodel, ".obj");
		int model_indice = load_model_from_obj(pathmodel, 25);
		u->obj = add_object(nullptr, model_indice, x, y, z, rx,ry,rz);
	}
}
