/*  Título:
    TRABALHO 3 – ESTRUTURA DE DADOS II

    Descrição:
    Implementar (em linguagem C) uma Árvore B que possui como chave valores
    inteiros positivos não repetidos. A cada novo nó inserido devem ser mantidas
    as propriedades da árvore.

    Autor: Eduardo Stefanello
    Data: 7 de Junho de 2017
*/

#include <stdio.h>
#include <stdlib.h>

#define ORDEM 5
#define BT    (*page)

/*  Estrutura: Página da B
    Contém:
        Vetores para chaves e Filhos
        Inficadores de Tipo e de quantidade de chaves
        Tipos:
            0: Nó folha
            1: Nó interno
            2: Raiz sem filhos
            3: Raiz
*/
typedef struct bPage{
    int k[ORDEM - 1];           // Vetor para as Chaves da página
    struct bPage **p[ORDEM];    // Vetor para os Filhos da página
    int type;                   // Indicador do tipo de nó
    int keys;                   // Indicador da Quanidade de chave
}bPage;

/*  Anulador
    Anula vetor de ponteiros e zera vetor de chaves.
    Função auxiliar na inicialização da página
*/
void nullifier(bPage **page){
    for(int i = 0; i < ORDEM - 1; i++){
        BT->k[i] = 0;
        BT->p[i] = NULL;
    }
    BT->p[ORDEM] = NULL;
}

/*  Inicialização da Raiz
    Retorna espaço alocado com o tipo da página da árvore B
    com os vetores zerados ou anulados
    com o primeiro valor inserido
*/
bPage *initializeRoot(){
    bPage *thisPage = (bPage *) malloc(sizeof(bPage));
    nullifier(&thisPage);
    thisPage->type = 2; // Raiz sem filhos
    thisPage->keys = 0; // Nenhuma chave ainda
    return thisPage;
}



/*  Cabeçalhos
    Função de Impressão dos Cabeçalhos da execução do programa;
    Tipos de cabeçalhos:
    X. Cabeçalho geral
    1. Cabeçalho do menu principal com opções de execução;
    2. Cabeçalho entrada de valor para inserção;
*/
void headers(int option){
    system("clear");
    printf(" ========================================\n");
    printf(" -       Universidade Federal da        -\n");
    printf(" -            Fronteira Sul             -\n");
    printf(" - Disciplina de Estruturas de Dados II -\n");
    printf(" -            T2 - Árvore B             -\n");
    printf(" - Aluno:     Eduardo Stefanello        -\n");
    printf(" - Professor: Doglas André Finco        -\n");
    printf(" ========================================\n");
    if(option == 1){
        printf(" = OPÇÕES:                              =\n");
        printf(" = 1. Inserir Valor                     =\n");
        printf(" = 2. Percorrer Árvore                  =\n");
        printf(" = 0. Encerrar Execução                 =\n");
        printf(" ========================================\n");
        printf(" >>");
    }
    else if(option == 2){
        printf(" = Informe o Valor a ser inserido:      =\n");
        printf(" >>");
    }
    else if(option == 3){
        printf(" = Sua árvore está organizada           =\n");
        printf(" = da seguinte maneira:                 =\n\n");
    }
}

bPage *search(bPage **page, int newKey){
    if(BT->type == 2 || BT->type == 0){
        return BT;
    }
    else{
        for(int i = 0; i < 0; i++);
    }
    bPage *toReturn = NULL;
    return toReturn;
}

/*  Inserção
    Função recursiva.
    Recebe raiz da árvore e nova chave que será inserida.
    Leva em conta que já esiste árvore na primeira execução
*/
void insert(bPage **page, int newKey){
    if(&BT == NULL){
        BT = initializeRoot();
        bPage *toInsert = search(&BT, newKey);
    }

}

/*  principal
*/
int main(int argc, char const *argv[]) {
    short  option;
    int    newKey;
    bPage *bRoot = NULL;

    while(1){
        headers(1);
        scanf("%hi\n", &option);
        switch(option){
            case 1:
                headers(2);
                scanf("%d\n", &newKey);
                insert(&bRoot, newKey);
                break;
            case 2:
                printf("\n");
                break;
            default:
                return 0;
        }
    }

    return 0;
}
