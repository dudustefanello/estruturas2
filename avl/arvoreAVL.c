#include <stdio.h>
#include <stdlib.h>

/*	Título:
	TRABALHO 1 – ESTRUTURA DE DADOS II
	
	Descrição:
	Implementar (em linguagem C) uma Árvore AVL que possui como chave valores inteiros positivos nao repetidos.
	A cada novo no inserido na arvore deve ocorrer o balanceamento da mesma, se necessario. 

	Autor: Eduardo Stefanello
	Data: 22 de Abril de 2017
	*/

/* 	Estrutura Geral
	Estrutura unica, que contem todos os campos utilizados na arvore AVL
	*/
typedef struct AVLTree{
	int key; // Inteiro que contém a informação principal de cada nó.
	int level; // Inteiro que marca o nível de cada nó no momento da impressão.
	int balanceFactor; // Inteiro utilizado para definir se é necessário ou não executar um balanceamento, se ele será simples ou duplo.
	struct AVLTree *left; //Ponteiro que aponta para o filho à esquerda de cada nó
	struct AVLTree *right; // Ponteiro que aponta para o filho à direita de cada nó
	struct AVLTree *father; // Ponteiro que aponta para o pai de cada nó, é usado na função de impressão.
}AVLTree;

/*  Identação
	Essa classe identa cada nó no momento da impressão, usando como referencia de espacamento, o nivel do no.
	*/
void identation(int level){
	while(level--){
		printf("   ");
	}
}

/*	Impressão
	Essa função imprime cada nó, de acordo com o que é solicitado na descrição do trabalho.
	*/
void printNodeAVL(AVLTree **node){
	if((*node) != NULL){
		identation((*node)->level);
		printf("=> Chave %d", (*node)->key);
	} 
	if((*node) != NULL){
		printf(" (nível %d, ", (*node)->level);
	}	
	if((*node)->father != NULL){
		printf("chave-pai: %d)\n", (*node)->father->key);
	}
	else{
		printf("raiz)\n");
	}
}

/* 	Percorrer em Pre Ordem (preorder)
	Função recursiva que percorre a árvore em preordem, marcando cada nodo com o seu nível e setando o no pai.
	E uma funcao recurssiva
	*/
void throughAVLPreorder(AVLTree **node, int level, AVLTree **father){
	(*node)->level = level;
	if(father != NULL){
		(*node)->father = (*father);
	} 
	level++;
	if((*node) != NULL){
		printNodeAVL(&(*node));
	}
	if((*node)->left != NULL){
		throughAVLPreorder(&(*node)->left, level, &(*node));
	} 
	if((*node)->right != NULL){
		throughAVLPreorder(&(*node)->right, level, &(*node));
	} 
}

/*	Percorrer em Ordem (inorder)
	Função recursiva que percorre a árvore em ordem, marcando cada nodo com o seu nível e setando o no pai.
	E uma funcao recurssiva
    */
void throughAVLInorder(AVLTree **node, int level, AVLTree **father){
    (*node)->level = level;
	if(father != NULL){
		(*node)->father = (*father);
	} 
	level++;
	if((*node)->left != NULL){
		throughAVLInorder(&(*node)->left, level, &(*node));
	}
	if((*node) != NULL){
		printNodeAVL(&(*node));
	} 
	if((*node)->right != NULL){
		throughAVLInorder(&(*node)->right, level, &(*node));
	}
}

/*	Percorrer em Pos Ordem (postorder)
	Função recursiva que percorre a árvore em pos ordem, marcando cada nodo com o seu nível e setando o no pai.
	*/
void throughAVLPostorder(AVLTree **node, char option, int level, AVLTree **father){
	(*node)->level = level;
	if(father != NULL){
		(*node)->father = (*father);
	} 
	level++;
	if((*node)->left != NULL){
		throughAVLPostorder(&(*node)->left, option, level, &(*node));
	} 
	if((*node)->right != NULL){
		throughAVLPostorder(&(*node)->right, option, level, &(*node));
	}
	if((*node) != NULL && option == 1){
		free((*node));
	}
	if((*node) != NULL && option == 2){
		printNodeAVL(&(*node));
	} 
}

