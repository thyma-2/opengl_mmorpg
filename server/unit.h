#include <stdlib.h>
#include "utile/string.h"
#include "utile/file.h"

struct unit
{
	int id, pv;
	char acount[50];
	char name[50];
	char utype[20];
	float x,y,z,rx,ry,rz;
	struct unit* next;
};

init_unit_list(char *path);
