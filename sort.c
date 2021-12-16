#include <stdio.h>
#include <string.h>
#include "type.h"

int check_sum_medal(int,int,int,int,int,int);
int check_rank_medal(int,int,int,int,int,int);
int alpha(char [64],char [64]);

#define SWAP(a,b)   { int temp = a; a = b; b = temp; }
//mode:0で総数、1で順位、2でアルファベット順でソートする
void sort(type_country_data *data,int size,int mode){
    int i,j;
    switch (mode)
    {
    case 0:
    for(i=0; i<size-1; i++){
        for(j=size-1; j>i; j--){
            if(check_sum_medal(data[i].gold,data[i].silver,data[i].bronze,data[j].gold,data[j].silver,data[j].bronze)){
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
    for(i=0; i<size-1; i++){
        for(j=size-1; j>i; j--){
            if(check_rank_medal(data[i].gold,data[i].silver,data[i].bronze,data[j].gold,data[j].silver,data[j].bronze)){
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
    for(i=0; i<size-1; i++){
        for(j=size-1; j>i; j--){
            if(alpha(data[i].name,data[j].name)){
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
    printf("有効でないモードです\n");
        break;
    }
}