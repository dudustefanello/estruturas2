/*  Título:
    TRABALHO 4 – ESTRUTURA DE DADOS II

    Descrição:
    Implementar (em linguagem C) um programa que permita cadastrar produtos ou
    listar produtos cadastrados. Cada produto contém pelo menos um código, nome
    e preço. A cada produto cadastrado ele é gravado em arquivo. Quando o
    usuário deseja ler as informações que já foram gravadas, é feita a leitura
    do arquivo. Quem quiser explorar mais a atividade para fins de aprendizagem,
    pode ficar a vontade.

    Autor: Eduardo Stefanello
    Data: 30 de Junho de 2017
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void novo(int codigo, char nome[], float preco){
    char nomeArquivo1[20];
    char nomeArquivo2[20];
    sprintf(nomeArquivo1, "dados/%i.txt", codigo);
    sprintf(nomeArquivo2, "%i.txt", codigo);

    FILE *index = fopen("dados/index.txt", "a");
    FILE *arquivo = fopen(nomeArquivo1, "w");

    fprintf(index, "%s\n", nomeArquivo1);

    fprintf(arquivo, "Código: %d\nNome:   %s\nValor:  R$ %.2f\n", codigo, nome, preco);

    fclose(arquivo);
    fclose(index);
}

void imprime(char endereco[]){
    char info[30];
    if(strlen(endereco) < 8) return;
    FILE *arquivo = fopen(endereco, "r");
    if(arquivo == NULL){
        printf("Erro2: %s\n", endereco);
        return;
    }

    else while((fgets(info, sizeof(info), arquivo)) != NULL){
        printf("%s", info);
    }
    printf("\n");
    fclose(arquivo);
}

void mostrar(){
    FILE *index = fopen("dados/index.txt", "r");
    char linhaIndice[15];
    if(index == NULL){
        printf("Erro1\n");
        return;
    }
    else while((fgets(linhaIndice, sizeof(linhaIndice), index)) != NULL){
            imprime(linhaIndice);
    }
    fclose(index);
}

int codigo(char nome[]){
    int codigo = 0;
    codigo += (nome[0] - 48) * 1;
    codigo += (nome[1] - 48) * 10;
    codigo += (nome[2] - 48) * 100;
    return codigo;
}

int main() {
    char nome[20];
    float preco;

    short a = 1;

    while(a){
        short option;

        printf("(1) Cadastrar Novo\n");
        printf("(2) Mostrar Produtos\n");
        printf("(3) Sair\n");
        scanf("%hi", &option);
        switch(option){
            case 1:
                printf("  Nome: "); scanf("%s", nome);
                printf(" Valor: "); scanf("%f", &preco);
                getchar();
                novo(codigo(nome), nome, preco);
                break;
            case 2:
                mostrar();
                break;
            default:
                a = 0;
                return 0;
        }
    }
    return 0;
}
