#include <stdio.h>
#include <stdlib.h>
#define PI 4

int main(){
    int list[20];
    int c = 0;
    int min = 9999;
    do{
        scanf("%d ", &list[c]);
        c += 1;
        if(list[c] != 0 && list[c] < min)
            min = list[c];
        printf("%d ", list[c]);
    } while(list[c] != 0);

    printf("\n%d\n", min);
    int total = 0;
    c = 0;
    do{
        total += list[c]-min;
        c += 1;
    }  while(list[c] != 0);

    printf("%d\n", total);

    return 0;
}