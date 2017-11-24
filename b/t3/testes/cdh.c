#define T 2
#include <stdio.h>
#include <stdlib.h>

typedef struct btree{
    int n;
    int keys[(2*T)-1];
    struct btree* children[2*T];
    int leaf;
}btree;


btree* btree_create(){
    int i;
    btree* x=(btree*)malloc(sizeof(btree));
    x->leaf = 1;
    x->n = 0;
    for (i=0; i<=2*T;i++) x->children[i] = NULL;
    return x;
}

void split_child(btree* x,int i,btree* y){
    int j;
    btree* z=btree_create();
    z->leaf = y->leaf;
    z->n = T-1;
    for (j=1;j<=T-1;j++){
        z->keys[j] = y->keys[j+T];
    }
    if (y->leaf == 0){
        for(j=1;j<=T;j++){
            z->children[j] = y->children[j+T];
        }
        y->n = T-1;
        for (j=x->n+1;j>=i+1;j--){
            x->children[j+1] = x->children[j];
        }
        x->children[i+1] = z;
        for (j=x->n;j>=i;j--){
            x->keys[j+1] = x->keys[j];
        }
    }
    x->keys[i] = x->keys[T];
    x->n = x->n+1;
}

void insert_nonfull(btree* x,int k){
    int i=x->n;
    if (x->leaf == 1){
        while(i>=1 && k<x->keys[i]){
            x->keys[i+1] = x->keys[i];
            i=i-1;
        }
        x->keys[i+1] = k;
        x->n = x->n+1;
    }
    else{
        while(i>=1 && k<x->keys[i]){
            i=i-1;
        }
        i=i+1;
        if (x->children[i]->n == 2*T - 1){
            split_child(x,i,x->children[i]);
            if (k > x->keys[i]){
                i=i+1;
            }
            insert_nonfull(x->children[i],k);
        }
    }
}

void insert(btree** root,int k){
    btree* s=btree_create();
    btree* r=*root;
    if (r->n == 2*T-1) {
        *root=s;
        s->leaf = 0;
        s->n = 0;
        s->children[1] = r;
        split_child(s,1,r);
        insert_nonfull(s,k);
    }
    else{
        insert_nonfull(r,k);
    }
}

int main (int argc, char *argv[]){
    btree* b = btree_create();
    insert(&b, 8);
    /*insert(&b, 10);
    insert(&b, 15);
    insert(&b, 25);
    insert(&b, 9);
    insert(&b, 7);
    insert(&b, 5);
    insert(&b, 22);
    insert(&b, 20);*/
    printf("%d\n",b->keys[1]);
    return 0;
}
