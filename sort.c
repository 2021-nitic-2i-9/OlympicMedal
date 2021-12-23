#include <stdio.h>
#include <string.h>
#include "type.h"

int check_sum_medal(int,int,int,int,int,int);
int check_rank_medal(int,int,int,int,int,int);
int alpha(char [64],char [64]);

#define SWAP(a,b)   { int temp = a; a = b; b = temp; }

//mode:0で総数、1で順位、2でアルファベット順でソートする
void sort(type_country_data *data,int size,int mode){
    int i, j;
    switch (mode) {
        case 0:
            for (i = 0; i < (size - 1); i++) {
                for (j = (size - 1); j > i; j--) {
                    if (check_sum_medal(data[i].gold, data[i].silver, data[i].bronze, data[j].gold, data[j].silver, data[j].bronze) == 1) {
                        char ctemp[64];
                        strcpy(ctemp,data[i].name);
                        strcpy(data[i].name,data[j].name);
                        strcpy(data[j].name,ctemp);

                        SWAP(data[i].gold,data[j].gold)
                        SWAP(data[i].silver,data[j].silver)
                        SWAP(data[i].bronze,data[j].bronze)
                    }
                    
                }
            }
            break;
        case 1:
            for (i = 0; i < (size - 1); i++) {
                for (j = (size - 1); j > i; j--) {
                    if (check_rank_medal(data[i].gold, data[i].silver, data[i].bronze, data[j].gold, data[j].silver, data[j].bronze) == 1) {
                        char ctemp[64];
                        strcpy(ctemp,data[i].name);
                        strcpy(data[i].name,data[j].name);
                        strcpy(data[j].name,ctemp);

                        SWAP(data[i].gold,data[j].gold)
                        SWAP(data[i].silver,data[j].silver)
                        SWAP(data[i].bronze,data[j].bronze)
                    }
                }
            }
            break;
        case 2:
            for (i = 0; i < (size - 1); i++) {
                for (j = (size - 1); j > i; j--) {
                    if (alpha(data[i].name, data[j].name) == 1) {
                        char ctemp[64];
                        strcpy(ctemp,data[i].name);
                        strcpy(data[i].name,data[j].name);
                        strcpy(data[j].name,ctemp);

                        SWAP(data[i].gold,data[j].gold)
                        SWAP(data[i].silver,data[j].silver)
                        SWAP(data[i].bronze,data[j].bronze)
                    }
                }
            }
            break;
        default:
            printf("Not enabled mode.\n");
            break;
    }

    for (int m = 0; m < size; m++) {
        data[m].rank = m + 1;
    }

    for (int n = 0; n < (size - 1); n++) {
        switch (mode) {
            case 0:
                if (check_sum_medal(data[n].gold, data[n].silver, data[n].bronze, data[n + 1].gold, data[n + 1].silver, data[n + 1].bronze) == 2) {
                    data[n + 1].rank = data[n].rank;
                }
                break;
            case 1:
                if (check_rank_medal(data[n].gold, data[n].silver, data[n].bronze, data[n + 1].gold, data[n + 1].silver, data[n + 1].bronze) == 2) {
                    data[n + 1].rank = data[n].rank;
                }
                break;
            case 2:
                if (alpha(data[n].name, data[n + 1].name) == 2) {
                    data[n + 1].rank = data[n].rank;
                }
                break;
            default:
                break;
        }
    }
}