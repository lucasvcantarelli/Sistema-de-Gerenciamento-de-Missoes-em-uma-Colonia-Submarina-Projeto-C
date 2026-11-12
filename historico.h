#ifndef HISTORICO_H
#define HISTORICO_H

#include "missao.h"

/* Historico de missoes realizadas: lista duplamente encadeada. */

typedef enum {
    STATUS_CONCLUIDA = 0,
    STATUS_FALHOU = 1
} StatusMissao;

typedef struct NoHistorico {
    Missao missao;
    StatusMissao status;
    int ordem;                       /* ordem de registro (1, 2, 3...) */
    struct NoHistorico *anterior;
    struct NoHistorico *proximo;
} NoHistorico;

typedef struct {
    NoHistorico *inicio;   /* registro mais antigo */
    NoHistorico *fim;      /* registro mais recente */
    int tamanho;
    int proxima_ordem;
} Historico;

void historico_inicializar(Historico *h);
int  historico_vazio(const Historico *h);
/* Insere no fim (mais recente). Retorna 1 em sucesso, 0 se faltou memoria. */
int  historico_inserir(Historico *h, Missao m, StatusMissao status);
/* Retorna o no com esse codigo (mais recente primeiro) ou NULL. */
NoHistorico *historico_buscar(const Historico *h, int codigo);
/* Remove o registro mais recente com esse codigo. Retorna 1 se removeu. */
int  historico_remover(Historico *h, int codigo);
/* Exibe do mais antigo ao mais recente. */
void historico_exibir(const Historico *h);
/* Exibe do mais recente ao mais antigo (usa o ponteiro 'anterior'). */
void historico_exibir_inverso(const Historico *h);
void historico_liberar(Historico *h);

#endif
