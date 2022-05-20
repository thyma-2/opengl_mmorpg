#include "recv.h"

void parse_order(char *line)
{
	int i = 0;
    int j;
    char tmpC[50];
    while (line[i] != 0)
    {
		int id = atoi(&line[i]);
        struct unit *p = get_ptr_from_id(id);
        if (p == NULL)
            return;
        p->has_changed = 1;
        while (line[i] != ' ')
            i++;
        i++;
        int idaction = atoi(&line[i]);
        i += 3;
        switch(idaction)
        {
            case 0:
				if (line[i] == '+')
                {
                    i++;
                    p->pv += atoi(&line[i]);
                }
                else if (line[i] == '-')
                {
                    i++;
                    p->pv -= atoi(&line[i]);
                }
                else
                    p->pv = atoi(&line[i]);
                while(line[i] != ' ')
                    i++;
                i++;
                break;
			case 4:
                if (line[i] == '+')
                {
                    i++;
                    p->x += atof(&line[i]);
                }
                else if (line[i] == '-')
                {
                    i++;
                    p->x -= atof(&line[i]);
                }
                else
                    p->x = atof(&line[i]);
                while(line[i] != ' ')
                    i++;
                i++;
                break;
			case 5:
                if (line[i] == '+')
                {
                    i++;
                    p->y += atof(&line[i]);
                }
                else if (line[i] == '-')
                {
                    i++;
                    p->y -= atof(&line[i]);
                }
                else
                    p->y = atof(&line[i]);
                while(line[i] != ' ')
                    i++;
                i++;
                break;
			case 6:
                if (line[i] == '+')
                {
                    i++;
                    p->z += atof(&line[i]);
                }
                else if (line[i] == '-')
                {
                    i++;
                    p->z -= atof(&line[i]);
                }
                else
                    p->z = atof(&line[i]);
                while(line[i] != ' ')
                    i++;
                i++;
                break;
			case 8:
                if (line[i] == '+')
                {
                    i++; 
                    p->ry += atof(&line[i]);
                }
                else if (line[i] == '-')
                {
                    i++; 
                    p->ry -= atof(&line[i]);
                }
                else
                    p->ry = atof(&line[i]);
                while(line[i] != ' ')
                    i++;
                i++;
                break;
			case 9:
                if (line[i] == '+')
                {
                    i++; 
                    p->rz += atof(&line[i]);
                }
                else if (line[i] == '-')
                {
                    i++; 
                    p->rz -= atof(&line[i]);
                }
                else
                    p->rz = atof(&line[i]);
                while(line[i] != ' ')
                    i++;
                i++;
                break;
		}
	}
}
