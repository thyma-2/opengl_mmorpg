#include "collision.hh"

extern char order[9999];
extern std::vector<std::vector<float>> land;
extern std::vector<struct unit*> unit_list;

void collision(void)
{
	for (int i = 0; i < unit_list.size(); i++)
	{
		if (land[(int)unit_list[i]->obj->position[2]][(int)unit_list[i]->obj->position[0]] == 0.0)
		{
			float a = unit_list[i]->obj->position[0] - unit_list[i]->lastx;
			float b = unit_list[i]->obj->position[2] - unit_list[i]->lastz;
			sprintf (order + strlen(order), "%d 06 -%f %d 04 -%f ", unit_list[i]->id, 2*b, unit_list[i]->id, 2*a);
		}
	}
}	

