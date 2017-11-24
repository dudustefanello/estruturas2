/*  Título:
    TRABALHO 3 – ESTRUTURA DE DADOS II

    Descrição:
    Implementar (em linguagem C) uma Árvore B que possui como chave
    valores inteiros positivos não repetidos. A cada novo nó inserido
    devem ser mantidas as propriedades da árvore.

    Autor: Eduardo Stefanello
    Data: 1 de Julho de 2017
*/

// Inclusão dos cabeçalhos
#include <stdio.h>
#include <stdlib.h>

// Variáveis globais para T e Ordem
short ORDEM;
short T;

/*  Tipo de Dados para o registro
    Nesse programa foi utilizado apenas um inteiro,
    mas pode ser inserido qualquer tipo de dado
    na árvore através dessa estrutura
*/
typedef struct TipoRegistro{
    int chave;
} TipoRegistro;

// Tipo de Ponteiro para a estrutura da página
//typedef struct TipoPagina* TipoPonteiro;

typedef struct TipoPagina{
    TipoRegistro       *registros;
    struct TipoPagina **ponteiros;
    short               quantidade;
} TipoPagina;

TipoPagina *alocacao(){
    TipoPagina *auxiliar = (TipoPagina *)
        calloc(1, sizeof(TipoPagina));

    auxiliar->registros  = (TipoRegistro *)
        calloc(ORDEM, sizeof(TipoRegistro));
    auxiliar->ponteiros  = (TipoPagina **)
        calloc(ORDEM + 1, sizeof(TipoPagina));

    return auxiliar;
}

void insereRegistro(
        TipoRegistro registro,
        TipoPagina  *ponteiro,
        TipoPagina  *ponteiroDireita){

    int   i    = ponteiro->quantidade;
    short flag = (i > 0);

    while(flag){
        if(registro.chave >= ponteiro->registros[i - 1].chave){
            flag = 0;
            break;
        }

        ponteiro->registros[i]     = ponteiro->registros[i - 1];
        ponteiro->ponteiros[i + 1] = ponteiro->ponteiros[i];
        i--;

        if(i < 1) flag = 0;
    }

    ponteiro->registros[i]     = registro;
    ponteiro->ponteiros[i + 1] = ponteiroDireita;
    ponteiro->quantidade++;
}

void inserePagina(
        TipoRegistro  registro,
        TipoRegistro *registroRetorno,
        TipoPagina   *ponteiro,
        TipoPagina   **ponteiroRetorno,
        short        *cresceu){

    int i;

    if(ponteiro == NULL){
        *cresceu         = 1;
        *registroRetorno = registro;
        *ponteiroRetorno = NULL;
        return;
    }

    for(i = 1;
        i < ponteiro->quantidade &&
        registro.chave > ponteiro->registros[i - 1].chave;
        i++);

    if(registro.chave == ponteiro->registros[i - 1].chave){
        //printf(" Erro: Registro ja esta presente\n");
        *cresceu = 0;
        return;
    }

    if(registro.chave < ponteiro->registros[i - 1].chave) i--;

    inserePagina(
            registro,
            registroRetorno,
            ponteiro->ponteiros[i],
            ponteiroRetorno,
            cresceu);

    if(!*cresceu) return;

    if(ponteiro->quantidade < ORDEM){
        insereRegistro(
                *registroRetorno,
                 ponteiro,
                *ponteiroRetorno);
        *cresceu = 0;
        return;
    }

    TipoPagina *ponteiroTemporario = alocacao();

    if(i < T + 1){
        insereRegistro(
                ponteiro->registros[ORDEM - 1],
                ponteiroTemporario,
                ponteiro->ponteiros[ORDEM]);
        ponteiro->quantidade--;
        insereRegistro(
                *registroRetorno,
                 ponteiro,
                *ponteiroRetorno);
    }
    else{
        insereRegistro(
                *registroRetorno,
                 ponteiroTemporario,
                *ponteiroRetorno);
    }

    for(int j = T + 2; j <= ORDEM; j++)
        insereRegistro(
                ponteiro->registros[j - 1],
                ponteiroTemporario,
                ponteiro->ponteiros[j]);

    ponteiro->quantidade = T;
    ponteiroTemporario->ponteiros[0] = ponteiro->ponteiros[T + 1];
    *registroRetorno = ponteiro->registros[T];
    *ponteiroRetorno = ponteiroTemporario;
}

void insere(
        TipoRegistro   registro,
        TipoPagina   **ponteiro){

    short cresceu;
    TipoRegistro  registroRetorno;
    TipoPagina   *ponteiroRetorno;

    inserePagina(
             registro,
            &registroRetorno,
            *ponteiro,
            &ponteiroRetorno,
            &cresceu);

    if(cresceu){
        TipoPagina *ponteiroTemporario   =  alocacao();
        ponteiroTemporario->quantidade   =  1;
        ponteiroTemporario->registros[0] =  registroRetorno;
        ponteiroTemporario->ponteiros[1] =  ponteiroRetorno;
        ponteiroTemporario->ponteiros[0] = *ponteiro;
        *ponteiro = ponteiroTemporario;
    }
}

void imprime(
        TipoPagina *ponteiro,
        int          nivel){

    if (ponteiro == NULL) return;

    for(int i = 0; i < nivel; i++)
        printf("    ");
    printf("Nivel %d: ", nivel);

    for (int i = 0; i < ponteiro->quantidade; i++)
        printf("%d ",(int)ponteiro->registros[i].chave);
    putchar('\n');

    nivel++;

    for (int i = 0; i <= ponteiro->quantidade; i++)
        imprime(ponteiro->ponteiros[i], nivel);
}

int main(int argc, char const *argv[]) {

    printf("Informe o T a ser utilizado: ");
    scanf("%hd", &T);
    ORDEM = T * 2;

    TipoRegistro registro;
    TipoPagina  *ponteiro = NULL;

    printf("Chave: "); scanf("%d%*[^\n]", &registro.chave);

    imprime(ponteiro, 0);

    while (registro.chave != 0){
        insere(registro, &ponteiro);
        imprime(ponteiro, 0);

        printf("Chave: "); scanf("%d%*[^\n]", &registro.chave);
    }

    return 0;
}
