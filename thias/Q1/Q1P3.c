#include <stdio.h>
#include <stdlib.h>
#define PI 4

int main(){
    int val = 0;
    char c = '1';
    int p = 0;
    int count = 0;
    while (c != EOF){
        c = getchar();
        switch (c){
            case 'A':
                p += 1;
                count = (count+1) %3;
                break;
            case 'B':
                val += 1;
                p += 1;
                count = (count+1) %3;
                break;
            case 'C':
                val += 3;
                p += 1;
                count = (count+1) %3;
                break;
            case 'D':
                val += 5;
                p += 1;
                count = (count+1) %3;
                break;
            case 'x':
                count = (count+1) %3;
                break;
            default:
                break;
        }
        if (count == 0){
            val += p*(p-1);
            p = 0;
        }
        //printf("%d, ", count);
        //printf("%c:%d, ", c, val);
    } 
                                                        //Programm ends about halfway through for no known reason
    printf("\n%d\n", val);
    return 0;
}