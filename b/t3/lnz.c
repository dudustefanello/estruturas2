void Reconstitui(TipoPonteiro PonteiroPag, TipoPonteiro PonteiroPai,int PosPai, short *Diminuiu){
    TipoPagina *Aux;  int DispAux, j;
        if (PosPai < PonteiroPai->n){  /* Aux = TipoPagina a direita de PonteiroPag */
            Aux = PonteiroPai->p[PosPai+1];  DispAux = (Aux->n - M + 1) / 2;
            PonteiroPag->r[PonteiroPag->n] = PonteiroPai->r[PosPai];
            PonteiroPag->p[PonteiroPag->n + 1] = Aux->p[0];  PonteiroPag->n++;
            if (DispAux > 0){  /* Existe folga: transfere de Aux para PonteiroPag */
                for (j = 1; j < DispAux; j++) InsereNPonteiroPagina(PonteiroPag, Aux->r[j-1], Aux->p[j]);
                PonteiroPai->r[PosPai] = Aux->r[DispAux-1];  Aux->n -= DispAux;
                for (j = 0; j < Aux->n; j++) Aux->r[j] = Aux->r[j + DispAux];
                for (j = 0; j <= Aux->n; j++) Aux->p[j] = Aux->p[j + DispAux];
                *Diminuiu = FALSE;
            }
            else /* Fusao: intercala Aux em PonteiroPag e libera Aux */
            { for (j = 1; j <= M; j++)    InsereNPonteiroPagina(PonteiroPag, Aux->r[j-1], Aux->p[j]);
                free(Aux);
                for (j = PosPai + 1; j < PonteiroPai->n; j++)    { PonteiroPai->r[j-1] = PonteiroPai->r[j];
                    PonteiroPai->p[j] = PonteiroPai->p[j+1];
                }
                PonteiroPai->n--;
                if (PonteiroPai->n >= M) *Diminuiu = FALSE;
            }
        }
        else /* Aux = TipoPagina a esquerda de PonteiroPag */
        { Aux = PonteiroPai->p[PosPai-1]; DispAux = (Aux->n - M + 1) / 2;
            for (j = PonteiroPag->n; j >= 1; j--) PonteiroPag->r[j] = PonteiroPag->r[j-1];
            PonteiroPag->r[0] = PonteiroPai->r[PosPai-1];
            for (j = PonteiroPag->n; j >= 0; j--) PonteiroPag->p[j+1] = PonteiroPag->p[j];
            PonteiroPag->n++;
            if (DispAux > 0) /* Existe folga: transf. de Aux para PonteiroPag */
            { for (j = 1; j < DispAux; j++)    InsereNPonteiroPagina(PonteiroPag, Aux->r[Aux->n - j],
                Aux->p[Aux->n - j + 1]);
                PonteiroPag->p[0] = Aux->p[Aux->n - DispAux + 1];
                PonteiroPai->r[PosPai-1] = Aux->r[Aux->n - DispAux];
                Aux->n -= DispAux;  *Diminuiu = FALSE;
            }
            else /* Fusao: intercala PonteiroPag em Aux e libera PonteiroPag */
            { for (j = 1; j <= M; j++)InsereNPonteiroPagina(Aux, PonteiroPag->r[j-1], PonteiroPag->p[j]);
                free(PonteiroPag);  PonteiroPai->n--;
                if (PonteiroPai->n >= M)  *Diminuiu = FALSE;
            }
        }
    }

    void Antecessor(TipoPonteiro Ponteiro, int Ind,
        TipoPonteiro PonteiroPai, short *Diminuiu){ if (PonteiroPai->p[PonteiroPai->n] != NULL)    { Antecessor(Ponteiro, Ind, PonteiroPai->p[PonteiroPai->n], Diminuiu);
            if (*Diminuiu)Reconstitui(PonteiroPai->p[PonteiroPai->n], PonteiroPai, (int)PonteiroPai->n, Diminuiu);
            return;
        }
        Ponteiro->r[Ind-1] = PonteiroPai->r[PonteiroPai->n - 1];
        PonteiroPai->n--;  *Diminuiu = (PonteiroPai->n < M);
    }

    void Ret(int Ch, TipoPonteiro *Ponteiro, short *Diminuiu){ int j, Ind = 1;
        TipoPonteiro Pag;
        if (*Ponteiro == NULL)    { printf("Erro: registro nao esta na arvore\n"); *Diminuiu = FALSE;
        return;
    }
    Pag = *Ponteiro;
    while (Ind < Pag->n && Ch > Pag->r[Ind-1].Chave) Ind++;
    if (Ch == Pag->r[Ind-1].Chave){ if (Pag->p[Ind-1] == NULL)   /* TipoPagina folha */
        { Pag->n--;
            *Diminuiu = (Pag->n < M);
            for (j = Ind; j <= Pag->n; j++){ Pag->r[j-1] = Pag->r[j];  Pag->p[j] = Pag->p[j+1]; }
            return;
        }
        /* TipoPagina nao e folha: trocar com antecessor */
        Antecessor(*Ponteiro, Ind, Pag->p[Ind-1], Diminuiu);
        if (*Diminuiu)    Reconstitui(Pag->p[Ind-1], *Ponteiro, Ind - 1, Diminuiu);
        return;
    }
    if (Ch > Pag->r[Ind-1].Chave) Ind++;
    Ret(Ch, &Pag->p[Ind-1], Diminuiu);
    if (*Diminuiu) Reconstitui(Pag->p[Ind-1], *Ponteiro, Ind - 1, Diminuiu);
}

void Retira(int Ch, TipoPonteiro *Ponteiro){
    short Diminuiu;
    TipoPonteiro Aux;
    Ret(Ch, Ponteiro, &Diminuiu);
    if (Diminuiu && (*Ponteiro)->n == 0)  /* Arvore diminui na altura */
    { Aux = *Ponteiro;   *Ponteiro = Aux->p[0];
        free(Aux);
    }
}

void Pesquisa(TipoRegistro *x, TipoPonteiro Ponteiro){
    int i = 1;
    if (Ponteiro == NULL){
        printf("TipoRegistro nao esta presente na arvore\n");
        return;
    }
    while (i < Ponteiro->n && x->Chave > Ponteiro->r[i-1].Chave) i++;
    if (x->Chave == Ponteiro->r[i-1].Chave){
        *x = Ponteiro->r[i-1];
        return;
    }
    if (x->Chave < Ponteiro->r[i-1].Chave)Pesquisa(x, Ponteiro->p[i-1]);
    else Pesquisa(x, Ponteiro->p[i]);
}

void TestaI(TipoPonteiro p, int pai, short direita){
    int i;
    int antecessor = 0;
    if (p == NULL) return;
    if (p->r[0].Chave > pai && direita == FALSE){
        printf("Erro: filho %12d maior que pai %d\n", p->r[0].Chave, pai);
        return;
    }
    for (i = 0; i < p->n; i++){
        if (p->r[i].Chave <= antecessor){
            printf("Erro: irmao %d maior que irmao a esquerda %d\n",
            (int)p->r[i].Chave, antecessor);
            return;
        }
        antecessor = p->r[i].Chave;
    }
    for (i = 0; i < p->n; i++)TestaI(p->p[i], p->r[i].Chave, FALSE);
    TestaI(p->p[p->n], p->r[i].Chave, TRUE);
}

void Testa(TipoPonteiro p){
    int i;
    if (p == NULL) return;
    for (i = 0; i < p->n; i++)TestaI(p->p[i], p->r[i].Chave, FALSE);
    TestaI(p->p[p->n], p->r[i].Chave, TRUE);
}