/*	Inicializacao
	Aloca espaco para a arvore quando ela ainda e nula;
	E usada pela funcao insertAVL
	retorna um ponteiro do tipo da arvore
	*/
AVLTree *inicializa(){
	AVLTree *node = (AVLTree*) malloc(sizeof(AVLTree));
	return node;
}

/*	Rotacao a Direita
	Executa a rotacao a direita quando e encontrado um erro no balanceamento da arvore;
	Faz a rotacao simples ou dupla, na mesma funcao;
	a rotacao simples e dupla ocorrem de forma totalmente desconexas.
	*/
AVLTree *rotationRight(AVLTree **node){
    printf("right ");
	AVLTree *u, *v;
	u = (*node)->left;
	if(u->balanceFactor > 0){
		printf("double\n");
		v = u->right;
		u->right = v->left;
		(*node)->left = v->right;
		v->left = u;
		v->right = (*node);
		if(v->balanceFactor == -1){
			u->balanceFactor = 0;
			(*node)->balanceFactor = 1;
		}
		else if(v->balanceFactor == 0){
			u->balanceFactor = 0;
			(*node)->balanceFactor = 0;
		}
		else if(v->balanceFactor == 1){
			u->balanceFactor = -1;
			(*node)->balanceFactor = 0;
		}
		return v;
	}
	printf("simples\n");
	(*node)->left = u->right;
	u->right = (*node);
	if(u->balanceFactor < 0){
		u->balanceFactor = 0;
		(*node)->balanceFactor = 0;
	}
	else{
		u->balanceFactor = -1;
		(*node)->balanceFactor = 1;
	}
	return u;
}

/*	Rotacao a Esquerda
	Executa a rotacao a esquerda quando e encontrado um erro no balanceamento da arvore;
	Faz a rotacao simples ou dupla, na mesma funcao;
	rotacao simples e dupla ocorrem de forma totalmente desconexas.
	*/
AVLTree *rotationLeft(AVLTree **node){
    printf("left ");
	AVLTree *u, *v;
	u = (*node)->right; //0
	if(u->balanceFactor < 0){
		printf("double\n");
		v = u->left; //1
		u->left = v->right; //2
		(*node)->right = v->left; //3
		v->right = u; //4
		v->left = (*node); //5
		if(v->balanceFactor == 1){
			u->balanceFactor = 0;
			(*node)->balanceFactor = -1;
		}
		else if(v->balanceFactor == 0){
			u->balanceFactor = 0;
			(*node)->balanceFactor = 0;
		}
		else if(v->balanceFactor == -1){
			u->balanceFactor = 1;
			(*node)->balanceFactor = 0;
		}
		return v;
	}
	printf("simples\n");
	(*node)->right = u->left;
	u->left = (*node);
	if(u->balanceFactor > 0){
		u->balanceFactor = 0;
		(*node)->balanceFactor = 0;
	}
	else{
		u->balanceFactor = 1;
		(*node)->balanceFactor = 1;
	}
	return u;
}

/*	Insercao com Balanceamento
	Inicializa a arvore caso ela for nula;
	Insere de forma recursiva:
	A esquerda se a nova chave for menor que a chave atual 
	A direita se a nova chave for maior que a chave atual
	Chama as funcoes de rotacao quando necessario 
    */
