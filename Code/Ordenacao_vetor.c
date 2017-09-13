/*
* Actor: DenyHs.
* Date: Forgot it.	
* 
* Description:The code orders a vector and then reads the number and places it in the form of *ladder with their respective values ​​... Execute to understand.
*/

#include <stdio.h>
#define N 6

int main()
{
    int Vet[]={1,3,9,6,8,4},Num,Aux,count,i;

    for(count=0;count<N;count++){
        for(i=1+count;i<N;i++){
            if(Vet[count]>Vet[i]){
                Aux=Vet[count];
                Vet[count]=Vet[i];
                Vet[i]=Aux;
            }
        }
    }

    for(count=0;count<N;count++){
        Num=Vet[count];
        for(i=0;i<Num;i++){
            printf("%d",Num);
        }
        printf("\n");
    }

    return 0;
}
