#include <stdio.h>
#include <stdlib.h>
#define PI 4

int main(){
    long list[500];
    for(int c = 0; c < 500; c++){
        scanf("%lu", &list[c]);
        // printf("%lu ", list[c]);
    }

    long total = 0;

    for(int c = 0; c < 500 ; c++){
        total += list[c];
    }

    long mean = total/500;
    printf("%lu\n", mean);

    long final = 0;

    for(int c = 0; c < 500; c++){
        final += abs(list[c]-mean);
    } 

    printf("%lu\n", final);

    return 0;
}