#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ITENS 10

// ==================== STRUCTS ====================

struct Item {
    char nome[30];
    char tipo[20];
    int quantidade;
};

struct No {
    struct Item dados;
    struct No *proximo;
};

// ==================== CONTADORES ====================

int comparacoesSequencial = 0;
int comparacoesBinaria = 0;

// ==================== VETOR ====================

void inserirItemVetor(struct Item mochila[], int *totalItens) {

    if (*totalItens >= MAX_ITENS) {
        printf("Mochila cheia!\n");
        return;
    }

    printf("Nome: ");
    scanf("%s", mochila[*totalItens].nome);

    printf("Tipo: ");
    scanf("%s", mochila[*totalItens].tipo);

    printf("Quantidade: ");
    scanf("%d", &mochila[*totalItens].quantidade);

    (*totalItens)++;

    printf("Item inserido com sucesso!\n");
}

void listarItensVetor(struct Item mochila[], int totalItens) {

    if (totalItens == 0) {
        printf("Mochila vazia!\n");
        return;
    }

    printf("\n===== ITENS NO VETOR =====\n");

    for (int i = 0; i < totalItens; i++) {
        printf("%d - Nome: %s | Tipo: %s | Quantidade: %d\n",
               i + 1,
               mochila[i].nome,
               mochila[i].tipo,
               mochila[i].quantidade);
    }
}

void removerItemVetor(struct Item mochila[], int *totalItens) {

    char nome[30];
    int encontrado = 0;

    printf("Nome do item para remover: ");
    scanf("%s", nome);

    for (int i = 0; i < *totalItens; i++) {

        if (strcmp(nome, mochila[i].nome) == 0) {

            for (int j = i; j < *totalItens - 1; j++) {
                mochila[j] = mochila[j + 1];
            }

            (*totalItens)--;

            encontrado = 1;

            printf("Item removido!\n");
            break;
        }
    }

    if (!encontrado)
        printf("Item nao encontrado!\n");
}

void buscarSequencialVetor(struct Item mochila[], int totalItens) {

    char nome[30];
    int encontrado = 0;

    comparacoesSequencial = 0;

    printf("Nome do item: ");
    scanf("%s", nome);

    for (int i = 0; i < totalItens; i++) {

        comparacoesSequencial++;

        if (strcmp(nome, mochila[i].nome) == 0) {

            printf("\nItem encontrado!\n");
            printf("Nome: %s\n", mochila[i].nome);
            printf("Tipo: %s\n", mochila[i].tipo);
            printf("Quantidade: %d\n", mochila[i].quantidade);

            encontrado = 1;
            break;
        }
    }

    if (!encontrado)
        printf("Item nao encontrado!\n");

    printf("Comparacoes realizadas: %d\n", comparacoesSequencial);
}

void ordenarVetor(struct Item mochila[], int totalItens) {

    struct Item aux;

    for (int i = 0; i < totalItens - 1; i++) {

        for (int j = 0; j < totalItens - i - 1; j++) {

            if (strcmp(mochila[j].nome, mochila[j + 1].nome) > 0) {

                aux = mochila[j];
                mochila[j] = mochila[j + 1];
                mochila[j + 1] = aux;
            }
        }
    }

    printf("Itens ordenados!\n");
}

void buscarBinariaVetor(struct Item mochila[], int totalItens) {

    char nome[30];

    printf("Nome do item: ");
    scanf("%s", nome);

    int inicio = 0;
    int fim = totalItens - 1;
    int encontrado = 0;

    comparacoesBinaria = 0;

    while (inicio <= fim) {

        int meio = (inicio + fim) / 2;

        comparacoesBinaria++;

        int resultado = strcmp(nome, mochila[meio].nome);

        if (resultado == 0) {

            printf("\nItem encontrado!\n");
            printf("Nome: %s\n", mochila[meio].nome);
            printf("Tipo: %s\n", mochila[meio].tipo);
            printf("Quantidade: %d\n", mochila[meio].quantidade);

            encontrado = 1;
            break;
        }

        if (resultado > 0)
            inicio = meio + 1;
        else
            fim = meio - 1;
    }

    if (!encontrado)
        printf("Item nao encontrado!\n");

    printf("Comparacoes realizadas: %d\n", comparacoesBinaria);
}

// ==================== LISTA ENCADEADA ====================

void inserirItemLista(struct No **inicio) {

    struct No *novo = malloc(sizeof(struct No));

    printf("Nome: ");
    scanf("%s", novo->dados.nome);

    printf("Tipo: ");
    scanf("%s", novo->dados.tipo);

    printf("Quantidade: ");
    scanf("%d", &novo->dados.quantidade);

    novo->proximo = *inicio;
    *inicio = novo;

    printf("Item inserido!\n");
}

