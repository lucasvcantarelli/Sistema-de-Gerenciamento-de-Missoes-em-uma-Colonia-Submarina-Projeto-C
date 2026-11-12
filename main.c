/*
 * Demonstracao da Gestao Sequencial (Integrante 2):
 * Fila de Execucao + Historico (lista duplamente encadeada) + Exibicao.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "missao.h"
#include "fila.h"
#include "historico.h"

/* Le uma linha do teclado sem o '\n'. Retorna 0 em EOF. */
static int ler_linha(const char *msg, char *buf, size_t tam) {
    printf("%s", msg);
    if (fgets(buf, (int)tam, stdin) == NULL) return 0;
    buf[strcspn(buf, "\r\n")] = '\0';
    return 1;
}

/* Le um inteiro no intervalo [min, max], repetindo ate ser valido. */
static int ler_int(const char *msg, int min, int max) {
    char buf[32];
    for (;;) {
        if (!ler_linha(msg, buf, sizeof buf)) exit(0);
        char *fim;
        long v = strtol(buf, &fim, 10);
        if (fim != buf && *fim == '\0' && v >= min && v <= max) return (int)v;
        printf("Valor invalido. Digite um numero entre %d e %d.\n", min, max);
    }
}

static void cadastrar_missao(Fila *fila, const Historico *hist) {
    Missao m;
    m.codigo = ler_int("Codigo: ", 1, 999999);
    if (fila_contem(fila, m.codigo) || historico_buscar(hist, m.codigo)) {
        printf("Ja existe missao com esse codigo (na fila ou no historico).\n");
        return;
    }
    if (!ler_linha("Destino: ", m.destino, sizeof m.destino)) exit(0);
    m.duracao = ler_int("Duracao estimada (horas): ", 1, 10000);
    m.risco = ler_int("Nivel de risco (1-5): ", 1, 5);
    m.prioridade = ler_int("Prioridade cientifica (1-5): ", 1, 5);
    if (!ler_linha("Veiculo associado (vazio = nenhum): ", m.veiculo, sizeof m.veiculo)) exit(0);

    if (fila_enfileirar(fila, m)) printf("Missao %d enfileirada.\n", m.codigo);
    else printf("Erro: memoria insuficiente.\n");
}

static void executar_proxima(Fila *fila, Historico *hist) {
    Missao m;
    if (!fila_frente(fila, &m)) {
        printf("Nao ha missoes na fila.\n");
        return;
    }
    printf("Executando: ");
    missao_imprimir(&m);
    printf("\n");

    int ok = ler_int("Resultado (1 = concluida, 2 = falhou): ", 1, 2);
    StatusMissao st = (ok == 1) ? STATUS_CONCLUIDA : STATUS_FALHOU;

    if (historico_inserir(hist, m, st)) {
        fila_desenfileirar(fila, NULL);   /* so remove da fila se registrou */
        printf("Missao %d registrada no historico.\n", m.codigo);
    } else {
        printf("Erro: memoria insuficiente. Missao mantida na fila.\n");
    }
}

static void buscar_historico(const Historico *hist) {
    int cod = ler_int("Codigo a buscar: ", 1, 999999);
    NoHistorico *no = historico_buscar(hist, cod);
    if (no == NULL) {
        printf("Missao %d nao encontrada no historico.\n", cod);
        return;
    }
    printf("#%d [%s] ", no->ordem, no->status == STATUS_CONCLUIDA ? "CONCLUIDA" : "FALHOU");
    missao_imprimir(&no->missao);
    printf("\n");
}

static void remover_historico(Historico *hist) {
    int cod = ler_int("Codigo a remover: ", 1, 999999);
    if (historico_remover(hist, cod)) printf("Registro removido.\n");
    else printf("Missao %d nao encontrada no historico.\n", cod);
}

int main(void) {
    Fila fila;
    Historico hist;
    fila_inicializar(&fila);
    historico_inicializar(&hist);

    int op;
    do {
        printf("\n===== Gestao Sequencial - Colonia Submarina =====\n");
        printf("1. Cadastrar missao e enfileirar\n");
        printf("2. Listar fila de execucao\n");
        printf("3. Executar proxima missao (fila -> historico)\n");
        printf("4. Exibir historico (antigo -> recente)\n");
        printf("5. Exibir historico (recente -> antigo)\n");
        printf("6. Buscar missao no historico\n");
        printf("7. Remover registro do historico\n");
        printf("0. Sair\n");
        op = ler_int("Opcao: ", 0, 7);

        switch (op) {
            case 1: cadastrar_missao(&fila, &hist); break;
            case 2: fila_listar(&fila); break;
            case 3: executar_proxima(&fila, &hist); break;
            case 4: historico_exibir(&hist); break;
            case 5: historico_exibir_inverso(&hist); break;
            case 6: buscar_historico(&hist); break;
            case 7: remover_historico(&hist); break;
            default: break;
        }
    } while (op != 0);

    fila_liberar(&fila);
    historico_liberar(&hist);
    return 0;
}
