#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_COMPONENTES 20

// ==================== STRUCT ====================

struct Componente {
    char nome[30];
    char tipo[20];
    int prioridade;
};

// ==================== VARIÁVEIS GLOBAIS ====================

long comparacoes;
double tempoExecucao;
int ordenadoPorNome = 0;

// ==================== CADASTRO ====================

void cadastrarComponente(struct Componente componentes[], int *total) {

    if (*total >= MAX_COMPONENTES) {
        printf("\nLimite maximo de componentes atingido!\n");
        return;
    }

    printf("\nNome do componente: ");
    scanf(" %[^\n]", componentes[*total].nome);

    printf("Tipo do componente: ");
    scanf(" %[^\n]", componentes[*total].tipo);

    printf("Prioridade (1 a 10): ");
    scanf("%d", &componentes[*total].prioridade);

    (*total)++;

    ordenadoPorNome = 0;

    printf("\nComponente cadastrado com sucesso!\n");
}

// ==================== LISTAGEM ====================

void listarComponentes(struct Componente componentes[], int total) {

    if (total == 0) {
        printf("\nNenhum componente cadastrado!\n");
        return;
    }

    printf("\n===== COMPONENTES CADASTRADOS =====\n");

    for (int i = 0; i < total; i++) {

        printf("\nComponente %d\n", i + 1);
        printf("Nome: %s\n", componentes[i].nome);
        printf("Tipo: %s\n", componentes[i].tipo);
        printf("Prioridade: %d\n", componentes[i].prioridade);
    }
}

// ==================== BUBBLE SORT (NOME) ====================

void bubbleSortNome(struct Componente componentes[], int total) {

    comparacoes = 0;

    clock_t inicio = clock();

    struct Componente aux;

    for (int i = 0; i < total - 1; i++) {

        for (int j = 0; j < total - i - 1; j++) {

            comparacoes++;

            if (strcmp(componentes[j].nome,
                       componentes[j + 1].nome) > 0) {

                aux = componentes[j];
                componentes[j] = componentes[j + 1];
                componentes[j + 1] = aux;
            }
        }
    }

    clock_t fim = clock();

    tempoExecucao =
        (double)(fim - inicio) / CLOCKS_PER_SEC;

    ordenadoPorNome = 1;

    printf("\n===== BUBBLE SORT (NOME) =====\n");
    printf("Comparacoes: %ld\n", comparacoes);
    printf("Tempo: %.6f segundos\n", tempoExecucao);
}

// ==================== INSERTION SORT (TIPO) ====================

void insertionSortTipo(struct Componente componentes[],
                       int total) {

    comparacoes = 0;

    clock_t inicio = clock();

    for (int i = 1; i < total; i++) {

        struct Componente chave = componentes[i];
        int j = i - 1;

        while (j >= 0 &&
               strcmp(componentes[j].tipo,
                      chave.tipo) > 0) {

            comparacoes++;

            componentes[j + 1] = componentes[j];

            j--;
        }

        comparacoes++;

        componentes[j + 1] = chave;
    }

    clock_t fim = clock();

    tempoExecucao =
        (double)(fim - inicio) / CLOCKS_PER_SEC;

    ordenadoPorNome = 0;

    printf("\n===== INSERTION SORT (TIPO) =====\n");
    printf("Comparacoes: %ld\n", comparacoes);
    printf("Tempo: %.6f segundos\n", tempoExecucao);
}

// ==================== SELECTION SORT (PRIORIDADE) ====================

void selectionSortPrioridade(struct Componente componentes[],
                             int total) {

    comparacoes = 0;

    clock_t inicio = clock();

    struct Componente aux;

    for (int i = 0; i < total - 1; i++) {

        int menor = i;

        for (int j = i + 1; j < total; j++) {

            comparacoes++;

            if (componentes[j].prioridade <
                componentes[menor].prioridade) {

                menor = j;
            }
        }

        aux = componentes[i];
        componentes[i] = componentes[menor];
        componentes[menor] = aux;
    }

    clock_t fim = clock();

    tempoExecucao =
        (double)(fim - inicio) / CLOCKS_PER_SEC;

    ordenadoPorNome = 0;

    printf("\n===== SELECTION SORT (PRIORIDADE) =====\n");
    printf("Comparacoes: %ld\n", comparacoes);
    printf("Tempo: %.6f segundos\n", tempoExecucao);
}

// ==================== BUSCA BINÁRIA ====================

void buscaBinaria(struct Componente componentes[],
                  int total) {

    if (!ordenadoPorNome) {

        printf("\nA busca binaria so funciona apos ordenar por nome!\n");
        return;
    }

    char chave[30];

    printf("\nDigite o componente-chave: ");
    scanf(" %[^\n]", chave);

    int inicio = 0;
    int fim = total - 1;
    int encontrado = 0;

    while (inicio <= fim) {

        int meio = (inicio + fim) / 2;

        int resultado =
            strcmp(chave, componentes[meio].nome);

        if (resultado == 0) {

            printf("\n===== COMPONENTE ENCONTRADO =====\n");
            printf("Nome: %s\n", componentes[meio].nome);
            printf("Tipo: %s\n", componentes[meio].tipo);
            printf("Prioridade: %d\n",
                   componentes[meio].prioridade);

            encontrado = 1;
            break;
        }

        if (resultado > 0)
            inicio = meio + 1;
        else
            fim = meio - 1;
    }

    if (!encontrado) {
        printf("\nComponente nao encontrado!\n");
    }
}

// ==================== CONFIRMAÇÃO FINAL ====================

void confirmarComponenteChave(struct Componente componentes[],
                              int total) {

    char chave[30];
    int encontrado = 0;

    printf("\nDigite o componente-chave para verificar: ");
    scanf(" %[^\n]", chave);

    for (int i = 0; i < total; i++) {

        if (strcmp(chave, componentes[i].nome) == 0) {

            encontrado = 1;
            break;
        }
    }

    if (encontrado)
        printf("\nComponente-chave presente. Torre pronta para montagem!\n");
    else
        printf("\nComponente-chave nao encontrado.\n");
}

// ==================== MENU ====================

int main() {

    struct Componente componentes[MAX_COMPONENTES];

    int total = 0;
    int opcao;

    do {

        printf("\n=====================================\n");
        printf(" SISTEMA DE MONTAGEM DA TORRE\n");
        printf("=====================================\n");
        printf("1 - Cadastrar componente\n");
        printf("2 - Listar componentes\n");
        printf("3 - Ordenar por nome (Bubble Sort)\n");
        printf("4 - Ordenar por tipo (Insertion Sort)\n");
        printf("5 - Ordenar por prioridade (Selection Sort)\n");
        printf("6 - Buscar componente-chave\n");
        printf("7 - Confirmar componente-chave\n");
        printf("0 - Sair\n");
        printf("Opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {

            case 1:
                cadastrarComponente(componentes, &total);
                break;

            case 2:
                listarComponentes(componentes, total);
                break;

            case 3:
                bubbleSortNome(componentes, total);
                break;

            case 4:
                insertionSortTipo(componentes, total);
                break;

            case 5:
                selectionSortPrioridade(componentes, total);
                break;

            case 6:
                buscaBinaria(componentes, total);
                break;

            case 7:
                confirmarComponenteChave(componentes, total);
                break;

            case 0:
                printf("\nEncerrando programa...\n");
                break;

            default:
                printf("\nOpcao invalida!\n");
        }

    } while (opcao != 0);

    return 0;
}