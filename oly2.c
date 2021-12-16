#include <stdio.h>
#include <string.h>
#include "type.h"
char *lower(char *str);
int namecountry(type_country_data *data, int num) {
    int much,i;
    char name[30];
    printf("国名を入力して下さい。")
    scanf("%s",name);
    for ( i = 0; i < num; i++)
    {
        much=strcmp(lower(name),lower(data[i].name));
        if (much==0)
        {
            break;
        }
    }
    if (much!=0)
    {
        printf("データがありません。");
    }

return i;
}