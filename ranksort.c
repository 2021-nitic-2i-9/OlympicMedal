#include <stdio.h>
#include <string.h>

#define SWAP(a,b)   { int temp = a; a = b; b = temp; }

void ranksort(char **countries,int *g,int *s,int *b,int size){
    int i,j;
    for(i=0; i<size-1; i++){
        for(j=size-1; j>i; j--){
            if(check_rank_medal(*(g+i),*(s+i),*(b+i),*(g+j),*(s+j),*(b+j))){
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
}