#include <stdio.h>

#define ORDEM 5

int main(){
    int vector[ORDEM];
    int auxili[ORDEM];
    int i, j, k, input;

    for(i = 0; i < ORDEM; i++) vector[i] = 0;

    i = 0;


    for(i = 0; i < ORDEM; i++){

        scanf("%d\n", &input);
        if(vector[0] == 0) vector[0] = input;

        for(j = 0; j < ORDEM; j++);

        printf("%d\n", i);
        for(j = 0; j < ORDEM; j++) printf("%d ", vector[j]);
        printf("\n\n");
    }

    /*for(i = 0; i < ORDEM; i++){

        scanf("%d\n", &input);

        if(vector[0] == 0) vector[0] = input;

        if(input < vector[i] && vector[i + 1] == 0){

            for(j = i; j < ORDEM; j++){
                auxili[j] = vector[j];
            }

            vector[i] = input;

            for(j = i; j < ORDEM - 1; j++){
                vector[j + 1] = auxili[j];
            }

        }
    }
    for(i = 0; i < ORDEM; i++) printf("%d, ", vector[i] = 0);*/
}
