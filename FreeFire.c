#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_ITENS 10

// Estrutura base dos itens
typedef struct {
    char nome[50];
    char tipo[50];
    int quantidade;
    int prioridade; // usado apenas no nível mestre
} Item;

Item mochila[MAX_ITENS];
int totalItens = 0;
bool ordenadoPorNome = false;

// -------- Funções Comuns --------
void listarItens() {
    if (totalItens == 0) {
        printf("\n📦 Mochila vazia!\n");
        return;
    }
    printf("\n📋 Itens na mochila:\n");
    printf("%-20s %-15s %-10s %-10s\n", "Nome", "Tipo", "Qtd", "Prioridade");
    for (int i = 0; i < totalItens; i++) {
        printf("%-20s %-15s %-10d %-10d\n",
               mochila[i].nome, mochila[i].tipo, mochila[i].quantidade, mochila[i].prioridade);
    }
}

// -------- Nível Novato --------
void adicionarItem() {
    if (totalItens >= MAX_ITENS) {
        printf("\n⚠️ Mochila cheia!\n");
        return;
    }
    printf("\nDigite o nome do item: ");
    scanf(" %[^\n]", mochila[totalItens].nome);
    printf("Digite o tipo do item: ");
    scanf(" %[^\n]", mochila[totalItens].tipo);
    printf("Digite a quantidade: ");
    scanf("%d", &mochila[totalItens].quantidade);
    mochila[totalItens].prioridade = 0;
    totalItens++;
    printf("\n✅ Item adicionado com sucesso!\n");
}

void removerItem() {
    char nome[50];
    printf("\nDigite o nome do item que deseja remover: ");
    scanf(" %[^\n]", nome);

    for (int i = 0; i < totalItens; i++) {
        if (strcmp(mochila[i].nome, nome) == 0) {
            for (int j = i; j < totalItens - 1; j++) {
                mochila[j] = mochila[j + 1];
            }
            totalItens--;
            printf("\n🗑️ Item removido com sucesso!\n");
            return;
        }
    }
    printf("\n❌ Item não encontrado.\n");
}

// -------- Nível Aventureiro --------
void buscarItemSequencial() {
    char nome[50];
    printf("\nDigite o nome do item que deseja buscar: ");
    scanf(" %[^\n]", nome);
    bool encontrado = false;

    for (int i = 0; i < totalItens; i++) {
        if (strcmp(mochila[i].nome, nome) == 0) {
            printf("\n🔍 Item encontrado:\n");
            printf("Nome: %s\nTipo: %s\nQuantidade: %d\n", 
                   mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
            encontrado = true;
            break;
        }
    }

    if (!encontrado)
        printf("\n❌ Item não encontrado!\n");
}

// -------- Nível Mestre --------
void adicionarItemComPrioridade() {
    if (totalItens >= MAX_ITENS) {
        printf("\n⚠️ Mochila cheia!\n");
        return;
    }
    printf("\nDigite o nome do item: ");
    scanf(" %[^\n]", mochila[totalItens].nome);
    printf("Digite o tipo do item: ");
    scanf(" %[^\n]", mochila[totalItens].tipo);
    printf("Digite a quantidade: ");
    scanf("%d", &mochila[totalItens].quantidade);
    printf("Digite a prioridade (1 a 5): ");
    scanf("%d", &mochila[totalItens].prioridade);
    totalItens++;
    ordenadoPorNome = false;
    printf("\n✅ Item adicionado com sucesso!\n");
}

// Ordenação (Insertion Sort)
void ordenarPorNome(int *comparacoes) {
    *comparacoes = 0;
    for (int i = 1; i < totalItens; i++) {
        Item chave = mochila[i];
        int j = i - 1;
        while (j >= 0 && strcmp(mochila[j].nome, chave.nome) > 0) {
            mochila[j + 1] = mochila[j];
            j--;
            (*comparacoes)++;
        }
        mochila[j + 1] = chave;
    }
    ordenadoPorNome = true;
}

void ordenarPorTipo(int *comparacoes) {
    *comparacoes = 0;
    for (int i = 1; i < totalItens; i++) {
        Item chave = mochila[i];
        int j = i - 1;
        while (j >= 0 && strcmp(mochila[j].tipo, chave.tipo) > 0) {
            mochila[j + 1] = mochila[j];
            j--;
            (*comparacoes)++;
        }
        mochila[j + 1] = chave;
    }
    ordenadoPorNome = false;
}

void ordenarPorPrioridade(int *comparacoes) {
    *comparacoes = 0;
    for (int i = 1; i < totalItens; i++) {
        Item chave = mochila[i];
        int j = i - 1;
        while (j >= 0 && mochila[j].prioridade > chave.prioridade) {
            mochila[j + 1] = mochila[j];
            j--;
            (*comparacoes)++;
        }
        mochila[j + 1] = chave;
    }
    ordenadoPorNome = false;
}

void menuOrdenacao() {
    int opcao, comparacoes;
    printf("\nEscolha o critério de ordenação:\n");
    printf("1 - Nome\n2 - Tipo\n3 - Prioridade\n> ");
    scanf("%d", &opcao);

    switch (opcao) {
        case 1: ordenarPorNome(&comparacoes); break;
        case 2: ordenarPorTipo(&comparacoes); break;
        case 3: ordenarPorPrioridade(&comparacoes); break;
        default: printf("\n❌ Opção inválida.\n"); return;
    }
    printf("\n✅ Itens ordenados com sucesso!\n");
    printf("🔢 Comparações realizadas: %d\n", comparacoes);
}

// Busca binária (somente se estiver ordenado por nome)
void buscarItemBinario() {
    if (!ordenadoPorNome) {
        printf("\n⚠️ A lista deve estar ordenada por nome antes da busca binária!\n");
        return;
    }

    char nome[50];
    printf("\nDigite o nome do item para busca binária: ");
    scanf(" %[^\n]", nome);

    int inicio = 0, fim = totalItens - 1;
    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;
        int cmp = strcmp(mochila[meio].nome, nome);
        if (cmp == 0) {
            printf("\n🎯 Item encontrado:\n");
            printf("Nome: %s\nTipo: %s\nQtd: %d\nPrioridade: %d\n",
                   mochila[meio].nome, mochila[meio].tipo,
                   mochila[meio].quantidade, mochila[meio].prioridade);
            return;
        } else if (cmp < 0)
            inicio = meio + 1;
        else
            fim = meio - 1;
    }

    printf("\n❌ Item não encontrado.\n");
}

