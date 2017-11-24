#include <stdio.h>
#include <stdlib.h>

/*	Título:
	TRABALHO 2 – ESTRUTURA DE DADOS II
	
	Descrição:
	Implementar (em linguagem C) uma Árvore RedBlack que possui como chave valores inteiros
	positivos não repetidos. A cada novo nó inserido devem ser mantidas as propriedades da
	árvore,de modo a fazer as rotações e recoloramento dos nodos, se necessário. 

	Autor: Eduardo Stefanello
	Data: 24 de Maio de 2017
	*/

#define RED 1 // Define constante para as cores
#define BLK 0 // Facilita o Gerenciamento

/* 	Estrutura Geral
	Estrutura unica, que contem todos os campos utilizados na arvore Red-Black
	*/
typedef struct RBNode{
	int key;	
	int level;	
	int color;	
	struct RBNode *left;
	struct RBNode *right;
	struct RBNode *father;
}RBTree;

RBTree *sentinel; //Todos os sentinelas apontam pasa o mesmo local

/*  Identação
	Essa classe identa cada nó no momento da impressão, usando como referencia de espacamento, o nivel do nó.
	É usada na função de impressão.
	*/
void identation(int level){
	while(level--)
		printf("    ");
}

/*	Impressão
	Essa função imprime cada nó, de acordo com o que é solicitado na descrição do trabalho.
	*/
void printNode(RBTree **node){
	if((*node) != NULL){
		if((*node) == sentinel){
			identation((*node)->level);
			printf("=> Sentinela (%s)", (*node)->color? "RED": "BLK");	
		} 
		else{
			identation((*node)->level);
			printf("=> Chave %d (%s)", (*node)->key, (*node)->color? "RED": "BLK");
		}
	} 
	if((*node) != NULL)
		printf(" (nível %d, ", (*node)->level);

	if((*node)->father != NULL)
		printf("chave-pai: %d)\n", (*node)->father->key);

	else
		printf("raiz)\n");
}

/* 	Percorrer em Pre Ordem (preorder)
	Função recursiva que percorre a árvore em preordem, marcando cada nodo com o seu nível e setando o no pai.
	E uma funcao recurssiva
	*/
void throughRBPreorder(RBTree **node, int level, RBTree **father){
	(*node)->level = level;
	if(father != NULL){
		(*node)->father = (*father);
	} 
	level++;
	if((*node) != NULL)
		printNode(&(*node));

	if((*node)->left != NULL)
		throughRBPreorder(&(*node)->left, level, &(*node));

	if((*node)->right != NULL)
		throughRBPreorder(&(*node)->right, level, &(*node));
}

/*	Faz a Rotação à Esquerda no Caso 3
	*/
void rotationLeft2(RBTree **node){ // Créditos à Naomi Fernanda de Mello
	RBTree *aux = (*node)->left;
	(*node)->left = aux->right;
	aux->right = (*node);
	(*node) = aux;
}

/*	Faz a Rotação à Direita no Caso 3
	*/
void rotationRight2(RBTree **node){ // Créditos à Naomi Fernanda de Mello
	RBTree *aux = (*node)->right;
	(*node)->right = aux->left;
	aux->left = (*node);
	(*node) = aux;
}

/*	Faz troca de cores do caso 3
	*/
void swapColors2(RBTree **A, RBTree **B){
	(*A)->color  = RED;
	(*B)->color = BLK;
}

/*	Caso 03
	*/
void last(RBTree **node){
	if((*node)->left != NULL)
		last(&(*node)->left);

	if((*node)->right != NULL)
		last(&(*node)->right);

	if((*node)->left != NULL  && (*node)->right != NULL){
		if((*node)->left->color == RED && (*node)->right->color == BLK){
			if((*node)->left->left != NULL){
				if((*node)->left->left->color == RED){
					swapColors2(&(*node), &(*node)->left);
					rotationLeft2(&(*node));
				}
			}
		}
		else if((*node)->right->color == RED && (*node)->left->color == BLK){
			if((*node)->right->right != NULL){
				if((*node)->right->right->color == RED){
					swapColors2(&(*node), &(*node)->right);
					rotationRight2(&(*node));
				}
			}
		}
	}
}

/*	Faz a Rotação à Esquerda no Caso 2
	*/
void rotationLeft1(RBTree **node){ // Créditos à Naomi Fernanda de Mello
	RBTree *aux = (*node)->left;
	aux->father = aux->right;
	(*node)->left = aux->right;
	aux->right = aux->right->left;
	(*node)->left->left = aux;
}

