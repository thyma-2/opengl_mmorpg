#pragma once

#include <stdlib.h>
#include "utile/file.h"
#include <string.h>

struct unit
{
	////////////// online variables
	int id, pv;
	char acount[50];
	char name[50];
	char utype[20];
	float x,y,z,rx,ry,rz;
	///////////// local variables
	struct unit* next;
	char has_changed;
};

char acount_have_unit(char *name);
void init_unit_list(char *path);
void create_new_char(char *name, char *acount);
struct unit *get_ptr_from_id(int id);