// -------- Menus de Níveis --------
void menuNovato() {
    int opcao;
    do {
        printf("\n=== 🪓 NÍVEL NOVATO ===\n");
        printf("1 - Adicionar item\n2 - Remover item\n3 - Listar itens\n0 - Voltar\n> ");
        scanf("%d", &opcao);
        switch (opcao) {
            case 1: adicionarItem(); break;
            case 2: removerItem(); break;
            case 3: listarItens(); break;
            case 0: break;
            default: printf("\n❌ Opção inválida.\n");
        }
    } while (opcao != 0);
}

void menuAventureiro() {
    int opcao;
    do {
        printf("\n=== 🏹 NÍVEL AVENTUREIRO ===\n");
        printf("1 - Adicionar item\n2 - Remover item\n3 - Listar itens\n4 - Buscar item\n0 - Voltar\n> ");
        scanf("%d", &opcao);
        switch (opcao) {
            case 1: adicionarItem(); break;
            case 2: removerItem(); break;
            case 3: listarItens(); break;
            case 4: buscarItemSequencial(); break;
            case 0: break;
            default: printf("\n❌ Opção inválida.\n");
        }
    } while (opcao != 0);
}

void menuMestre() {
    int opcao;
    do {
        printf("\n=== 🧙 NÍVEL MESTRE ===\n");
        printf("1 - Adicionar item (com prioridade)\n2 - Listar itens\n3 - Ordenar itens\n4 - Buscar binário\n0 - Voltar\n> ");
        scanf("%d", &opcao);
        switch (opcao) {
            case 1: adicionarItemComPrioridade(); break;
            case 2: listarItens(); break;
            case 3: menuOrdenacao(); break;
            case 4: buscarItemBinario(); break;
            case 0: break;
            default: printf("\n❌ Opção inválida.\n");
        }
    } while (opcao != 0);
}

// -------- Função Principal --------
int main() {
    int nivel;
    do {
        printf("\n=== 🏝️ DESAFIO CÓDIGO DA ILHA – FREE FIRE ===\n");
        printf("Escolha o nível:\n");
        printf("1 - Novato\n2 - Aventureiro\n3 - Mestre\n0 - Sair\n> ");
        scanf("%d", &nivel);

        switch (nivel) {
            case 1: menuNovato(); break;
            case 2: menuAventureiro(); break;
            case 3: menuMestre(); break;
            case 0: printf("\nSaindo do jogo... 🏁\n"); break;
            default: printf("\n❌ Opção inválida.\n");
        }
    } while (nivel != 0);

    return 0;
}
