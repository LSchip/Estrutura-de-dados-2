#include <stdio.h>
#include <stdlib.h>

#define BLACK 0
#define RED 1

typedef struct arvoreRB{
  int info;
  int cor;
  struct arvoreRB *esq;
  struct arvoreRB *dir;
} ArvoreRB;


int eh_no_vermelho(ArvoreRB * no){
  if(!no) return BLACK;
  return(no->cor == RED);
}

int verifica_arv_vazia(ArvoreRB *a){
    return (a == NULL);
}

ArvoreRB *rot_esq(ArvoreRB *no){
    ArvoreRB *tree = no->dir;
    no->dir = tree->esq;
    tree->esq = no;
    tree->cor = no->cor;
    no->cor = RED;
    return (tree);
}

ArvoreRB *rot_dir(ArvoreRB *no){
    ArvoreRB *tree = no->esq;
    no->esq = tree->dir;
    tree->dir = no;
    tree->cor = no->cor;
    no->cor = RED;
    return (tree);
}

void flip_cor(ArvoreRB *no){
    no->cor = RED;
    no->esq->cor = BLACK;
    no->dir->cor = BLACK;
}

void print(ArvoreRB * a,int spaces){
    int i;
    for(i=0;i<spaces;i++) printf(" ");
    if(!a){
        printf("//\n");
        return;
    }

    printf("%d\n", a->info);
    print(a->esq,spaces+2);
    print(a->dir,spaces+2);
}


ArvoreRB *insere(ArvoreRB *a, int v){
    int change = 0;
    if (a == NULL){
        a = (ArvoreRB *)malloc(sizeof(ArvoreRB));
        a->info = v;
        a->cor = BLACK;
        a->esq = a->dir = NULL;
    }else if (v < a->info){
        change = a->esq == NULL;
        a->esq = insere(a->esq, v);
        if (change)
        a->esq->cor = RED;
    }else{
        change = a->dir == NULL;
        a->dir = insere(a->dir, v);
        if (change)
            a->dir->cor = RED;
    }

    change = 0;

    if(eh_no_vermelho(a->dir) == 1 && eh_no_vermelho(a->esq) == 0)
        a = rot_esq(a);
    else if (eh_no_vermelho(a->esq) == 1 && eh_no_vermelho(a->esq->esq) == 1)
        a = rot_dir(a);
    else if (eh_no_vermelho(a->dir) == 1 && eh_no_vermelho(a->esq) == 1)
        flip_cor(a);

    return a;
}

ArvoreRB *remove_nodo(ArvoreRB *a, int x){
    ArvoreRB *aux, *pai_aux;
    int filhos = 0, tmp, isBlack;

    if (!a)
        return (NULL);

    if(a->info < x){
        isBlack = eh_no_vermelho(a->dir);
        a->dir = remove_nodo(a->dir, x);
        if ((isBlack && eh_no_vermelho(a)) == 1 || (!isBlack && eh_no_vermelho(a) == 0)){
            if (a->dir == NULL)
                a->cor = BLACK;
            else if (a->dir->esq == NULL && a->dir->dir == NULL)
                a->dir->cor = BLACK;
    }else if (isBlack && eh_no_vermelho(a) == 0){
        if (verifica_arv_vazia(a->dir) && verifica_arv_vazia(a->esq))
            a->cor = BLACK;
        else if (!verifica_arv_vazia(a->dir))
            a->dir->cor = BLACK;
    }
    }else if (a->info > x){
        isBlack = eh_no_vermelho(a->esq);
        a->esq = remove_nodo(a->esq, x);
        if ((isBlack && eh_no_vermelho(a)) == 1 || (!isBlack && eh_no_vermelho(a) == 0)){
        if (a->esq == NULL)
            a->cor = BLACK;
        else if (a->esq->esq == NULL && a->esq->dir == NULL)
            a->esq->cor = BLACK;
        }else if (isBlack && eh_no_vermelho(a) == 0){
            if (verifica_arv_vazia(a->esq) && verifica_arv_vazia(a->dir))
                a->cor = BLACK;
            else if (!verifica_arv_vazia(a->esq))
                a->esq->cor = BLACK;
            }
    }else{
        if (a->esq)
        filhos++;
        if (a->dir)
        filhos++;

        if (filhos == 0){
            free(a);
            return (NULL);
        }else if (filhos == 1){
        aux = a->esq ? a->esq : a->dir;
        free(a);
        return (aux);
        }else{
            aux = a->esq;
            pai_aux = a;
            while(aux->dir){
                pai_aux = aux;
                aux = aux->dir;
            }
            tmp = a->info;
            a->info = aux->info;
            aux->info = tmp;
            pai_aux->dir = remove_nodo(aux, tmp);
            return (a);
        }
    }

    if (eh_no_vermelho(a->dir) == 1 && eh_no_vermelho(a->esq) == 0)
        a = rot_esq(a);
    else if (eh_no_vermelho(a->esq) == 1 && eh_no_vermelho(a->esq->esq) == 1)
        a = rot_dir(a);
    else if (eh_no_vermelho(a->dir) == 1 && eh_no_vermelho(a->esq) == 1)
        flip_cor(a);

    return a;
}

ArvoreRB *arv_libera(ArvoreRB *a){
    if (!verifica_arv_vazia(a))  {
        arv_libera(a->esq);
        arv_libera(a->dir);
        free(a);
    }
    return NULL;
}

int get_tree_height(ArvoreRB *a){
    int height = 0;
    ArvoreRB *no = a;
    while (no != NULL){
        if(eh_no_vermelho(no) == 0)
        height++;
        no = no->esq;
    }
    return height;
}

int main(){
    ArvoreRB *a;
    a = insere(a, 1);
    a = insere(a, 3);
    a = insere(a, 5);
    a = insere(a, 7);
    a = insere(a, 9);
    a = insere(a, 2);
    a = insere(a, 4);
    a = insere(a, 6);
    a = insere(a, 8);
    a = insere(a, 10);
    print(a, get_tree_height(a));
    a = remove_nodo(a, 6);
    a = remove_nodo(a, 1);
    a = remove_nodo(a, 2);
    print(a, get_tree_height(a));
    arv_libera(a);
    printf("OK");
    getchar();
}
