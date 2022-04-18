#include "3d/object.hh"

struct unit
{
	int id, pv;
	char acount[50];
	char name[50];
	char utype[20];
	struct object* obj;
};

void init_unit_list(char *str);
char *loadfile(void);
