#include <stdio.h>
#include <string.h>
char *lower(char *);

// アルファベット順での大小比較
int alpha(char a[64],char b[64]) {
    a = lower(a);
    b = lower(b);
    if (strcmp(a, b) == 0) return 0;    //全く同じ文字列だった場合に2を出力
    int n = 0;
    while (1) {                       //ここから無限ループ
        if (a[n] > b[n]) return 1;   //アルファベット順で遅い方が左の入力だった場合に1を出力。
        if (b[n] > a[n]) return 0;
        else {
            if (n > 64) break;
            n++;                    //同じ文字だったら次の文字へ
            continue;               //ここまで無限ループ
        }
        return 0;
    }
}

// メダルランキングでの大小比較
// G=金,S=銀,B=銅
int check_rank_medal(int aG, int aS, int aB, int bG, int bS, int bB) {
    int Lchange = 0;

    // aとbの金メダルの比較
    if (aG < bG) {
        Lchange = 1;
    } else if (aG == bG) {
        if (aS < bS) {
            Lchange = 1;
        } else if (aS == bS) {
            if (aB < bB) {
                Lchange = 1;
            }
        }    
    }
    return Lchange;
}

// メダル総数での大小比較
// g=金,s=銀,b=銅
int check_sum_medal(int ag, int as, int ab, int bg, int bs, int bb){
	int a_total;
	int b_total;
	int Nchange;

	a_total = ag + as + ab;
	b_total = bg + bs + bb;
	
	//aの国が大きい場合0を返す
	if (a_total > b_total) {
		Nchange = 0;
	} else {
		Nchange = 1;
	}
	return Nchange;
}
