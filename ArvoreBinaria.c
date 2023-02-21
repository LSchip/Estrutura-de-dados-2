#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct arvore {
   char info;
   struct arvore *esq;
   struct arvore *dir;
} Arvore;

Arvore*  cria_arv_vazia (void);
Arvore*  arv_constroi (char c, Arvore* e, Arvore* d);
int      verifica_arv_vazia (Arvore* a);
Arvore*  arv_libera (Arvore* a);
int      arv_pertence (Arvore* a, char c);
void     arv_imprime (Arvore* a);
int      arv_bin_check(Arvore *a);

Arvore* cria_arv_vazia (void) {
   return NULL;
}

Arvore* arv_constroi (char c, Arvore* e, Arvore* d) {
  Arvore* a = (Arvore*)malloc(sizeof(Arvore));
  a->info = c;
  a->esq = e;
  a->dir = d;
  return a;
}

int verifica_arv_vazia (Arvore* a) {
  return (a == NULL);
}

Arvore* arv_libera (Arvore* a) {
  if (!verifica_arv_vazia(a)) {
    arv_libera (a->esq);
    arv_libera (a->dir);
    free(a);
  }
  return NULL;
}

bool eh_espelho(Arvore* a, Arvore* b){
    if((a==NULL) && (b==NULL))return true;
    if((!a && b) || (a && !b))return false;

    bool check_esq = eh_espelho(a->esq,b->dir);
    bool check_dir = eh_espelho(a->dir,b->esq);
    return (a->info == b->info) && check_esq && check_dir;
}

Arvore *cria_espelho(Arvore *a){
    if(a == NULL) return NULL;
    Arvore *b = (Arvore*)malloc(sizeof(Arvore));

    b = arv_constroi(a->info, cria_espelho(a->dir), cria_espelho(a->esq));
    return b;
}

int arv_bin_check(Arvore *a){
    if(a == NULL) return 1;

    if(a->esq != NULL && a->esq->info > a->info)
        return 0;

    if(a->dir != NULL && a->dir->info < a->info)
        return 0;

    if(!arv_bin_check(a->esq) || !arv_bin_check(a->dir))
        return 0;

    return 1;
}

int main (int argc, char *argv[]) {
  Arvore *a, *b, *c;
  a = arv_constroi('a',
    arv_constroi('b',
        arv_constroi('d',
            cria_arv_vazia(),
            cria_arv_vazia()
            ),
        cria_arv_vazia()
    ),
    arv_constroi('c',
        arv_constroi('e',
            cria_arv_vazia(),
            cria_arv_vazia()
        ),
        arv_constroi('f',
            cria_arv_vazia(),
            cria_arv_vazia()
        )
    )
);

c = cria_espelho(a);

b = arv_constroi('a',
    arv_constroi('c',
        arv_constroi('f',
            cria_arv_vazia(),
            cria_arv_vazia()
        ),
        arv_constroi('e',
            cria_arv_vazia(),
            cria_arv_vazia()
        )
    ),
    arv_constroi('b',
        cria_arv_vazia(),
        arv_constroi('d',
            cria_arv_vazia(),
            cria_arv_vazia()
        )
    )
);

if(eh_espelho(a, b))
    printf("\nArvores a e b sao espelhos");
else printf("\nArvores a e b NAO sao espelhos");

if(eh_espelho(a, c))
    printf("\nArvores a e c sao espelhos");
else printf("\nArvores a e c NAO sao espelhos");


arv_libera(a);
arv_libera(b);
arv_libera(c);

  return 0;
}
