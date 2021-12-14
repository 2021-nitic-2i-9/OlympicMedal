#include <stdio.h>
#include <string.h>

#define SWAP(a,b)   { int temp = a; a = b; b = temp; }

void sumsort(char **countries,int *g,int *s,int *b,int size){
    int i,j;
    for(i=0; i<size-1; i++){
        for(j=size-1; j>i; j--){
            if(check_sum_medal(*(g+i),*(s+i),*(b+i),*(g+j),*(s+j),*(b+j))){
                char ctemp[64];
                strcpy(ctemp,*(countries+i));
                strcpy(*(countries+i),*(countries+j));
                strcpy(*(countries+j),ctemp);

                SWAP(*(g+i),*(g+j))
                SWAP(*(s+i),*(s+j))
                SWAP(*(b+i),*(b+j))
            }
        }
    }
}/*
int main(void){
    char country[][6]={"Abcd","Bdc","Cde","Defgh","Efg"};
    int gold[]={6,7,1,6,9};
    int silver[]={5,8,2,5,7};
    int bronze[]={1,8,3,7,9};
    char *pcountry[5];
    int i;
    for(i=0; i<5; i++){
        pcountry[i] = &country[i][0];
    }
    sumsort(pcountry,gold,silver,bronze,5);
    for(i=0; i<5; i++){
        printf("%s,%d,%d,%d:%d\n",country[i],gold[i],silver[i],bronze[i],gold[i]+silver[i]+bronze[i]);
    }
}*/