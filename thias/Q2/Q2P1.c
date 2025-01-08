#include <stdio.h>
#include <stdlib.h>
#define PI 4

int matching(char c1, char c2, char words[][]){
    for(int j = 0; j < sizeof(words); j++){
        
    }
    return 1;
}

int main(){
    char words[7][3];
    int matches = 0;
    char current = getchar();
    for(int line = 0; current != '\0'; line++){     //Keywords speichern
        for(int row = 0; current != ','; row++){
            words[line][row] = getchar();
            current = getchar();
            printf("%c", words[line][row]);
        }
        current = getchar();
    }                                               //###Liest aktuell nur jedes zweite Symbol

    current = getchar();                            //nächste Zeile
    char follow1 = getchar();
    char follow2 = getchar();

    while(current != 0){
        for(int i = 0; i < sizeof(words); i++){
            if(current == words[i][0])
                matches += matching(follow1, follow2, words);
        }
        current = follow1;
        follow1 = follow2;
        follow2 = getchar();
    }


    printf("\n%d\n", matches);
    return 0;
}