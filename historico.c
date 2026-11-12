#include <stdio.h>
#include <stdlib.h>
#include "historico.h"

static const char *texto_status(StatusMissao s) {
    return s == STATUS_CONCLUIDA ? "CONCLUIDA" : "FALHOU";
}

static void imprimir_no(const NoHistorico *no) {
    printf("#%d [%s] ", no->ordem, texto_status(no->status));
    missao_imprimir(&no->missao);
    printf("\n");
}

void historico_inicializar(Historico *h) {
    h->inicio = NULL;
    h->fim = NULL;
    h->tamanho = 0;
    h->proxima_ordem = 1;
}

int historico_vazio(const Historico *h) {
    return h->inicio == NULL;
}

int historico_inserir(Historico *h, Missao m, StatusMissao status) {
    NoHistorico *novo = (NoHistorico *)malloc(sizeof(NoHistorico));
    if (novo == NULL) return 0;

    novo->missao = m;
    novo->status = status;
    novo->ordem = h->proxima_ordem++;
    novo->proximo = NULL;
    novo->anterior = h->fim;

    if (h->fim == NULL) {      /* lista vazia */
        h->inicio = novo;
    } else {
        h->fim->proximo = novo;
    }
    h->fim = novo;
    h->tamanho++;
    return 1;
}

NoHistorico *historico_buscar(const Historico *h, int codigo) {
    for (NoHistorico *p = h->fim; p != NULL; p = p->anterior) {
        if (p->missao.codigo == codigo) return p;
    }
    return NULL;
}

int historico_remover(Historico *h, int codigo) {
    NoHistorico *no = historico_buscar(h, codigo);
    if (no == NULL) return 0;

    if (no->anterior) no->anterior->proximo = no->proximo;
    else h->inicio = no->proximo;

    if (no->proximo) no->proximo->anterior = no->anterior;
    else h->fim = no->anterior;

    free(no);
    h->tamanho--;
    return 1;
}

void historico_exibir(const Historico *h) {
    if (historico_vazio(h)) {
        printf("Historico vazio.\n");
        return;
    }
    printf("--- Historico (mais antigo -> mais recente, %d registro(s)) ---\n", h->tamanho);
    for (NoHistorico *p = h->inicio; p != NULL; p = p->proximo) imprimir_no(p);
}

void historico_exibir_inverso(const Historico *h) {
    if (historico_vazio(h)) {
        printf("Historico vazio.\n");
        return;
    }
    printf("--- Historico (mais recente -> mais antigo, %d registro(s)) ---\n", h->tamanho);
    for (NoHistorico *p = h->fim; p != NULL; p = p->anterior) imprimir_no(p);
}

void historico_liberar(Historico *h) {
    NoHistorico *p = h->inicio;
    while (p != NULL) {
        NoHistorico *prox = p->proximo;
        free(p);
        p = prox;
    }
    historico_inicializar(h);
}
