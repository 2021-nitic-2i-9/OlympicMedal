#include <stdio.h>
#include <stdlib.h>
#include "type.h"

unsigned get_count_countries(void);
void get_countries_data(type_country_data *data);
void get_writing_data(void);
void sort(type_country_data *data,int size,int mode);
int namecountry(type_country_data *data, int num);
void display_data(type_country_data *data, int index, int rank);
void all_data_display(type_country_data *data, int num);

int main(void) {
    int mode = 0;
    char str[4];

    printf("--- mode ---\n1. Input Data\n2. Display Medal Ranking\
    \n3. Display The Total Medal Ranking\n4. Search Country Data\
    \n5. Display Data In Alphabetical Order\n");
    while (1) {
        printf("Enter mode: ");
        fgets(str, sizeof str, stdin);
        mode = atoi(str);

        if (mode >= 1 && mode <= 5) break;
        printf("Please Enter Again!\n");
    }

    printf("\n");

    unsigned count_countries = get_count_countries();
    struct _country_data countries_data[count_countries];
    // データ取得
    get_countries_data(countries_data);
    int index;

    switch (mode) {
        // データ入力
        case 1:
            get_writing_data();
            printf("done\n");
            break;
        // メダル順位表示
        case 2:
            sort(countries_data, count_countries, 1);
            all_data_display(countries_data, count_countries);
            break;
        // メダル総数順位表示
        case 3:
            sort(countries_data, count_countries, 0);
            all_data_display(countries_data, count_countries);
            break;
        // 国別データ表示
        case 4:
            // メダル順位順に並べ替え
            sort(countries_data, count_countries, 1);
            index = namecountry(countries_data, count_countries);
            if (index >= count_countries) break;
            display_data(countries_data, index, index + 1);
            break;
        // アルファベット順に表示
        case 5:
            sort(countries_data, count_countries, 2);
            all_data_display(countries_data, count_countries);
            break;
        default:
            break;
    }

    return 0;
}
