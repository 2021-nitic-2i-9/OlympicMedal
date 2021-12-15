#include <stdio.h>
#include <string.h>

#define SWAP(a,b) { int temp =a; a = b; b = temp; }

void alphasort(char **countries,int *g,int *s,int *b,int size){
    int i,j;
    for(i=0; i<size-1; i++){
        for(j=size-1; j>i; j--){
            if(alpha(*(countries+i),*(countries+j))){
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