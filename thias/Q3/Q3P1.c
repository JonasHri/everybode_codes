#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define PI 4

int nachbarn(int level, char field[13][30]){
    int ret = 0;
    int n = level+48;

    for (int u = 1; u < 12; u++){
        for (int v = 1; v < 29; v++){
            if (field[u][v] == n && field[u-1][v] >= n && field[u][v-1] >= n && field[u+1][v] >= n && field[u][v+1] >= n){
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
    char input[13][30];
    for(int i = 0; i < 13; i++)
        for(int j = 0; j < 30; j++)
            input[i][j] =  getchar(); 

    int res = 0;

    for(int n = 0; n < 13; n++)
        for(int m = 0; m < 30; m++)
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