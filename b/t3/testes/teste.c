#include <stdio.h>

int main(int argc, char const *argv[]) {
    int vetor[20] = {2,3,6,9,15};
    int insert = 7;
    int aux[20];
    int i;

    for(i = 0; i < 20; i++){
        if(vetor[i] < insert) aux[i] = vetor[i];
        if(vetor[i] > insert){
            aux[i] = insert;
            break;
        }
    }

    for(int j = i; j < 20 - 1; j++){
        aux[j+1] = vetor[j];
    }

    for (size_t i = 0; i < 20; i++) {
        printf("%d\n", aux[i]);
    }



    return 0;
}