void listarItensLista(struct No *inicio) {

    if (inicio == NULL) {
        printf("Lista vazia!\n");
        return;
    }

    printf("\n===== ITENS NA LISTA =====\n");

    struct No *aux = inicio;

    while (aux != NULL) {

        printf("Nome: %s | Tipo: %s | Quantidade: %d\n",
               aux->dados.nome,
               aux->dados.tipo,
               aux->dados.quantidade);

        aux = aux->proximo;
    }
}

void buscarLista(struct No *inicio) {

    char nome[30];

    printf("Nome do item: ");
    scanf("%s", nome);

    comparacoesSequencial = 0;

    struct No *aux = inicio;

    while (aux != NULL) {

        comparacoesSequencial++;

        if (strcmp(aux->dados.nome, nome) == 0) {

            printf("\nItem encontrado!\n");
            printf("Nome: %s\n", aux->dados.nome);
            printf("Tipo: %s\n", aux->dados.tipo);
            printf("Quantidade: %d\n", aux->dados.quantidade);

            printf("Comparacoes realizadas: %d\n",
                   comparacoesSequencial);

            return;
        }

        aux = aux->proximo;
    }

    printf("Item nao encontrado!\n");
    printf("Comparacoes realizadas: %d\n",
           comparacoesSequencial);
}

void removerLista(struct No **inicio) {

    char nome[30];

    printf("Nome do item para remover: ");
    scanf("%s", nome);

    struct No *atual = *inicio;
    struct No *anterior = NULL;

    while (atual != NULL &&
           strcmp(atual->dados.nome, nome) != 0) {

        anterior = atual;
        atual = atual->proximo;
    }

    if (atual == NULL) {
        printf("Item nao encontrado!\n");
        return;
    }

    if (anterior == NULL)
        *inicio = atual->proximo;
    else
        anterior->proximo = atual->proximo;

    free(atual);

    printf("Item removido!\n");
}

void liberarLista(struct No *inicio) {

    struct No *aux;

    while (inicio != NULL) {

        aux = inicio;
        inicio = inicio->proximo;

        free(aux);
    }
}

// ==================== MENUS ====================

void menuVetor(struct Item mochila[], int *totalItens) {

    int opcao;

    do {

        printf("\n===== MOCHILA VETOR =====\n");
        printf("1 - Inserir item\n");
        printf("2 - Remover item\n");
        printf("3 - Listar itens\n");
        printf("4 - Busca sequencial\n");
        printf("5 - Ordenar vetor\n");
        printf("6 - Busca binaria\n");
        printf("0 - Voltar\n");
        printf("Opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {

            case 1:
                inserirItemVetor(mochila, totalItens);
                break;

            case 2:
                removerItemVetor(mochila, totalItens);
                break;

            case 3:
                listarItensVetor(mochila, *totalItens);
                break;

            case 4:
                buscarSequencialVetor(mochila, *totalItens);
                break;

            case 5:
                ordenarVetor(mochila, *totalItens);
                break;

            case 6:
                buscarBinariaVetor(mochila, *totalItens);
                break;
        }

    } while (opcao != 0);
}

void menuLista(struct No **lista) {

    int opcao;

    do {

        printf("\n===== MOCHILA LISTA =====\n");
        printf("1 - Inserir item\n");
        printf("2 - Remover item\n");
        printf("3 - Listar itens\n");
        printf("4 - Buscar item\n");
        printf("0 - Voltar\n");
        printf("Opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {

            case 1:
                inserirItemLista(lista);
                break;

            case 2:
                removerLista(lista);
                break;

            case 3:
                listarItensLista(*lista);
                break;

            case 4:
                buscarLista(*lista);
                break;
        }

    } while (opcao != 0);
}

// ==================== MAIN ====================

int main() {

    struct Item mochila[MAX_ITENS];
    int totalItens = 0;

    struct No *lista = NULL;

    int opcao;

    do {

        printf("\n========== MENU PRINCIPAL ==========\n");
        printf("1 - Mochila usando Vetor\n");
        printf("2 - Mochila usando Lista Encadeada\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {

            case 1:
                menuVetor(mochila, &totalItens);
                break;

            case 2:
                menuLista(&lista);
                break;

            case 0:
                printf("Encerrando programa...\n");
                break;

            default:
                printf("Opcao invalida!\n");
        }

    } while (opcao != 0);

    liberarLista(lista);

    return 0;
}