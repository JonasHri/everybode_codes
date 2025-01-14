#include <stdio.h>
#include <stdlib.h>
#define PI 4

int main(){
    int val = 0;
    char c = '1';
    int p = 0;
    int count = 0;
    do {
        c = getchar();
        switch (c){
            case 'A':
                p += 1;
                count = (count+1) %2;
                break;
            case 'B':
                val += 1;
                p += 1;
                count = (count+1) %2;
                break;
            case 'C':
                val += 3;
                p += 1;
                count = (count+1) %2;
                break;
            case 'D':
                val += 5;
                p += 1;
                count = (count+1) %2;
                break;
            case 'x':
                count = (count+1) %2;
                break;
            default:
                break;
        }
        if (p == 2)
            val += 2;
        if (count == 0){
            p = 0;
        }
        //printf("%d, ", count);
        printf("%c:%d, ", c, val);
    } while (c != '.');

    printf("\n%d\n", val);
    return 0;
}