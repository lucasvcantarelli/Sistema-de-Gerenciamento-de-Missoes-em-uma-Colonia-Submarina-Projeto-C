#include <stdio.h>
#include <stdlib.h>
#include "fila.h"

void fila_inicializar(Fila *f) {
    f->inicio = NULL;
    f->fim = NULL;
    f->tamanho = 0;
}

int fila_vazia(const Fila *f) {
    return f->inicio == NULL;
}

int fila_enfileirar(Fila *f, Missao m) {
    NoFila *novo = (NoFila *)malloc(sizeof(NoFila));
    if (novo == NULL) return 0;

    novo->missao = m;
    novo->prox = NULL;

    if (f->fim == NULL) {      /* fila vazia */
        f->inicio = novo;
    } else {
        f->fim->prox = novo;
    }
    f->fim = novo;
    f->tamanho++;
    return 1;
}

int fila_desenfileirar(Fila *f, Missao *saida) {
    if (fila_vazia(f)) return 0;

    NoFila *no = f->inicio;
    if (saida) *saida = no->missao;

    f->inicio = no->prox;
    if (f->inicio == NULL) f->fim = NULL;   /* ficou vazia */
    f->tamanho--;
    free(no);
    return 1;
}

int fila_frente(const Fila *f, Missao *saida) {
    if (fila_vazia(f)) return 0;
    *saida = f->inicio->missao;
    return 1;
}

int fila_contem(const Fila *f, int codigo) {
    for (NoFila *p = f->inicio; p != NULL; p = p->prox) {
        if (p->missao.codigo == codigo) return 1;
    }
    return 0;
}

void fila_listar(const Fila *f) {
    if (fila_vazia(f)) {
        printf("Fila de execucao vazia.\n");
        return;
    }
    printf("--- Fila de execucao (%d missao(oes)) ---\n", f->tamanho);
    int pos = 1;
    for (NoFila *p = f->inicio; p != NULL; p = p->prox, pos++) {
        printf("%d. ", pos);
        missao_imprimir(&p->missao);
        printf("\n");
    }
}

void fila_liberar(Fila *f) {
    while (!fila_vazia(f)) fila_desenfileirar(f, NULL);
}
