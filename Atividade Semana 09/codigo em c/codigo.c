#include <stdio.h>
#include <stdlib.h>

struct No {
    int valor;
    struct No *esq, *dir;
};

struct No* criar(int v) {
    struct No *n = malloc(sizeof(struct No));
    n->valor = v; n->esq = n->dir = NULL;
    return n;
}

struct No* inserir(struct No *r, int v) {
    if (!r) return criar(v);
    if (v < r->valor) r->esq = inserir(r->esq, v);
    else r->dir = inserir(r->dir, v);
    return r;
}

struct No* buscar(struct No *r, int v) {
    if (!r || r->valor == v) return r;
    return v < r->valor ? buscar(r->esq, v) : buscar(r->dir, v);
}

struct No* menor(struct No *r) {
    while (r->esq) r = r->esq;
    return r;
}

struct No* remover(struct No *r, int v) {
    if (!r) return NULL;
    if (v < r->valor) r->esq = remover(r->esq, v);
    else if (v > r->valor) r->dir = remover(r->dir, v);
    else {
        if (!r->esq) { struct No *t = r->dir; free(r); return t; }
        if (!r->dir) { struct No *t = r->esq; free(r); return t; }
        struct No *t = menor(r->dir);
        r->valor = t->valor;
        r->dir = remover(r->dir, t->valor);
    }
    return r;
}

void imprimir(struct No *r) {
    if (!r) return;
    imprimir(r->esq);
    printf("%d ", r->valor);
    imprimir(r->dir);
}

int main() {
    struct No *a = NULL;
    int v[] = {20, 10, 30, 5, 15, 25, 35, 8, 12, 28};

    for (int i = 0; i < 10; i++) a = inserir(a, v[i]);
    printf("Em ordem: "); imprimir(a); printf("\n");

    printf("Busca 15: %s\n", buscar(a, 15) ? "encontrado" : "nao encontrado");
    printf("Busca 99: %s\n", buscar(a, 99) ? "encontrado" : "nao encontrado");

    a = remover(a, 8);  printf("Removeu no folha (8):          "); imprimir(a); printf("\n");
    a = remover(a, 12); printf("Removeu no com um filho (12):  "); imprimir(a); printf("\n");
    a = remover(a, 10); printf("Removeu no com dois filhos(10):"); imprimir(a); printf("\n");

    return 0;
}