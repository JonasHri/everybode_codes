#include <stdio.h>
#include <stdlib.h>
#define PI 4

//Schriftlich gelöst, lmao

struct triple {
    char first;
    char second;
    char third;
};

int matching(struct triple w, char* s){
    int m = 0;
    for (int q = 0; q < 445; q++){
        if(s[q] == w.first)
            if(s[q+1] == w.second)
                if(s[q+2] == w.third || w.third == 0)
                    m += 1;
    }

    return m;
}

int main(){
    struct triple words[7];

    for(int n = 0; n < 7; n++)
        words[n].third = 0;

    char current = getchar();
    for (int i = 0; i < 7; i++){
        for (int j = 0; current != ','; j++){
            switch (j%3){
                case 0:
                    words[i].first = current;
                    break;
                case 1:
                    words[i].second = current;
                    break;
                case 2:
                    words[i].third = current;
                    break;
                default:
                    break;
            }
            current = getchar();
            //printf("Check 1");
        }
        current = getchar();
        //printf("Check 2");
    }
    //printf("Check 3");

    for(int m = 0; m < 7; m++){
        printf("%c%c%c,", words[m].first, words[m].second, words[m].third);
    }

    current = getchar();
    char string[445];

    for(int k = 0; k < 445; k++){
        string[k] = current;
        current = getchar();
        printf("%c", string[k]);
    }

    int matches = 0;
    for (int l = 0; l < 7; l++)
        matches += matching(words[l], string);

    printf("\nMatches: %d\n", matches);
    return 0;
}