#include <stdio.h>
#include <stdlib.h>

struct No {
    int valor;
    struct No *esq, *dir;
    int altura;
};

int altura(struct No *n) {
    if (n == NULL) return 0;
    return n->altura;
}

int fb(struct No *n) {
    return altura(n->esq) - altura(n->dir);
}

int maior(int a, int b) {
    return a > b ? a : b;
}

struct No* novo_no(int v) {
    struct No *n = malloc(sizeof(struct No));
    n->valor = v;
    n->esq = n->dir = NULL;
    n->altura = 1;
    return n;
}

void atualiza(struct No *n) {
    n->altura = 1 + maior(altura(n->esq), altura(n->dir));
}

struct No* rot_dir(struct No *y) {
    struct No *x = y->esq;
    y->esq = x->dir;
    x->dir = y;
    atualiza(y);
    atualiza(x);
    return x;
}

struct No* rot_esq(struct No *y) {
    struct No *x = y->dir;
    y->dir = x->esq;
    x->esq = y;
    atualiza(y);
    atualiza(x);
    return x;
}

struct No* inserir(struct No *raiz, int v) {
    if (!raiz) return novo_no(v);

    if (v < raiz->valor)
        raiz->esq = inserir(raiz->esq, v);
    else if (v > raiz->valor)
        raiz->dir = inserir(raiz->dir, v);
    else
        return raiz;

    atualiza(raiz);

    int f = fb(raiz);

    if (f == 2 && fb(raiz->esq) >= 0)
        return rot_dir(raiz);
    if (f == 2 && fb(raiz->esq) < 0) {
        raiz->esq = rot_esq(raiz->esq);
        return rot_dir(raiz);
    }
    if (f == -2 && fb(raiz->dir) <= 0)
        return rot_esq(raiz);
    if (f == -2 && fb(raiz->dir) > 0) {
        raiz->dir = rot_dir(raiz->dir);
        return rot_esq(raiz);
    }

    return raiz;
}

void imprimir(struct No *raiz) {
    if (!raiz) return;
    imprimir(raiz->esq);
    printf("%d ", raiz->valor);
    imprimir(raiz->dir);
}

int main() {
    struct No *arvore = NULL;
    int valores[] = {15, 10, 20, 8, 12, 25, 5, 9, 30, 18};

    for (int i = 0; i < 10; i++)
        arvore = inserir(arvore, valores[i]);

    printf("Valores em ordem: ");
    imprimir(arvore);
    printf("\n");
    printf("Raiz: %d | Altura: %d | FB: %d\n",
           arvore->valor, altura(arvore), fb(arvore));

    return 0;
}