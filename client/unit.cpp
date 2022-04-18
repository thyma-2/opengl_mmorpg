#include "unit.hh"

std::vector<struct unit> unit_list;

int int_to_next(char *str, int *to_set, int i)
{
	*to_set = atoi(str + i);
	while (str[i] != ',')
	{
		i++;
	}
	return i + 1;
}

int char_to_next(char *str, char *to_set, int i)
{
	int j = 0;
	while (str[i] != ',')
	{
		to_set[j] = str[i];
		i++;
		j++;
	}
	to_set[j] = 0;
	return i + 1;
}

void init_unit_list(char *str)
{
	int i = 0;
	char pathmodel[70] = "models/";
	int x,y,z;
	while (str[i] != 0)
	{
		struct unit *u = (struct unit*)malloc(sizeof(struct unit));
		i = int_to_next(str, &u->id, i);
		i = char_to_next(str, u->acount, i);
		i = char_to_next(str, u->name, i);
		i = char_to_next(str, u->utype, i);
		i = int_to_next(str, &u->pv, i);
		i = int_to_next(str, &x, i);
		i = int_to_next(str, &y, i);
		i = int_to_next(str, &z, i);
		i++;
		pathmodel[7] = 0;
		strcat(pathmodel, u->utype);
		strcat(pathmodel, ".obj");
		int model_indice = load_model_from_obj(pathmodel, 25);
		u->obj = add_object(nullptr, model_indice, x, y, z, 0,0,0);
	}
}

char *loadfile(void)
{
	FILE *f = fopen("unitlist.txt", "rb");
    size_t size;
	fseek(f, 0, SEEK_END);
	size = ftell(f);
	fseek(f, 0, SEEK_SET);  /* same as rewind(f); */
    char *source = (char*)malloc(size);
    fread(source, size, 1, f);
	source[size] = 0;
    fclose(f);
	return source;
}
	
