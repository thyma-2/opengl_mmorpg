#include "3d/object.hh"

struct unit
{
	/////////////// online variable
	int id, pv;
	char acount[50];
	char name[50];
	char utype[20];
	struct object* obj;
	/////////////// local variable
};

struct unit *init_unit_list(char *str, char *name);
void update_unit_list(char *str);