/*	Faz a Rotação à Direita no Caso 2
	*/
void rotationRight1(RBTree **node){ // Créditos à Naomi Fernanda de Mello
	RBTree *aux = (*node)->right;
	aux->father = aux->left;
	(*node)->right = aux->left;
	aux->left = aux->left->right;
	(*node)->right->right = aux;	
}

/* 	Caso 02
	*/
void elbow(RBTree **node){
	if((*node)->left != NULL)
		elbow(&(*node)->left);

	if((*node)->right != NULL)
		elbow(&(*node)->right);
	
	if((*node)->left != NULL  && (*node)->right != NULL){
		if((*node)->left->color == RED && (*node)->right->color == BLK){
			if((*node)->left->right != NULL){
				if((*node)->left->right->color == RED){
					rotationLeft1(&(*node));
				}
			}
		}
		else if((*node)->right->color == RED && (*node)->left->color == BLK){
			if((*node)->right->left != NULL){
				if((*node)->right->left->color == RED){
					rotationRight1(&(*node));
				}
			}
		}
	}
}

/*	Troca Cor
	Função que faz a troca de cores do pai, tio e avo
	*/
void swapColors1(RBTree **A, RBTree **B1, RBTree **B2){
	(*A)->color  = RED;
	(*B1)->color = BLK;
	(*B2)->color = BLK;
}

/* 	Caso 01
	*/
void twoRed(RBTree **node){
	if((*node)->left  != NULL)
		twoRed(&(*node)->left);
	
	if((*node)->right != NULL)
		twoRed(&(*node)->right);
	
	if((*node)->left  != NULL  && (*node)->right != NULL){
		if((*node)->color == BLK && (*node)->left->color == RED && (*node)->right->color == RED){
			if((*node)->left->left != NULL)
			 	if((*node)->left->left->color == RED)
			 		swapColors1(&(*node), &(*node)->left, &(*node)->right);
			
			else if((*node)->left->right != NULL)
				if((*node)->left->right->color == RED)
					swapColors1(&(*node), &(*node)->left, &(*node)->right);
			
			else if((*node)->right->left != NULL)
				if((*node)->right->left->color == RED)
					swapColors1(&(*node), &(*node)->left, &(*node)->right);
			
			else if((*node)->right->right != NULL)
				if((*node)->right->right->color == RED)
					swapColors1(&(*node), &(*node)->left, &(*node)->right);
		}
	}
}

/* 	Tratamento invariante:
	Garante que a raiz sempre seja preta.
	*/
void blackRoot(RBTree **node){
	(*node)->color = BLK;
}

/*	Função de inicialização de um novo nó
	*/
RBTree *init(int value){
	RBTree *node = (RBTree*) malloc(sizeof(RBTree));
	node->key = value; 	node->right = sentinel;
	node->level = 0; 	node->left = sentinel;
	node->color = RED;	node->father = NULL;
	return node;
}

/*	Função de inserção do nó de fato
	*/
void insertNew(RBTree **RBRoot, int value){
	if((*RBRoot) == NULL || (*RBRoot) == sentinel)
		(*RBRoot) = init(value);

	else if((*RBRoot)->key < value)
		insertNew(&(*RBRoot)->right, value);

	else if((*RBRoot)->key > value)
		insertNew(&(*RBRoot)->left,  value);
}

/*	Função Inserção com Tratamento
	*/
void insert(RBTree **RBRoot, int value){
	insertNew(&(*RBRoot), value);
	blackRoot(&(*RBRoot));
	twoRed(&(*RBRoot));
	elbow(&(*RBRoot));
	last(&(*RBRoot));
	blackRoot(&(*RBRoot));
}

/*	Principal
	Exibe o menu de auxilio ao usuario;
	Direciona o usuário a usar todas as funções disponíveis no programa e coleta os valores que serão inseridos na árvore
	*/
int main(){
	sentinel = (RBTree*) malloc(sizeof(RBTree));
	RBTree *RBRoot;
	int option, value;
	
	while(1){
		printf("1 inserir\n");
		printf("2 imprimir\n");
		printf("0 sair\n");
		scanf("%d", &option);
		switch(option){
			case 1:
				printf("valor: ");
				scanf("%d", &value);
				insert(&RBRoot, value);
				break;
			case 2:
				throughRBPreorder(&RBRoot, 0, NULL);
				break;
			default: return 0;

		}
	}
}