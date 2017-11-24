#include<stdlib.h>
    #include<stdio.h>

#define M 2
    #define MM  (M * 2)
    #define FALSE 0
    #define TRUE  1

typedef struct TipoRegistro{
    int Chave;
    /*outros componentes*/
} TipoRegistro;

typedef struct TipoPagina* TipoPonteiro;

typedef struct TipoPagina{
    short n;
    TipoRegistro r[MM];
    TipoPonteiro p[MM + 1];
} TipoPagina;


void InsereNPonteiroPagina(TipoPonteiro Ponteiro, TipoRegistro Reg,
        TipoPonteiro PonteiroDir){

            int k = Ponteiro->n;
            short NaoAchouPosicao = (k > 0);

    while (NaoAchouPosicao){
        if (Reg.Chave >= Ponteiro->r[k-1].Chave){
            NaoAchouPosicao = FALSE;
            break;
        }
        Ponteiro->r[k] = Ponteiro->r[k-1];
        Ponteiro->p[k+1] = Ponteiro->p[k];
        k--;
        if (k < 1) NaoAchouPosicao = FALSE;
    }
    Ponteiro->r[k] = Reg;
    Ponteiro->p[k+1] = PonteiroDir;
    Ponteiro->n++;
}

void Ins(TipoRegistro Reg, TipoPonteiro Ponteiro, short *Cresceu,
            TipoRegistro *RegRetorno,  TipoPonteiro *PonteiroRetorno){
    int i = 1;
    int j;
    TipoPonteiro PonteiroTemp;

    if (Ponteiro == NULL){
        printf("é nulo\n");
        *Cresceu = TRUE;
        (*RegRetorno) = Reg;
        (*PonteiroRetorno) = NULL;
        return;
    }

    while(i < Ponteiro->n && Reg.Chave > Ponteiro->r[i-1].Chave){
        i++;
    }

    if (Reg.Chave == Ponteiro->r[i-1].Chave){
        printf(" Erro: Registro ja esta presente\n");
        *Cresceu = FALSE;
        return;
    }

    if (Reg.Chave < Ponteiro->r[i-1].Chave){
        i--;
    }

    Ins(Reg, Ponteiro->p[i], Cresceu, RegRetorno, PonteiroRetorno);

    if (!*Cresceu){
        return;
    }

    if (Ponteiro->n < MM){/* Pagina tem espaco */
        InsereNPonteiroPagina(Ponteiro, *RegRetorno, *PonteiroRetorno);
        *Cresceu = FALSE;
        return;
    }

    /* Overflow: Pagina tem que ser dividida */
    PonteiroTemp = (TipoPonteiro)malloc(sizeof(TipoPagina));
    PonteiroTemp->n = 0;
    PonteiroTemp->p[0] = NULL;

    if (i < M + 1){
        InsereNPonteiroPagina(PonteiroTemp, Ponteiro->r[MM-1], Ponteiro->p[MM]);
        Ponteiro->n--;
        InsereNPonteiroPagina(Ponteiro, *RegRetorno, *PonteiroRetorno);
    }

    else{
        InsereNPonteiroPagina(PonteiroTemp, *RegRetorno, *PonteiroRetorno);
    }

    for(j = M + 2; j <= MM; j++){
        InsereNPonteiroPagina(PonteiroTemp, Ponteiro->r[j-1], Ponteiro->p[j]);
    }

    Ponteiro->n = M;
    PonteiroTemp->p[0] = Ponteiro->p[M+1];
    *RegRetorno = Ponteiro->r[M];
    *PonteiroRetorno = PonteiroTemp;
}

void Insere(TipoRegistro Reg, TipoPonteiro *Ponteiro){
    short Cresceu;
    TipoRegistro RegRetorno;
    TipoPagina *PonteiroRetorno;

    Ins(Reg, *Ponteiro, &Cresceu, &RegRetorno, &PonteiroRetorno);

    if (Cresceu){ /* Arvore cresce na altura pela raiz */
        TipoPagina *PonteiroTemp = (TipoPagina *)malloc(sizeof(TipoPagina));
        PonteiroTemp->n = 1;
        PonteiroTemp->r[0] = RegRetorno;
        PonteiroTemp->p[1] = PonteiroRetorno;
        PonteiroTemp->p[0] = *Ponteiro;
        *Ponteiro = PonteiroTemp;
    }
}

void ImprimeI(TipoPonteiro p, int nivel){
    int i;
    if (p == NULL) return;

    for(int i = 0; i < nivel; i++)
        printf("    ");
    printf("Nivel %d : ", nivel);

    for (i = 0; i < p->n; i++)
        printf("%d ",(int)p->r[i].Chave);
    putchar('\n');

    nivel++;

    for (i = 0; i <= p->n; i++)
        ImprimeI(p->p[i], nivel);
}

int main(int argc, char *argv[]){
    TipoRegistro x;
    TipoPagina *D = NULL;

    printf("Chave: "); scanf("%d%*[^\n]", &x.Chave);

    while (x.Chave != 0){
        Insere(x, &D);
        ImprimeI(D,0);

        printf("Chave: "); scanf("%d%*[^\n]", &x.Chave);
    }

    return 0;
}
