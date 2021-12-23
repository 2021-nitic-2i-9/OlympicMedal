#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "type.h"

// 小文字化
char *lower(char *str) {
    char *tmp;
    for (tmp = str; *tmp; tmp++) {
        *tmp = tolower(*tmp);
    }
    return str;
}

// 末尾の改行削除
char *removenl(char *str) {
    char *tmp;
    for (tmp = str; *tmp; tmp++) {
        if (*tmp == 0x0a) *tmp = '\0';
    }
    return str;
}

// 入力された国名のIndexを返す
int namecountry(type_country_data *data, int num) {
    int much, i;
    char name[30];

    printf("Enter Country Name: ");
    fgets(name, sizeof name, stdin);

    for (i = 0; i < num; i++) {
        much = strcmp(lower(removenl(name)), lower(data[i].name));
        if (much == 0) {
            break;
        }
    }

    if (much != 0) {
        printf("There is no data.\n");
    }

    return i;
}