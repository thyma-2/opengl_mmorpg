#include "unit.h"

struct unit *unitlist = NULL;

init_unit_list(char *path)
{
	char *str = loadfile(path);
	int i = 0;
	while (str[i] != 0)
	{
		unit *u = malloc(sizeof(struct unit));
		//unit_list.push_back(u);
		i = int_to_next(str, &u.id, i, ',');
		i = char_to_next(str, u.acount, i, ',');
		i = char_to_next(str, u.name, i, ',');
		i = char_to_next(str, u.utype, i, ',');
		i = int_to_next(str, &u.pv, i, ',');
		i = float_to_next(str, &u.x, i, ',');
		i = float_to_next(str, &u.y, i, ',');
		i = float_to_next(str, &u.z, i, ',');
		i = float_to_next(str, &u.rx, i, ',');
        i = float_to_next(str, &u.ry, i, ',');
        i = float_to_next(str, &u.rz, i, ',');
		i++;
	}
	free(str);
	return u;
}