int insertAVL(AVLTree **node, int value, int *changeHeight){
	if((*node) == NULL){
		(*node) = inicializa();
		(*node)->key = value;
		(*node)->balanceFactor = 0;
		(*node)->level = 0;
		(*node)->left = NULL;
		(*node)->right = NULL;
		(*node)->father = NULL;
		*changeHeight = 1;
		return 1;
	}
	if(value < (*node)->key){
		if(insertAVL(&(*node)->left, value, changeHeight)){
			if(changeHeight){
				(*node)->balanceFactor -= 1;
				if((*node)->balanceFactor == -2){
					(*node) = rotationRight(&(*node));
					*changeHeight = 0;
				}
				else if((*node)->balanceFactor == 0){
					*changeHeight = 0;
				}
				else if((*node)->balanceFactor == -1){
					*changeHeight = 1;
				}
			}
			return 1;
		}
	}
	if(value > (*node)->key){
		printf("1\n");
		if(insertAVL(&(*node)->right, value, changeHeight)){
			printf("2\n");
			if(*changeHeight){
				printf("3\n");
				(*node)->balanceFactor += 1;
				if((*node)->balanceFactor == 2){
					printf("4\n");
					(*node) = rotationLeft(&(*node));
					*changeHeight = 0;
				}
				else if((*node)->balanceFactor == 0){
					*changeHeight = 0;
				}
				else if((*node)->balanceFactor == 1){
					*changeHeight = 1;
				}
			}
			return 1;
		}
	}
	return 0;
}

/*	Principal
	Exibe o menu de auxilio ao usuario;
	Direciona o usuário a usar todas as funções disponíveis no programa e coleta os valores que serão inseridos na árvore
	*/
int main(){
	AVLTree *AVLRoot = NULL;
	int changeHeight = 0, option, value, sucess = 1, first = 1;
	while(1){
		system("clear");
		if(!first){
			sucess?
			printf("\n =>    Valor inserido com sucesso!     <=\n"):
			printf("\n =>    O valor já existe na árvore.    <=\n");
		}
		printf("\n");
		printf(" ========================================\n");
		printf(" -       Universidade Federal da        -\n");
		printf(" -            Fronteira Sul             -\n");
		printf(" - Disciplina de Estruturas de Dados II -\n");
		printf(" -               T1 - AVL               -\n");
		printf(" - Aluno:     Eduardo Stefanello        -\n");
		printf(" - Professor: Doglas André Finco        -\n");
		printf(" ========================================\n");
		printf(" = OPÇÕES:                              =\n");
		printf(" = 1. Inserir Valor                     =\n");
		printf(" = 2. Percorrer Árvore                  =\n");
		printf(" = 0. Encerrar Execução                 =\n");
		printf(" ========================================\n");
		printf(" ==> ");
		scanf("%d", &option);
		switch(option){
			case 1:{ // Inserir Valor
				first = 0;
				system("clear");
				printf("\nEntre com um valor inteiro para ser inserido: ");
				scanf("%d", &value);
				sucess = insertAVL(&AVLRoot, value, &changeHeight);
				break;
			}
			case 2:{ // Percorrer Árvore
				if(AVLRoot != NULL){
					first = 1;
					system("clear");
					printf("\n");
					printf(" ========================================\n");
					printf(" -       Universidade Federal da        -\n");
					printf(" -            Fronteira Sul             -\n");
					printf(" - Disciplina de Estruturas de Dados II -\n");
					printf(" -               T1 - AVL               -\n");
					printf(" - Aluno:     Eduardo Stefanello        -\n");
					printf(" - Professor: Doglas André Finco        -\n");
					printf(" ========================================\n");
					printf(" = PERCOREER EM:                        =\n");
					printf(" = 1. Preorder                          =\n");
					printf(" = 2. Inorder                           =\n");
					printf(" = 3. Postorder                         =\n");
					printf(" ========================================\n");
					printf(" ==> ");
					scanf("%d", &option);
					getchar();
					if(option == 1){
						throughAVLPreorder(&AVLRoot, 0, NULL);
						printf("Pressione Enter para continuar.");
						getchar();
					}
					else if(option == 2){
						throughAVLInorder(&AVLRoot, 0, NULL);
						printf("Pressione Enter para continuar.");
						getchar();					
					}
					else if(option == 3){
						throughAVLPostorder(&AVLRoot, 2, 0, NULL);
						printf("Pressione Enter para continuar.");
						getchar();					
					}
				}
				break;
			}
			case 0:{ // Encerra o Programa
				if(AVLRoot != NULL){
					throughAVLPostorder(&AVLRoot, 1, 0, NULL);					
				}
				return 0;
			}
		}
	}	
}