#include <stdio.h>
#include <stdlib.h>
#define PI 4

int main(){
    int list[200];
    int min = 9999;
    for(int c = 0; c < 200; c++){
        scanf("%d", &list[c]);
        if(list[c] != 0 && list[c] < min)
            min = list[c];
        printf("%d ", list[c]);
    }

    printf("\n%d\n", min);
    int total = 0;
    for(int c = 0; c < 200; c++){
        total += list[c]-min;
    } 

    printf("%d\n", total);

    return 0;
}