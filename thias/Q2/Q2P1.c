#include <stdio.h>
#include <stdlib.h>
#define PI 4

//Schriftlich gelöst, lmao

int matching(char c1, char c2, char* w){
    for(int j = 0; j < 7; j++){
        if (w[j*3+1] == c1)
            if (w[j*3+2] == c2 || w[j*3+2] == '-')
                return 1;
    }
    return 0;
}

int main(){
    char words[7][3];
    int matches = 0;
    char current = getchar();
    for(int line = 0; current != '\0'; line++){     //Keywords speichern
        for(int row = 0; current != ','; row++){
            //printf("C: %c, ", current);
            words[line][row] = current;
            current = getchar();
            //printf("%c", words[line][row]);
        }
        current = getchar();
        if(words[line-1][2] == 0)
            words[line-1][2] == '-';
    }                                          
                                                    //ab hier hakt es, hatte aber noch nicht die lust, es näher zu untersuchen     

    current = getchar();                            //nächste Zeile
    char follow1 = getchar();
    char follow2 = getchar();

    while(current != 0){
        for(int i = 0; i < 7; i++){
            if(current == words[i][0])
                matches += matching(follow1, follow2, *words);
        }
        current = follow1;
        follow1 = follow2;
        follow2 = getchar();
    }


    printf("\nMatches: %d\n", matches);
    return 0;
}