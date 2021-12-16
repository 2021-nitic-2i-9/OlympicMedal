#include <stdio.h>
#include <string.h>
#include "type.h"
char *lower(char *str);
char *removenl(char *str);
int namecountry(type_country_data *data, int num) {
    int much,i;
    char name[30];
    printf("Enter Country Name: ");
    fgets(name, sizeof name, stdin);
    for ( i = 0; i < num; i++)
    {
        much=strcmp(lower(removenl(name)),lower(data[i].name));
        if (much==0)
        {
            break;
        }
    }
    if (much!=0)
    {
        printf("There is no data.\n");
    }

return i;
}