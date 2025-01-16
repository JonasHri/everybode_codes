#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define PI 4

int nachbarn(int level, char field[53][144]){
    int ret = 0;
    int n = level;

    for (int u = 1; u < 52; u++){
        for (int v = 1; v < 143; v++){
            if (field[u][v]-48 == n && field[u-1][v]-48 >= n && field[u][v-1]-48 >= n && field[u+1][v]-48 >= n && field[u][v+1]-48 >= n 
                && field[u-1][v-1]-48 >= n && field[u+1][v-1]-48 >= n && field[u-1][v+1]-48 >= n && field[u+1][v+1]-48 >= n){
                field[u][v] = n+1;
                ret += 1;
            }
            printf("%c", field[u][v]);
        }
        printf("\n");
    }


    printf("Nach %d Iterationen: %d\n", level+1, ret);
    return ret;
}

int main(){
    char input[53][144];
    for(int i = 0; i < 51; i++)
        for(int j = 0; j < 142; j++)
            input[i+1][j+1] =  getchar(); 

    for (int q = 0; q < 53; q++){
        input[q][0] = '.';
        input[q][143] = '.';
    }

    for (int p = 0; p < 144; p++){
        input[0][p] = '.';
        input[52][p] = '.';
    }

    int res = 0;

    for(int n = 0; n < 53; n++)
        for(int m = 0; m < 144; m++)
            if(input[n][m]=='#'){
                res += 1;
                input[n][m]='1';
            }

    int new = res;
    int count = 1;

    //printf("Nach Erster Iteration: %d\n", new);

    do{
        res = new;
        new += nachbarn(count, input);
        count += 1;
    } while(new != res);

    printf("\n%d\n", new);
    return 0;
}