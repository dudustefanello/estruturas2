/*  Título:
    TRABALHO 3 – ESTRUTURA DE DADOS II

    Descrição:
    Implementar (em linguagem C) uma Árvore B que possui como chave
    valores inteiros positivos não repetidos. A cada novo nó
    inserido devem ser mantidas as propriedades da árvore.

    Autor: Eduardo Stefanello
    Data:  7 de Junho de 2017
    Referência:
        ZIVIANI, N.
        Projeto de Algoritmos com Implementações Pascal e C. 2. ed.
        São Paulo: Thomson Pioneira, 2004
*/

// Inclusão dos cabeçalhos
#include <stdio.h>
#include <stdlib.h>

// Variáveis constantes para Ordem e T
short ORDEM;    // Quantidade máxima de registros (ORDEM + 1 para filhos)
short T;        // Quantidade mínima de registros (T + 1 para filhos)

// Tipo genérico para os dados de registro
typedef struct TipoRegistro{
    int chave;
} TipoRegistro;

// Tipo ponteiro para a estrutura
typedef struct TipoPagina* TipoPonteiro;

/*  Estrutura de dados base
        Contém:
            - Ponteiro para o registros
            - Ponteiro para o ponteiro para a estrutura (duplo)
            - Indicador de Quantidade de registros na página
        Foram utilizado ponteiros para poder ser usada a
        alocação dinâmica, diferente da implementação da referência,
        que usa implementação do tamanho diretamente dentro da estrutura
    */
typedef struct TipoPagina{
    TipoRegistro *registros;
    TipoPonteiro *ponteiros;
    short         quantidade;
} TipoPagina;

void continua(){
    char ch = 0;
    do{
        printf("Pressione ENTER para continuar...");
        getchar();
        ch = getchar();
    }while(ch != 10);
}

/*  Função de Alocação
        Função que retorna um espaço alocado para uma nova página
        Faz a alocação dos vetores de registros e de ponteiros
        (filhos) com base na ordem;
    */
TipoPagina *alocacao(){
    TipoPagina *auxiliar = (TipoPagina *)
        calloc(1, sizeof(TipoPagina));

    auxiliar->registros  = (TipoRegistro *)
        calloc(ORDEM, sizeof(TipoRegistro));
    auxiliar->ponteiros  = (TipoPonteiro *)
        calloc(ORDEM + 1, sizeof(TipoPagina));

    return auxiliar;
}

void insereRegistro(
        TipoRegistro registro,          // Inserir este registro
        TipoPonteiro ponteiro,          // neste endereço
        TipoPonteiro ponteiroDireita){  // com este filho à direita

    int i = ponteiro->quantidade;

    while(i > 0){
        if(registro.chave > ponteiro->registros[i - 1].chave){
            /*  Encontrou a posição de inserção
                */
            break;
        }

        /*  Se o registro for menor que a posição i-1,
            então se faz um deslocamento do vetor a partir desta posição
            e então vai testando-se os anteriores (decremento de i e laço)
            */
        ponteiro->registros[i]     = ponteiro->registros[i - 1];
        ponteiro->ponteiros[i + 1] = ponteiro->ponteiros[i];
        i--;
    }

    /*  Com a posição encontrada e feitos os devidos deslocamentos
        é inserido o registro e o filho à direita na página
        e aumentada a quantidade
        */
    ponteiro->registros[i]     = registro;
    ponteiro->ponteiros[i + 1] = ponteiroDireita;
    ponteiro->quantidade++;
}

