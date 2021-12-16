#include <stdio.h>
#include "type.h"

// 単一のデータ表示
// ランクを非表示にする場合, rankを0に
// 総数を表示する場合, istotalを1に
void display_data(type_country_data *data, int index, int rank, int istotal) {
    if (rank == 0) printf("%s\n", data[index].name);
    else printf("%d: %s\n", rank, data[index].name);
    if (istotal != 1) printf("Gold: %2d Silver: %2d Bronze: %2d\n", data[index].gold, data[index].silver, data[index].bronze);
    else {
        int total = data[index].gold + data[index].silver + data[index].bronze;
        printf("Total: %3d Gold: %2d Silver: %2d Bronze: %2d\n", total, data[index].gold, data[index].silver, data[index].bronze);
    }
}

// すべてのデータを表示
// numはdataの要素数
// 総数を表示する場合, istotalを1に
void all_data_display(type_country_data *data, int num, int istotal) {
    for (int i = 0; i < num; i++) {
        display_data(data, i, i + 1, istotal);
    }
}