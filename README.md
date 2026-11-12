# Sistema de Gerenciamento de Missões em uma Colônia Submarina (C)

Trabalho de Estrutura de Dados (Estácio)
## O que está implementado

- **Fila de Execução** (FIFO, lista encadeada): organiza as missões aguardando execução.
- **Histórico** (lista duplamente encadeada): armazena as missões realizadas, com status
  (concluída ou falhou) e número de ordem.
- **Exibição do Histórico**: do mais antigo ao mais recente e do mais recente ao mais antigo.
- `main.c`: menu interativo que demonstra a fila e o histórico trabalhando juntos.

> A struct `Missao` em `missao.h` é **provisória**. Deve ser substituída pela versão
> oficial do integrante responsável. Fila e histórico só dependem do campo `codigo`
> e da função `missao_imprimir`.

## Arquivos

| Arquivo | Descrição |
|---|---|
| `missao.h` / `missao.c` | Struct `Missao` e função de impressão |
| `fila.h` / `fila.c` | Fila de execução |
| `historico.h` / `historico.c` | Histórico (lista duplamente encadeada) e exibição |
| `main.c` | Menu de demonstração |

## Como compilar e executar

Requer um compilador C (por exemplo GCC/MinGW).

```
gcc -std=c99 -Wall -Wextra -o gestao main.c missao.c fila.c historico.c
```

Executar:

- Git Bash / Linux / macOS: `./gestao`
- PowerShell / CMD: `.\gestao.exe`

## Menu

| Opção | Ação |
|---|---|
| 1 | Cadastrar missão e enfileirar (códigos repetidos são recusados) |
| 2 | Listar a fila de execução |
| 3 | Executar a próxima missão (sai da fila, entra no histórico como concluída ou falhou) |
| 4 | Exibir histórico, do mais antigo ao mais recente |
| 5 | Exibir histórico, do mais recente ao mais antigo |
| 6 | Buscar missão no histórico por código |
| 7 | Remover um registro do histórico |
| 0 | Sair |

## Complexidade

| Operação | Custo |
|---|---|
| Enfileirar / desenfileirar | O(1) |
| Inserir no histórico | O(1) |
| Buscar na fila / no histórico | O(n) |
| Remover do histórico | O(n) para achar, O(1) para desligar o nó |
