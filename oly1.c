#include <stdio.h>  
int check_sum_medal(int aG,int aS,int aB,int bG,int bS,int bB){   //G=金,S=銀,B=銅//
int Lchange;

if (aG<bG)  //aとbの金メダルの比較：
{
    Lchange=0;
}
else if (aG==bG)
{
    if (aS<bS)
    {
        Lchange=1;
    }
    else if (aS==bS)
    {
        if (aB<bB)
        {
           Lchange=1;
        }
    }    
}

    return Lchange;
}