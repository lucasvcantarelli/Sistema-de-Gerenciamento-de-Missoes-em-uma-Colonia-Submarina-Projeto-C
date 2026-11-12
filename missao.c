#include <stdio.h>
#include "missao.h"

void missao_imprimir(const Missao *m) {
    printf("Cod %d | Destino: %s | Duracao: %dh | Risco: %d | Prioridade: %d | Veiculo: %s",
           m->codigo, m->destino, m->duracao, m->risco, m->prioridade,
           m->veiculo[0] ? m->veiculo : "(nenhum)");
}
