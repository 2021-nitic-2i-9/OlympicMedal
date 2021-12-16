#include <stdio.h>
#include "type.h"

// ランクを非表示にするには rank を0に
void display_data(type_country_data *data, int index, int rank) {
    if (rank == 0) printf("%s\n", data[index].name);
    else printf("%d: %s\n", rank, data[index].name);
    printf("Gold: %2d Silver: %2d Bronze: %2d\n", data[index].gold, data[index].silver, data[index].bronze);
}

// すべてのデータを表示
void all_data_display(type_country_data *data, int num) {
    for (int i = 0; i < num; i++) {
        display_data(data, i, i + 1);
    }
}