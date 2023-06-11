//Exercício 1
#include <stdio.h>
#include <stdlib.h>

typedef struct Restaurante {
    char nome[100];
    char endereco[100];
    float preco;
    char comida[100];
    struct Restaurante* proximo;
} Restaurante;

void flush_stdin() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

Restaurante* criar() {
    Restaurante* nrestaurante = (Restaurante*)malloc(sizeof(Restaurante));
    if (nrestaurante == NULL) {
        printf("Erro ao alocar memória!\n");
        exit(1);
    }
    nrestaurante->proximo = NULL;
    return nrestaurante;
}

void adicionar(Restaurante** lista) {
    Restaurante* nrestaurante = criar();
    
    printf("\nDigite o nome do restaurante:\t");
    fgets( nrestaurante->nome, sizeof(nrestaurante->nome), stdin);
    
    printf("\nDigite o endereço do restaurante:\t");
    fgets( nrestaurante->endereco, sizeof(nrestaurante->endereco), stdin);
  
    printf("\nDigite o tipo de comida do restaurante:\t");
    fgets( nrestaurante->comida, sizeof(nrestaurante->comida), stdin);

      printf("\nDigite o preço médio do restaurante:\t");
    scanf("%f", &nrestaurante->preco);
    
    printf("\n");
    
    if (*lista == NULL) {
        *lista = nrestaurante;
    } else {
        Restaurante* temp = *lista;
        while (temp->proximo != NULL) {
            temp = temp->proximo;
        }
        temp->proximo = nrestaurante;
    }
}

void listar(Restaurante* lista) {
    Restaurante* temp = lista;
    while (temp != NULL) {
        printf("Nome: %s", temp->nome);
        printf("Endereço: %s", temp->endereco);
        printf("Preço médio: %.2f\n", temp->preco);
        printf("Tipo de comida: %s", temp->comida);
        printf("------------------------");
        printf("\n");
        temp = temp->proximo;
    }
  printf("\nDigite qualquer número para continuar.\n");
  flush_stdin();
  getchar();
}

int main() {
    Restaurante* lista = NULL;
    int opcao;
    
    do {
        printf("1. Adicionar restaurante\n");
        printf("2. Listar restaurantes\n");
        printf("3. Sair\n");
        printf("\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar(); 
        printf("\033c");
        switch (opcao) {
            case 1:
                adicionar(&lista);
                break;
            case 2:
                listar(lista);
                break;
            case 3:
                printf("\nEncerrando o programa...\n");
                break;
            default:
                printf("\nOpção inválida! Tente novamente.\n");
        }
        printf("\033c");
        
    } while (opcao != 3);
    Restaurante* temp = lista;
    while (temp != NULL) {
        Restaurante* proximo = temp->proximo;
        free(temp);
        temp = proximo;
    }
    
    return 0;
}
