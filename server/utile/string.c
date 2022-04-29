#include "string.h"

int int_to_next(char *str, int *to_set, int i, char stop)
{
    *to_set = atoi(str + i);
    while (str[i] != stop)
        i++;
    return i + 1;
}

int float_to_next(char *str, float *to_set, int i, char stop)
{
    *to_set = atof(str + i);
    while (str[i] != stop)
        i++;
    return i + 1;
}

int char_to_next(char *str, char *to_set, int i, char stop)
{
    int j = 0;
    while (str[i] != stop)
    {
        to_set[j] = str[i];
        i++;
        j++;
    }
    to_set[j] = 0;
    return i + 1;
}
