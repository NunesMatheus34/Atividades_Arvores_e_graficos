#include <stdio.h>
#include <stdlib.h>

/* Estrutura do nó da árvore AVL
   Cada nó guarda seu valor, os filhos esquerdo e direito,
   e sua altura atual na árvore */
struct No {
    int valor;
    struct No *esq, *dir;
    int altura;
};

/* Retorna a altura do nó
   Se o nó for NULL (não existe), retorna 0 */
int altura(struct No *n) {
    if (n == NULL) return 0;
    return n->altura;
}

/* Calcula o fator de balanceamento do nó
   FB = altura esquerda - altura direita
   Valores aceitos: -1, 0 ou +1 */
int fb(struct No *n) {
    return altura(n->esq) - altura(n->dir);
}

/* Retorna o maior entre dois números
   Usada para calcular a altura do nó */
int maior(int a, int b) {
    return a > b ? a : b;
}

/* Cria um novo nó com o valor recebido
   Todo nó novo começa com altura 1 pois é uma folha */
struct No* novo_no(int v) {
    struct No *n = malloc(sizeof(struct No));
    n->valor = v;
    n->esq = n->dir = NULL;
    n->altura = 1;
    return n;
}

/* Atualiza a altura do nó com base nos seus filhos
   Altura = 1 + a maior altura entre esquerda e direita */
void atualiza(struct No *n) {
    n->altura = 1 + maior(altura(n->esq), altura(n->dir));
}

/* Rotação simples à direita
   Usada quando a árvore está pesada no lado esquerdo-esquerdo
   O filho esquerdo sobe e a raiz desce para a direita */
struct No* rot_dir(struct No *y) {
    struct No *x = y->esq;   /* filho esquerdo vai subir */
    y->esq = x->dir;         /* subárvore direita de x vai para esquerda de y */
    x->dir = y;              /* y desce para direita de x */
    atualiza(y);             /* atualiza altura de y primeiro (agora é filho) */
    atualiza(x);             /* depois atualiza x (agora é a nova raiz) */
    return x;
}

/* Rotação simples à esquerda
   Usada quando a árvore está pesada no lado direito-direito
   O filho direito sobe e a raiz desce para a esquerda */
struct No* rot_esq(struct No *y) {
    struct No *x = y->dir;   /* filho direito vai subir */
    y->dir = x->esq;         /* subárvore esquerda de x vai para direita de y */
    x->esq = y;              /* y desce para esquerda de x */
    atualiza(y);             /* atualiza altura de y primeiro (agora é filho) */
    atualiza(x);             /* depois atualiza x (agora é a nova raiz) */
    return x;
}

/* Inserção AVL
   1. Insere o valor como numa ABB normal
   2. Atualiza a altura do nó
   3. Verifica o fator de balanceamento
   4. Aplica a rotação correta se necessário */
struct No* inserir(struct No *raiz, int v) {
    /* se chegou em NULL, cria o nó aqui */
    if (!raiz) return novo_no(v);

    /* insere no lado correto como numa ABB normal */
    if (v < raiz->valor)
        raiz->esq = inserir(raiz->esq, v);
    else if (v > raiz->valor)
        raiz->dir = inserir(raiz->dir, v);
    else
        return raiz; /* valor duplicado, ignora */

    /* atualiza a altura após a inserção */
    atualiza(raiz);

    /* calcula o fator de balanceamento */
    int f = fb(raiz);

    /* caso esquerda-esquerda: rotação simples à direita */
    if (f == 2 && fb(raiz->esq) >= 0)
        return rot_dir(raiz);

    /* caso esquerda-direita: rotação dupla (esq depois dir) */
    if (f == 2 && fb(raiz->esq) < 0) {
        raiz->esq = rot_esq(raiz->esq);
        return rot_dir(raiz);
    }

    /* caso direita-direita: rotação simples à esquerda */
    if (f == -2 && fb(raiz->dir) <= 0)
        return rot_esq(raiz);

    /* caso direita-esquerda: rotação dupla (dir depois esq) */
    if (f == -2 && fb(raiz->dir) > 0) {
        raiz->dir = rot_dir(raiz->dir);
        return rot_esq(raiz);
    }

    /* árvore já está balanceada, retorna sem alteração */
    return raiz;
}

/* Percorre a árvore em ordem (esq → raiz → dir)
   Imprime os valores em ordem crescente */
void imprimir(struct No *raiz) {
    if (!raiz) return;
    imprimir(raiz->esq);
    printf("%d ", raiz->valor);
    imprimir(raiz->dir);
}

int main() {
    struct No *arvore = NULL;

    /* 10 elementos inseridos fora de ordem
       forçando desbalanceamentos e rotações */
    int valores[] = {15, 10, 20, 8, 12, 25, 5, 9, 30, 18};

    /* insere cada elemento na árvore AVL */
    for (int i = 0; i < 10; i++)
        arvore = inserir(arvore, valores[i]);

    /* imprime os resultados */
    printf("Valores em ordem: ");
    imprimir(arvore);
    printf("\n");
    printf("Raiz: %d | Altura: %d | FB: %d\n",
           arvore->valor, altura(arvore), fb(arvore));

    return 0;
}