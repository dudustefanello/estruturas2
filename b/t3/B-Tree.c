#include <stdio.h>
#include <stdlib.h>

#define BTN (*BTreeNode)

typedef struct node {
    int     *keys;          // Ponteiro para as chaves
    struct  node **childs;  // Ponteiro para os ponteiros
    int     amount;         // Quantidade de valores no nó
    short   isLeaf;         // Indicador se é folha
    short   isRoot;         // Indicador se é raiz
    int     order;          // Carrega a ordem da árvore
}BTreeStruct;

BTreeStruct *createNode(short leaf, short root, int order){
    BTreeStruct *auxiliary = (BTreeStruct*) malloc(sizeof(BTreeStruct));
    auxiliary->keys = (int*) calloc(order, sizeof(int));
    if(!leaf){
        auxiliary->childs = (BTreeStruct**) calloc(order, sizeof(BTreeStruct));
    }
    auxiliary->amount = 0;
    auxiliary->isRoot = root;
    auxiliary->isLeaf = leaf;
    auxiliary->order = order;
    return auxiliary;
}

void insertInOrderLeaf(BTreeStruct **BTreeNode, int value){
    int auxiliary[20];
    int i;
    for(i = 0; i < BTN->order; i++){
        if(BTN->keys[i] < value){
            auxiliary[i] = BTN->keys[i];
        }
        if(BTN->keys[i] > value){
            auxiliary[i] = value;
            break;
        }
    }
    for(int j = i; j < BTN->order - 1; j++){
        auxiliary[j+1] = BTN->keys[j];
    }
    for (int i = 0; i < BTN->order; i++) {
        BTN->keys[i] = auxiliary[i];
    }
    BTN->amount++;
}

BTreeStruct *searchLeafToInsert(BTreeStruct **BTreeNode, int value){
    if(BTN->isLeaf){
        return BTN;
    }
    for(int i = 0; i < BTN->amount; i++){
        if(i == 0 && BTN->keys[i] > value){
            return searchLeafToInsert(&BTN->childs[i], value);
        }
        if(BTN->keys[i] < value && BTN->keys[i + 1] > value){
            return searchLeafToInsert(&BTN->childs[i + 1], value);
        }
        if(i == BTN->amount - 1){
            if(BTN->keys[i] < value){
                return searchLeafToInsert(&BTN->childs[i+1], value);
            }
        }
    }
    return NULL;
}

void insertNew(BTreeStruct **BTreeNode, int value){
    BTreeStruct *auxiliary = searchLeafToInsert(&BTN, value);
    insertInOrderLeaf(&auxiliary, value);
    //if(auxiliary->amount == auxiliary->order){
        //split();
    //}
}

int main(int argc, char const *argv[]) {
    BTreeStruct *BTreeRoot = createNode(1, 1, 3);

    insertNew(&BTreeRoot, 5);
    insertNew(&BTreeRoot, 8);

    for (int i = 0; i < 3; i++) {
        printf("key %d\n", BTreeRoot->keys[i]);
        printf("amount %d\n", BTreeRoot->amount);
        printf("isRoot %d\n", BTreeRoot->isRoot);
        printf("isLeaf %d\n", BTreeRoot->isLeaf);
        printf("\n");
    }



    return 0;
}
