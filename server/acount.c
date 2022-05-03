#include "acount.h"

void cut(char *str, char cutter)
{
    int i = 0;
    while (str[i] != 0)
    {
        if (str[i] == cutter)
        {
            str[i] = 0;
            return;
        }
        i++;
    }
}

int open_acount(char *test)
{
    if (test[0] == '\0' || test[0] == '\n')
        return 0;
    FILE *acount = fopen("sfiles/acount.txt", "r");
    char *line = NULL;
    size_t len = 0;
    while (getline(&line, &len, acount) > 0)
    {
        if (strncmp(line, test, strlen(line) - 1) == 0)
        {
            fclose(acount);
            return 1;
        }
    }
    fclose(acount);
    return 0;
}
