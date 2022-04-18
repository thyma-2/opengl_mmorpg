#define _GNU_SOURCE
#include "map_op.h"

void save_map(void)
{
	FILE *file = fopen("map.txt","w");
	char order[100000]; //TODO
	order[0] = 0;
	for (struct personnages *l = list; l != NULL; l = l->next)
	{
		sprintf(order + strlen(order), "%d %d %s %f %f %f %f %d %d %d %s %s %s %s %s %s %d [", l->id, l->pv, l->nom_de_compte, l->x, l->y, l->ordrex, l->ordrey, l->angle, l->timer_dom, l->faim, l->skin, l->nom, l->nom_superieur, l->titre, l->religion, l->region, l->nb_vassaux);
        for (struct linked_enemie *p = l->e_list; p != NULL; p = p->next)
        {
            if (p->next != NULL) 
                sprintf (order + strlen(order), "%s %d ", p->nom, p->rang);
            else
                sprintf (order + strlen(order), "%s %d", p->nom, p->rang);
        }
        strcat(order, "] [");
        for (struct linked_item *p = l->i_list; p != NULL; p =p->next)
        {
            if (p->next != NULL) 
                sprintf (order + strlen(order), "%s %d ", p->nom, p->count);
            else
                sprintf (order + strlen(order), "%s %d", p->nom, p->count);
        }
        sprintf(order + strlen(order),  "] %s %d %d %s %d %d", l->echange_player, l->item1, l->item2, l->speak, l->animation, l->animation_2);
		if (l->next != NULL)
			strcat(order, "\n");
	}
	fprintf(file, "%s", order);
	fclose(file);
}

struct personnages *init_map(void)
{
    FILE *acount = fopen("map.txt", "r+");
    char *line = NULL;
    size_t len = 0;
    while (getline(&line, &len, acount) > 0)
        list = append_perso(line);

    return list;
}
