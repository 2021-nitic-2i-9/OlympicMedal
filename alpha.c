#include <stdio.h>
#include <string.h>
int alpha(char a[64],char b[64]){
    if(strcmp(a,b)==0) return 0;    //全く同じ文字列だった場合に2を出力
    int n=0;
    while(1){                       //ここから無限ループ
        if(a[n] > b[n]) return 1;   //アルファベット順で遅い方が左の入力だった場合に1を出力。
        if(b[n] > a[n]) return 0;
        else{
            if(n>64) break;
            n++;                    //同じ文字だったら次の文字へ
            continue;               //ここまで無限ループ
        }
        return 0;
    }
}