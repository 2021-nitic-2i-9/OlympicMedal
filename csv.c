#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
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
            if (!isCut) result_tmp[result_index] = '\0';
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

// data.csvからデータ取得
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

// データ書き込み (リセットする場合, isResetを1に)
void write_countries_data(type_country_data *new_data, int datasize, int isReset) {
    FILE *FP;
    time_t t = time(NULL);
    char oldfilename[64], *filename = "data.csv", *header = "Country,Gold,Silver,Bronze\n";
    sprintf(oldfilename, "%ld_data.csv.old", t);

    unsigned count_countries = get_count_countries(), writing_datasize = count_countries + datasize, i = 0;
    struct _country_data old_countries_data[count_countries], writing_countries_data[writing_datasize];
    get_countries_data(old_countries_data);

    // ファイル名の変更
    if (rename(filename, oldfilename) != 0) {
        printf("Error\n");
        exit(-1);
    }

    if ((FP = fopen(filename, "w")) == NULL) {
        printf("Error\n");
        exit(-1);
    }

    fprintf(FP, header);

    if (isReset == 1) {
        for (int i = 0; i < datasize; i++) {
            fprintf(FP, "\"%s\",%d,%d,%d\n", removenl(new_data[i].name), new_data[i].gold, new_data[i].silver, new_data[i].bronze);
        }
        return;
    }

    for (i = 0; i < count_countries; i++) {
        strcpy(writing_countries_data[i].name, old_countries_data[i].name);
        writing_countries_data[i].gold = old_countries_data[i].gold;
        writing_countries_data[i].silver = old_countries_data[i].silver;
        writing_countries_data[i].bronze = old_countries_data[i].bronze;
    }

    for (int j = 0; j <= datasize; i++, j++) {
        strcpy(writing_countries_data[i].name, new_data[j].name);
        writing_countries_data[i].gold = new_data[j].gold;
        writing_countries_data[i].silver = new_data[j].silver;
        writing_countries_data[i].bronze = new_data[j].bronze;
    }

    for (int n = 0; n < writing_datasize; n++) {
        fprintf(FP, "\"%s\",%d,%d,%d\n", removenl(writing_countries_data[n].name), writing_countries_data[n].gold, writing_countries_data[n].silver, writing_countries_data[n].bronze);
    }
}

// 書き込みデータ取得
void get_writing_data() {
    int count, isReset, gold, silver, bronze, isEnd, max = 256;
    struct _country_data writing_countries_data[max];
    char country_name[256], tmp[8];

    printf("--- Input Data ---\n");

    printf("Enter 1 to overwrite the data: ");
    fgets(tmp, sizeof(tmp), stdin);
    isReset = atoi(tmp);

    for (count = 0; count < max; count++) {
        country_name[0] = '\0';
        gold = 0;
        silver = 0;
        bronze = 0;

        printf("----- %d -----\n", count + 1);
        printf("Enter Country Name(Alphabet Only): ");
        fgets(country_name, sizeof(country_name), stdin);

        printf("Enter the number of Gold Medals won: ");
        fgets(tmp, sizeof(tmp), stdin);
        gold = atoi(tmp);

        printf("Enter the number of Silver Medals won: ");
        fgets(tmp, sizeof(tmp), stdin);
        silver = atoi(tmp);

        printf("Enter the number of Bronze Medals won: ");
        fgets(tmp, sizeof(tmp), stdin);
        bronze = atoi(tmp);

        strcpy(writing_countries_data[count].name, country_name);
        writing_countries_data[count].gold = gold;
        writing_countries_data[count].silver = silver;
        writing_countries_data[count].bronze = bronze;

        printf("Enter 1 to exit: ");
        fgets(tmp, sizeof(tmp), stdin);
        isEnd = atoi(tmp);

        if (isEnd == 1) break;
    }

    // 最後の分を追加
    count++;

    write_countries_data(writing_countries_data, count, isReset);
}
