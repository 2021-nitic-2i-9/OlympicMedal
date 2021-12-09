#include <stdio.h>
#include <string.h>
#include <stdlib.h>
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

// データ区切り(.csv用)
char *cutcsv(char *input_str) {
    static char *savedstr;
    char *result, *tail;
    char delim = ',';
    char tmp[256], result_tmp[256], tail_tmp[256];
    char *str = input_str ? removenl(input_str) : savedstr;

    if (*str == '\0') {
        savedstr = '\0';
        return NULL;
    }

    strcpy(tmp, str);

    int isCut = 0, isContent = 0;
    for (int i = 0, result_index = 0, tail_index = 0; i < 256; i++) {
        // 末尾かどうか
        if (tmp[i] == '\0') {
            tail_tmp[tail_index] = '\0';
            break;
        }

        // 区切り後かどうか
        if (isCut) {
            tail_tmp[tail_index] = tmp[i];
            tail_index++;
            continue;
        }

        // ダブルクォーテーションかどうか
        if (tmp[i] == 0x22) {
            isContent = (isContent == 0) ? 1 : 0;
            continue;
        }

        // 区切られておらず, 区切り文字かどうか
        if (tmp[i] == delim && !isContent) {
            result_tmp[result_index] = '\0';
            isCut = 1;
            continue;
        }

        result_tmp[result_index] = tmp[i];
        result_index++;
    }

    result = &(result_tmp[0]);
    tail = &(tail_tmp[0]);
    savedstr = tail;

    return result;
}

// 国の数を取得
unsigned get_count_countries(void) {
    FILE *FP;
    char str[256];
    unsigned count = 0;

    if ((FP = fopen("data.csv", "r")) == NULL) {
        printf("Error\n");
        exit(-1);
    }

    while (fgets(str, 256, FP) != NULL) {
        count++;
    }

    // 1行目はヘッダーなので、その分を削除
    count--;

    fclose(FP);

    return count;
}

void get_countries_data(type_country_data *data) {
    FILE *FP;
    char str[256];
    int country_index, gold_index, silver_index, bronze_index;
    char *tmpstr;

    if ((FP = fopen("data.csv", "r")) == NULL) {
        printf("Error\n");
        exit(-1);
    }

    int i = 0, j = 0;
    while (fgets(str, 256, FP) != NULL) {
        tmpstr = cutcsv(removenl(str));
        j = 0;

        // 区切り
        while(tmpstr != NULL) {
            if (i == 0) {
                tmpstr = lower(tmpstr);
                if (strcmp(tmpstr, "country") == 0) country_index = j;
                else if (strcmp(tmpstr, "gold") == 0) gold_index = j;
                else if (strcmp(tmpstr, "silver") == 0) silver_index = j;
                else if (strcmp(tmpstr, "bronze") == 0) bronze_index = j;
                tmpstr = cutcsv(NULL);
                j++;
                continue;
            }

            if (j == country_index) strcpy(data[i - 1].name, tmpstr);
            else if (j == gold_index) data[i - 1].gold = atoi(tmpstr);
            else if (j == silver_index) data[i - 1].silver = atoi(tmpstr);
            else if (j == bronze_index) data[i - 1].bronze = atoi(tmpstr);
            tmpstr = cutcsv(NULL);
            j++;
        }
        i++;
    }

    fclose(FP);
}
