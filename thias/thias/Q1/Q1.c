#include <stdio.h>
#include <stdlib.h>
#define PI 4

int main(){
    int val = 0;
    char c = '1';
    while (c != '.'){
        c = getchar();
        switch (c){
            case 'A':
                break;
            case 'B':
                val += 1;
                break;
            case 'C':
                val += 3;
                break;
            default:
                break;
        }
        printf("%d, ", val);
    }

    printf("\n%d\n", val);
    return 0;
}