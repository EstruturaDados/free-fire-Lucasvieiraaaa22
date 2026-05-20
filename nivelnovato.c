#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct item {
    char nome[30];
    char tipo[20];
    int quantidade;

};
        //listar todos os itens

    void listarItens(struct item mochilha[], int totalItens) {
         
            printf("\n ===== Itens na mochilha =====\n");

            // Verificar se a mochila está vazia
            if (totalItens == 0) {
                printf("A mochila está vazia.\n");
                return;
            }

        /* Percorre o vetor mostrando os itens*/

            for (int i = 0; i < totalItens; i++){

                printf("%d. Nome: %s | Tipo: %s | Quantidade: %d\n", i + 1, mochilha[i].nome, mochilha[i].tipo, mochilha[i].quantidade);
            }
    }

    
 /*Inserir Item*/

    void inserirItem(struct item mochila[], int * totalItens){

        /*Verifica se a mochila está cheia*/
    if (*totalItens >= 10) {
        printf("A mochila está cheia");

    return;
    }

    printf("\n ==== Inserir Item ====\n");

    printf("Digite o nome do item: ");
    scanf("%s", mochila[*totalItens].nome);

    printf("Digite o tipo do item: ");
    scanf("%s", mochila[*totalItens].tipo);

    printf("Digite a quantidade do item: ");
    scanf("%d", &mochila[*totalItens].quantidade);

    (*totalItens)++;

    printf("Item inserido com sucesso!\n");

    }

    /*Busca Sequencial*/

    void buscarItem(struct item mochila[], int totalItens){

        char nomeBusca[30];
        int encontrado = 0;

        printf("\n ==== Buscar Item ====\n");

        printf("Digite o nome do item que deseja buscar: ");
        scanf("%s", nomeBusca);

        /*Percorre buscando o item*/

        for (int i = 0; i < totalItens; i++) {

            /*Strcmp compara strings*/
            if (strcmp(nomeBusca, mochila[i].nome) == 0){

                printf("Nome: %s\n", mochila[i].nome);
                printf("Tipo: %s\n", mochila[i].tipo);
                 printf("Quantidade: %d\n", mochila[i].quantidade);
                encontrado = 1;
                break;
            }
        }

        /* Caso não encontre*/
        if (encontrado == 0) {
            printf("Item não encontrado.\n");
        }
    }
  
    /* Função para remover Item*/

    void removerItem(struct item mochila[], int *totalItens){

        char nomeRemover[30];
        int encontrado = 0;

        printf("\n ==== Remover Item ====\n");

        printf("Digite o nome do item que deseja remover: ");
        scanf("%s", nomeRemover);

        /*Percorre buscando o item*/

        for (int i = 0; i < *totalItens; i++) {

            /*Strcmp compara strings*/
            if (strcmp(nomeRemover, mochila[i].nome) == 0){

                /*Desloca os itens para preencher o espaço vazio*/
                for (int j = i; j < *totalItens - 1; j++) {
                    mochila[j] = mochila[j + 1];
                }

                (*totalItens)--;
                printf("Item removido com sucesso!\n");
                encontrado = 1;
                break;
            }
        }

        if (encontrado == 0) {
            printf("Item não encontrado.\n");
        }
    }
int main () {

        struct item mochila[10];

        int totalItens = 0;
        int opcao;

        do {
                printf("\n========== MENU ==========\n");
        printf("1 - Inserir item\n");
        printf("2 - Remover item\n");
        printf("3 - Listar itens\n");
        printf("4 - Buscar item\n");
        printf("0 - Sair\n");

        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                inserirItem(mochila, &totalItens);
                break;
            case 2:
                removerItem(mochila, &totalItens);
                break;
            case 3:
                listarItens(mochila, totalItens);
                break;
            case 4:
                buscarItem(mochila, totalItens);
                break;
            case 0:
                printf("Saindo do programa...\n");
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
        }

        } while (opcao != 0);

        return 0;

        }