void inserePagina(
        TipoRegistro  registro,
        TipoRegistro *registroRetorno,
        TipoPonteiro  ponteiro,
        TipoPonteiro *ponteiroRetorno,
        short        *cresceu){

    if(ponteiro == NULL){
        /*  Encontrou um ponteiro nulo:
            Página é folha
                - seta a flag de cresimento
                - retorna o próprio registro com filho nulo
            */
        *cresceu         = 1;
        *registroRetorno = registro;
        *ponteiroRetorno = NULL;
        return;
    }

    //  Página contém valores

    // Encontra a posição para o novo registro
    int i;
    for(i = 1;
        i < ponteiro->quantidade && // não estourar o acesso
        registro.chave > ponteiro->registros[i - 1].chave;
        i++);

    if(registro.chave == ponteiro->registros[i - 1].chave){
        /*  Impressão do erro de registro repetido
            Um registro com a mesma chave já está na página;
                Neste ponto poderia ser implementado uma lista encadeada
                para não impedir a inserção de valores repetidos, e este
                acontecer na mesma página e posição, o que seria mais útil
                caso a chave fosse um valor Hash
            */
        printf(" Erro: Registro ja esta presente\n");
        continua();
        *cresceu = 0;
        return;
    }

    /*  Decremento opcional do i
            Decrementa se o novo registro for adicionado no meio da página.
            Se for adicionado ao final da página, será adicionado onde já
            tem um valor nulo, aí não precisa decrementar;
        */
    if(registro.chave < ponteiro->registros[i - 1].chave) i--;

    // Chama recursivamente a função de inserção na página, passando o filho
    inserePagina(
            registro,
            registroRetorno,
            ponteiro->ponteiros[i],
            ponteiroRetorno,
            cresceu);

    // Não houve crescimento, fim da execução
    if(!*cresceu) return;

    // Filho no intervalo de inserção do valor é nulo

    if(ponteiro->quantidade < ORDEM){
        /*  insere um novo registro na mesma página
            considerando que tem espaço nela (sua quantidade interna é
            menor que a ordem)
                Após a insersão, retorna com flag cresceu = 0,
                já que tendo espaço, não é necessário mexer na estrutura
                da árvore
            */
        insereRegistro(
                *registroRetorno,
                 ponteiro,
                *ponteiroRetorno);
        *cresceu = 0;
        return;
    }

    // Não há espaço para inserir na página

    // Alocação de um novo ponteiro
    TipoPonteiro ponteiroTemporario = alocacao();

    /*  Se a posição encontrada para inserir estiver antes da metade a nova
        página vai receber o último registro (junto com respectivos filhos),
        sua quantidade de filhos vai diminuir e o ponteiro vai receber o
        ponteiro para o registro de retorno.
        Se estiver depois da metade, o ponteiro vai receber um ponteiro para
        registro de retorno
        */
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

    /*  Laço que percorre o ponteiro de posição em posição, inserindo os dados
        no ponteiro temporario.
        */
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

/*  Função de Inserção I
    Função de base do processo de Inserção;
        Esta função é responsável pela execução do processo de "Promote" na
        raiz, por que recebe (por referência) o valor a ser promovido e seus
        dois filhos (direita e esquerda).
    */
void insere(
        TipoRegistro  registro,         // Recebe o registro a ser inserdo
        TipoPonteiro *ponteiro){        // Recebe o ponteiro da raiz

    short cresceu;                      // Usados na chamada da próxima função
    TipoRegistro  registroRetorno;      // para retornar indicadores de estado
    TipoPagina   *ponteiroRetorno;      // e valores para serem manipulados

    inserePagina(
             registro,                  // Novo registro para a árvore
            &registroRetorno,           // Registro a ser promovido
            *ponteiro,                  // Raiz da árvore
            &ponteiroRetorno,           // Ponteiro para nó de valores maiores
            &cresceu);                  // Indicador de necessidade de Promote

    if(cresceu){
        /*  Algoritmo de promoção do valor indicado pela função inserePagina,
            utilizando os devidos retornos para a organização dos filhos;
                - Cria um novo nó (com alocação dinâmica)
                - Seta as informações necessárias, antiga raiz é filho à
                  esquerda [mesma posição nos vetores]
                - Raiz passa e ser o ponteiro alocado.
            */
        TipoPagina *ponteiroTemporario   =  alocacao();
        ponteiroTemporario->quantidade   =  1;
        ponteiroTemporario->registros[0] =  registroRetorno;
        ponteiroTemporario->ponteiros[1] =  ponteiroRetorno;
        ponteiroTemporario->ponteiros[0] = *ponteiro;
        *ponteiro = ponteiroTemporario;
    }
}

/*  Função de Impressão da Árvore
        Faz a Impressão em pré-ordem:
            - imprime;
            - Acessa à Esquerda;
            - Acessa à Direita.
        Função recursiva.
    */
void imprime(
        TipoPonteiro ponteiro,
        int          nivel){

    if (ponteiro == NULL) return;

    for(int i = 0; i < nivel; i++)
        printf("    ");
    printf("Nível %d:\n", nivel);

    for(int i = 0; i < nivel; i++)
        printf("    ");
    printf("  ");

    for (int i = 0; i < ponteiro->quantidade; i++)
        printf("%3d ",(int)ponteiro->registros[i].chave);
    printf("\n\n");

    nivel++;

    for (int i = 0; i <= ponteiro->quantidade; i++)
        imprime(ponteiro->ponteiros[i], nivel);
}

void cabecalhos(int option){
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
        printf(" = 2. Imprimir Árvore                   =\n");
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
    else if(option == 4){
        printf(" = Informe o valor de T:                =\n");
        printf(" >>");
    }
}

int main(int argc, char const *argv[]) {
    cabecalhos(4);
    scanf("%hd", &T);
    ORDEM = T * 2;

    TipoRegistro registro;
    TipoPagina  *ponteiro = NULL;
    short  option;

    while(1){
        cabecalhos(1);
        scanf("%hi", &option);
        switch(option){
            case 1:
                cabecalhos(2);
                scanf("%d", &registro.chave);
                insere(registro, &ponteiro);
                break;
            case 2:
                cabecalhos(3);
                imprime(ponteiro, 0);
                continua();
                break;
            default:
                return 0;
        }
    }

    return 0;
}
