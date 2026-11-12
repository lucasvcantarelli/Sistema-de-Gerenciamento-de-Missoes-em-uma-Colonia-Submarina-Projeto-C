#ifndef FILA_H
#define FILA_H

#include "missao.h"

/* Fila de Execucao (FIFO) com lista encadeada simples. */

typedef struct NoFila {
    Missao missao;
    struct NoFila *prox;
} NoFila;

typedef struct {
    NoFila *inicio;   /* proxima missao a executar */
    NoFila *fim;      /* ultima missao enfileirada */
    int tamanho;
} Fila;

void fila_inicializar(Fila *f);
int  fila_vazia(const Fila *f);
/* Retorna 1 em sucesso, 0 se faltou memoria. */
int  fila_enfileirar(Fila *f, Missao m);
/* Remove a primeira missao e copia para *saida. Retorna 1 em sucesso, 0 se vazia. */
int  fila_desenfileirar(Fila *f, Missao *saida);
/* Copia a primeira missao sem remover. Retorna 1 em sucesso, 0 se vazia. */
int  fila_frente(const Fila *f, Missao *saida);
/* Retorna 1 se ja existe missao com esse codigo na fila. */
int  fila_contem(const Fila *f, int codigo);
void fila_listar(const Fila *f);
void fila_liberar(Fila *f);

#endif
