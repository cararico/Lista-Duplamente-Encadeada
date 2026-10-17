
#include <stdio.h>
#include <stdlib.h>

// Estrutura de cada no da lista
typedef struct No {
    int valor;
    struct No *anterior;
    struct No *proximo;
} No;

// Estrutura que controla o inicio e o fim da lista
typedef struct {
    No *inicio;
    No *fim;
    int tamanho;
} Lista;

// Inicializa a lista vazia
void inicializarLista(Lista *lista) {
    lista->inicio = NULL;
    lista->fim = NULL;
    lista->tamanho = 0;
}

// Cria um novo no
No *criarNo(int valor) {
    No *novo = malloc(sizeof(No));

    if (novo == NULL) {
        printf("Erro: memoria insuficiente!\n");
        return NULL;
    }

    novo->valor = valor;
    novo->anterior = NULL;
    novo->proximo = NULL;

    return novo;
}

// Insere um elemento no inicio
void inserirInicio(Lista *lista, int valor) {
    No *novo = criarNo(valor);

    if (novo == NULL) {
        return;
    }

    novo->proximo = lista->inicio;

    if (lista->inicio != NULL) {
        lista->inicio->anterior = novo;
    } else {
        lista->fim = novo;
    }

    lista->inicio = novo;
    lista->tamanho++;

    printf("Elemento inserido no inicio!\n");
}

// Insere um elemento no final
void inserirFinal(Lista *lista, int valor) {
    No *novo = criarNo(valor);

    if (novo == NULL) {
        return;
    }

    novo->anterior = lista->fim;

    if (lista->fim != NULL) {
        lista->fim->proximo = novo;
    } else {
        lista->inicio = novo;
    }

    lista->fim = novo;
    lista->tamanho++;

    printf("Elemento inserido no final!\n");
}

// Insere um elemento em uma posicao especifica
void inserirPosicao(Lista *lista, int valor, int posicao) {
    if (posicao < 1 || posicao > lista->tamanho + 1) {
        printf("Posicao invalida!\n");
        return;
    }

    if (posicao == 1) {
        inserirInicio(lista, valor);
        return;
    }

    if (posicao == lista->tamanho + 1) {
        inserirFinal(lista, valor);
        return;
    }

    No *atual = lista->inicio;

    for (int i = 1; i < posicao; i++) {
        atual = atual->proximo;
    }

    No *novo = criarNo(valor);

    if (novo == NULL) {
        return;
    }

    novo->anterior = atual->anterior;
    novo->proximo = atual;

    atual->anterior->proximo = novo;
    atual->anterior = novo;

    lista->tamanho++;

    printf("Elemento inserido na posicao %d!\n", posicao);
}

// Remove um elemento de uma posicao especifica
void removerPosicao(Lista *lista, int posicao) {
    if (posicao < 1 || posicao > lista->tamanho) {
        printf("Posicao invalida ou lista vazia!\n");
        return;
    }

    No *atual = lista->inicio;

    for (int i = 1; i < posicao; i++) {
        atual = atual->proximo;
    }

    if (atual->anterior != NULL) {
        atual->anterior->proximo = atual->proximo;
    } else {
        lista->inicio = atual->proximo;
    }

    if (atual->proximo != NULL) {
        atual->proximo->anterior = atual->anterior;
    } else {
        lista->fim = atual->anterior;
    }

    free(atual);
    lista->tamanho--;

    printf("Elemento removido com sucesso!\n");
}

// Busca um valor e retorna sua posicao ou -1
int buscarValor(Lista *lista, int valor) {
    No *atual = lista->inicio;
    int posicao = 1;

    while (atual != NULL) {
        if (atual->valor == valor) {
            return posicao;
        }

        atual = atual->proximo;
        posicao++;
    }

    return -1;
}

// Lista todos os elementos e seus ponteiros
void listarLista(Lista *lista) {
    No *atual = lista->inicio;
    int posicao = 1;

    if (atual == NULL) {
        printf("\nA lista esta vazia!\n");
        return;
    }

    printf("\n===== ELEMENTOS DA LISTA =====\n");

    while (atual != NULL) {
        printf("Posicao: %d | Valor: %d | Anterior: ",
               posicao, atual->valor);

        if (atual->anterior != NULL) {
            printf("%d", atual->anterior->valor);
        } else {
            printf("NULL");
        }

        printf(" | Proximo: ");

        if (atual->proximo != NULL) {
            printf("%d", atual->proximo->valor);
        } else {
            printf("NULL");
        }

        printf("\n");

        atual = atual->proximo;
        posicao++;
    }

    printf("==============================\n");
}

// Libera toda a memoria da lista
void liberarLista(Lista *lista) {
    No *atual = lista->inicio;

    while (atual != NULL) {
        No *temporario = atual;
        atual = atual->proximo;
        free(temporario);
    }

    lista->inicio = NULL;
    lista->fim = NULL;
    lista->tamanho = 0;
}

// Programa principal e menu
int main(void) {
    Lista lista;
    int opcao, valor, posicao;

    inicializarLista(&lista);

    do {
        printf("\n===== MENU LISTA DUPLAMENTE ENCADEADA =====\n");
        printf("1 - Inserir no inicio\n");
        printf("2 - Inserir em uma posicao especifica\n");
        printf("3 - Inserir no final\n");
        printf("4 - Remover de uma posicao\n");
        printf("5 - Buscar valor\n");
        printf("6 - Listar elementos\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");

        if (scanf("%d", &opcao) != 1) {
            printf("Entrada invalida!\n");
            break;
        }

        switch (opcao) {
            case 1:
                printf("Digite o valor: ");
                if (scanf("%d", &valor) != 1) {
                    printf("Entrada invalida!\n");
                    liberarLista(&lista);
                    return 1;
                }
                inserirInicio(&lista, valor);
                break;

            case 2:
                printf("Digite o valor: ");
                if (scanf("%d", &valor) != 1) {
                    printf("Entrada invalida!\n");
                    liberarLista(&lista);
                    return 1;
                }

                printf("Digite a posicao (1 a %d): ",
                       lista.tamanho + 1);

                if (scanf("%d", &posicao) != 1) {
                    printf("Entrada invalida!\n");
                    liberarLista(&lista);
                    return 1;
                }

                inserirPosicao(&lista, valor, posicao);
                break;

            case 3:
                printf("Digite o valor: ");
                if (scanf("%d", &valor) != 1) {
                    printf("Entrada invalida!\n");
                    liberarLista(&lista);
                    return 1;
                }
                inserirFinal(&lista, valor);
                break;

            case 4:
                printf("Digite a posicao a remover: ");
                if (scanf("%d", &posicao) != 1) {
                    printf("Entrada invalida!\n");
                    liberarLista(&lista);
                    return 1;
                }
                removerPosicao(&lista, posicao);
                break;

            case 5:
                printf("Digite o valor a buscar: ");
                if (scanf("%d", &valor) != 1) {
                    printf("Entrada invalida!\n");
                    liberarLista(&lista);
                    return 1;
                }

                posicao = buscarValor(&lista, valor);

                if (posicao != -1) {
                    printf("Valor encontrado na posicao %d!\n",
                           posicao);
                } else {
                    printf("Valor nao encontrado!\n");
                }
                break;

            case 6:
                listarLista(&lista);
                break;

            case 0:
                printf("Encerrando o programa...\n");
                break;

            default:
                printf("Opcao invalida! Tente novamente.\n");
        }

    } while (opcao != 0);

    liberarLista(&lista);

    return 0;
}
