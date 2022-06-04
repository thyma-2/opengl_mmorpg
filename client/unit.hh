#pragma once
#include "3d/object.hh"

struct unit
{
	/////////////// online variable
	int id, pv;
	char acount[50];
	char name[50];
	char utype[20];
	char bossname[50];
	struct object* obj;
	/////////////// local variable
	float lastx, lasty, lastz;
	
};

struct unit *init_unit_list(char *str, char *name);
void update_unit_list(char *str);
