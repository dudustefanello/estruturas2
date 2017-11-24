#include <stdlib.h>
#include <stdio.h>

#define T 2
#define ordem (T*2)










typedef struct TipoPagina{
    int *btkeys;
    struct TipoPagina **childs;
    int n;
} TipoPagina;

TipoPagina *newPage(){
    TipoPagina *auxiliar = (TipoPagina *) calloc(1, sizeof(TipoPagina));
    auxiliar->btkeys = (int *) calloc(ordem, sizeof(int));
    auxiliar->childs = (TipoPagina **) calloc(ordem + 1, sizeof(TipoPagina));
    return auxiliar;
}

/* Função confusa
*/
void InsereNaPagina(TipoPagina **D, int x, TipoPagina **PonteiroDir){
    int NaoAchouPosicao;
    int k;

    k = (*D)->n;
    NaoAchouPosicao = (k > 0);  // Se n for maior que 0, então entra no laço:

    while(NaoAchouPosicao){
        if(x >= (*D)->btkeys[k - 1]){
            NaoAchouPosicao = 0;
            break;
        }
        (*D)->btkeys[k] = (*D)->btkeys[k - 1];
        (*D)->childs[k + 1] = (*D)->childs[k];
        k--;
        if(!k) NaoAchouPosicao = 0;
    }

    (*D)->btkeys[k] = x;
    (*D)->childs[k + 1] = *PonteiroDir;
    (*D)->n++;

}

//############################modificando
void insert(int x, TipoPagina *D, int *cresceu, int *RegRetorno, TipoPagina **PonteiroRetorno){
    printf("insert, entra na função\n");
    int i, j;
    TipoPagina *PonteiroTemp;

    printf("insert, antes primeiro if\n");
    if(D == NULL){       // Entra aqui na primeira inserção do programa.
        printf("insert, no primeiro if\n");
        *cresceu = 1;            // Pois era nulo na primeira vez
        *RegRetorno = x;         // Retorna pra função insereo único valor que existe até agora
        (*PonteiroRetorno) = NULL; // Não tem ponteiros para filhos (não existem filhos)
        return;
    }
    printf("insert, depois primeiro if\n");

    for(i = 1; i < (*D).n && x > (*D).btkeys[i - 1]; i++); // Enconta a posição para guardar o novo registro

    printf("insert, antes segundo if, i: %d\n", i);
    printf("    informação (i-1): %d", (*D).btkeys[i-1]);
    if(x == (*D).btkeys[i - 1]){   // Quer dizer que o valor já existia na árvore
        printf("insert, no segundo if\n");
        printf("ERRO");                 // Indica erro
        *cresceu = 0;                    // Obviamente não há cresciemnto na árvore
        return;                         // Acabou a função por que não há nada a ser feito
    }
    printf("insert, depois segundo if\n");

    if(x < (*D).btkeys[i - 1]){
        i--;    // Faz isso para chamar recursivamente o ponteiro da
        printf("    ifzinho\n");
    }                            // esquerda (menores) se for o caso.

    printf("insert, antes recurssao %p\n", (*D).childs[i]);
    insert(x, (*D).childs[i], cresceu, RegRetorno, &(*PonteiroRetorno));    //Faz a chamada recursiva

    if(!*cresceu) return;   // Saiu da recursão sem cresciemnto tá de boas

    // Se houve crescimento, segue abaixo:

    printf("insert, antes terceiro if\n");
    if((*D).n < ordem){                                // Significa que a página tem espaço, portanto inserenela;
        printf("insert, no terceiro if\n");
        InsereNaPagina(&D, *RegRetorno, &(*PonteiroRetorno)); // chama a função que insereefetivamente
        cresceu = 0;                                        // Não houve crescimento por que tinha espaço.
        return;
    }
    printf("insert, depois terceiro if\n");

    // else
    // Overflow: Pagina tem que ser dividida ############### CONFUSA
    PonteiroTemp = newPage();
    PonteiroTemp->n = 0;
    PonteiroTemp->childs[0] = NULL;

    printf("insert, antes quarto if\n");
    printf("AQUIIIIIIII %d\n", (*D).n);
    if(i < T + 1){
        printf("insert, no quarto if\n");
        InsereNaPagina(&PonteiroTemp, *RegRetorno, &(*PonteiroRetorno));
        (*D).n--;
        InsereNaPagina(&D, *RegRetorno, &(*PonteiroRetorno));
    }
    else{
        printf("insert, no else\n");
        InsereNaPagina(&PonteiroTemp, *RegRetorno, &(*PonteiroRetorno));
    }
    printf("insert, depois do else\n");

    for(j = ordem/2 + 2; j <= ordem; j++){
        printf("insert, no for\n");
        InsereNaPagina(&PonteiroTemp, (*D).btkeys[j - 1], &(*D).childs[j]);
    }
    printf("insert, depois do for\n");

    (*D).n = ordem/2;
    PonteiroTemp->childs[0] = (*D).childs[ordem/2+1];
    *RegRetorno = (*D).btkeys[ordem/2];
    PonteiroRetorno = &PonteiroTemp;
}

void insere(int x, TipoPagina **D){
    int cresceu = 0;
    int RegRetorno;                             // Retorna o registro que vai ser passado pra cima
    TipoPagina *PonteiroRetorno, *PonteiroTemp; // só se usam para obter retorno da insert

    printf("insere, antes recurssão\n");
    // ################################# Ver questão do tipo de ponteiro para passagem do d abaixo:
    insert(x, *D, &cresceu, &RegRetorno, &PonteiroRetorno);
    printf("insere, depois recurssão\n");

    if(cresceu){                                // No momento do retorno do procedimento insert para o
                                                // procedimento inseresignifica que a página raiz foi dividida e
                                                // então uma nova página raiz deve ser criada para acomodar o registro
                                                // emergente, fazendo com que a árvore cresca na altura
        printf("insere, if cresceu\n");
        PonteiroTemp = newPage();                   // Alocação temporária
        PonteiroTemp->n = 1;                        // É 1 por que subiu só 1 no split (sempre)
        PonteiroTemp->btkeys[0] = RegRetorno;       // É o registro que subiu no split
        PonteiroTemp->childs[1] = PonteiroRetorno;  // Ponteiro para os maiores em relação à RegRetorno
        PonteiroTemp->childs[0] = *D;             // Ponteiro para os menores em relação à RegRetorno
        *D = PonteiroTemp;                        // Raiz recebe as informações montadas no temporário
    }
    printf("insere, fim função\n");

}

void imprime(TipoPagina *D, int level){
    if(D == NULL) return;
    printf("Nível: %d:", level);
    for(int i = 0; i < D->n; i++) printf("%d ", D->btkeys[i]);
    putchar('\n');
    level++;
    for(int i = 0; i <= D->n; i++) imprime(D->childs[i], level);
}


int main(int argc, char const *argv[]) {
    int x;
    TipoPagina *D = NULL;

    printf("Chave: "); scanf("%d", &x);

    while(x != 0){
        insere(x, &D);
        imprime(D, 0);

        printf("Chave: "); scanf("%d", &x);
    }

    return 0;
}
