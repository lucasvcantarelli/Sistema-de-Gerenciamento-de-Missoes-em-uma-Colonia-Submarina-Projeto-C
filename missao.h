#ifndef MISSAO_H
#define MISSAO_H

/*
 * Struct provisoria de Missao.
 * Substituir/ajustar quando o integrante responsavel entregar a versao oficial.
 * Fila e Historico so dependem de: codigo (identificador) e dos campos
 * exibidos em missao_imprimir().
 */

#define TAM_DESTINO 50
#define TAM_VEICULO 50

typedef struct {
    int  codigo;                 /* identificador unico da missao */
    char destino[TAM_DESTINO];   /* local da exploracao */
    int  duracao;                /* duracao estimada (horas) */
    int  risco;                  /* nivel de risco: 1 (baixo) a 5 (alto) */
    int  prioridade;             /* prioridade cientifica: 1 (baixa) a 5 (alta) */
    char veiculo[TAM_VEICULO];   /* nome do veiculo associado ("" se nenhum) */
} Missao;

/* Imprime a missao em uma linha. */
void missao_imprimir(const Missao *m);

#endif
