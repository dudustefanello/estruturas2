#include <stdio.h>
#include <stdlib.h>

#define T 2
#define ORDEM (T * 2)

typedef struct TipoRegistro{
    int chave;
} TipoRegistro;

typedef struct TipoPagina* TipoPonteiro;

typedef struct TipoPagina{
    TipoRegistro *registros;
    TipoPonteiro *ponteiros;
    short         quantidade;
} TipoPagina;

TipoPagina *Alocacao(){
    TipoPagina *auxiliar = (TipoPagina *)
        calloc(1, sizeof(TipoPagina));

    auxiliar->registros  = (TipoRegistro *)
        calloc(ORDEM, sizeof(TipoRegistro));
    auxiliar->ponteiros  = (TipoPonteiro *)
        calloc(ORDEM + 1, sizeof(TipoPagina));

    return auxiliar;
}

void InsereRegistro(
        TipoRegistro registro,
        TipoPonteiro ponteiro,
        TipoPonteiro ponteiroDireita){

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

void InserePagina(
        TipoRegistro  registro,
        TipoRegistro *registroRetorno,
        TipoPonteiro  ponteiro,
        TipoPonteiro *ponteiroRetorno,
        short        *cresceu){

    int i;

    if(ponteiro == NULL){
        *cresceu         = 1;
        *registroRetorno = registro;
        *ponteiroRetorno = NULL;
        return;
    }
//////////////////////////////////////////////////////////////////////

    i = 1;
    while(i < ponteiro->quantidade && registro.chave > ponteiro->registros[i-1].chave){
        i++;
    }

    if (registro.chave == ponteiro->registros[i-1].chave){
        printf(" Erro: Registro ja esta presente\n");
        *cresceu = 0;
        return;
    }

    if (registro.chave < ponteiro->registros[i-1].chave){
        i--;
    }

    InserePagina(registro, registroRetorno, ponteiro->ponteiros[i], ponteiroRetorno, cresceu);

    if (!*cresceu){
        return;
    }

    if (ponteiro->quantidade < ORDEM){/* Pagina tem espaco */
        InsereRegistro(*registroRetorno, ponteiro, *ponteiroRetorno);
        *cresceu = 0;
        return;
    }

    /* Overflow: Pagina tem que ser dividida */
    TipoPonteiro ponteiroTemporario = Alocacao();

    if (i < T + 1){
        InsereRegistro(ponteiro->registros[ORDEM-1], ponteiroTemporario, ponteiro->ponteiros[ORDEM]);
        ponteiro->quantidade--;
        InsereRegistro(*registroRetorno, ponteiro, *ponteiroRetorno);
    }

    else{
        InsereRegistro(*registroRetorno, ponteiroTemporario, *ponteiroRetorno);
    }

    for(int j = T + 2; j <= ORDEM; j++){
        InsereRegistro(ponteiro->registros[j-1], ponteiroTemporario, ponteiro->ponteiros[j]);
    }

    ponteiro->quantidade = T;
    ponteiroTemporario->ponteiros[0] = ponteiro->ponteiros[T+1];
    *registroRetorno = ponteiro->registros[T];
    *ponteiroRetorno = ponteiroTemporario;
}

void Insere(TipoRegistro registro, TipoPonteiro *Ponteiro){
    short Cresceu;
    TipoRegistro RegRetorno;
    TipoPagina *PonteiroRetorno;

    InserePagina(registro, &RegRetorno, *Ponteiro, &PonteiroRetorno, &Cresceu);

    if (Cresceu){ /* Arvore cresce na altura pela raiz */
        TipoPagina *PonteiroTemp  = Alocacao();
        PonteiroTemp->quantidade = 1;
        PonteiroTemp->registros[0] = RegRetorno;
        PonteiroTemp->ponteiros[1] = PonteiroRetorno;
        PonteiroTemp->ponteiros[0] = *Ponteiro;
        *Ponteiro = PonteiroTemp;
    }
}

void ImprimeI(TipoPonteiro p, int nivel){
    int i;
    if (p == NULL) return;

    for(int i = 0; i < nivel; i++)
        printf("    ");
    printf("Nivel %d : ", nivel);

    for (i = 0; i < p->quantidade; i++)
        printf("%d ",(int)p->registros[i].chave);
    putchar('\n');

    nivel++;

    for (i = 0; i <= p->quantidade; i++)
        ImprimeI(p->ponteiros[i], nivel);
}

int main(int argc, char *argv[]){
    TipoRegistro x;
    TipoPagina *D = NULL;

    printf("chave: "); scanf("%d%*[^\n]", &x.chave);

    while (x.chave != 0){
        Insere(x, &D);
        ImprimeI(D,0);

        printf("chave: "); scanf("%d%*[^\n]", &x.chave);
    }

    return 0;
}
