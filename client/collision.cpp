#include "collision.hh"

extern char order[9999];
extern std::vector<std::vector<float>> land;
extern std::vector<struct unit*> unit_list;

void collision(void)
{
	for (int i = 0; i < unit_list.size(); i++)
		if (unit_list[i]->obj->position[0] != unit_list[i]->lastx || unit_list[i]->obj->position[2] != unit_list[i]->lastz)
			sprintf(order + strlen(order), "%d 05 %f ", i, land[(int)unit_list[i]->obj->position[0]][(int)unit_list[i]->obj->position[2]] + 5);
}	
