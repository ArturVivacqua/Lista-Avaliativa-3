//Exercício 2
#include <stdio.h>
#include <stdlib.h>

typedef struct Dieta {
    char nome[100];
    float calorias;
    float peso;
    struct Dieta* proximo;
} Dieta;

void flush_stdin() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

Dieta* criar() {
    Dieta* ndieta = (Dieta*)malloc(sizeof(Dieta));
    if (ndieta == NULL) {
        printf("Erro ao alocar memória!\n");
        exit(1);
    }
    ndieta->proximo = NULL;
    return ndieta;
}

void adicionar(Dieta** lista) {
    Dieta* ndieta = criar();
    
    printf("\nDigite o nome do alimento/prato:\t");
    fgets( ndieta->nome, sizeof(ndieta->nome), stdin);

    printf("\nDigite o número de calorias da refeição:\t");
    scanf("%f", &ndieta->calorias);

    printf("\nDigite o peso da comida(em gramas):\t");
    scanf("%f", &ndieta->peso);
    
    printf("\n");
    
    if (*lista == NULL) {
        *lista = ndieta;
    } else {
        Dieta* temp = *lista;
        while (temp->proximo != NULL) {
            temp = temp->proximo;
        }
        temp->proximo = ndieta;
    }
}

void listar(Dieta* lista) {
    Dieta* temp = lista;
    while (temp != NULL) {
        printf("Alimento: %s", temp->nome);
        printf("Calorias: %.2fkcal\n", temp->calorias);
        printf("Peso: %.2fg\n", temp->peso);
        printf("------------------------");
        printf("\n");
        temp = temp->proximo;
    }
  printf("\nDigite qualquer número para continuar.\n");
  flush_stdin();
  getchar();
}

int main() {
    Dieta* lista = NULL;
    int opcao;
    
    do {
        printf("1. Adicionar alimento\n");
        printf("2. Listar alimentos\n");
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
    Dieta* temp = lista;
    while (temp != NULL) {
        Dieta* proximo = temp->proximo;
        free(temp);
        temp = proximo;
    }
    
    return 0;
}
