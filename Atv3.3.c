//Exercício 3
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <ctype.h>

typedef struct Veiculo {
    char proprietario[50];
    char combustivel[20];
    char modelo[50];
    char cor[20];
    char chassi[50];
    int ano;
    char placa[8];
    struct Veiculo* proximo;
} Veiculo;

void flush_stdin() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

int verificarletras(const char* str) {
    for (int i = 0; i < 3; i++) {
        if (!isalpha(str[i])) {
            return 0;
        }
    }
    return 1;
}

int verificardigitos(const char* str) {
    for (int i = 0; i < 4; i++) {
        if (!isdigit(str[i])) {
            return 0;
        }
    }
    return 1;
}

void verificarplaca(char* placa) {
    int valido = 0;
    do {
        printf("Digite a placa (3 letras seguidas por 4 números): ");
        scanf(" %[^\n]s", placa);

        if (strlen(placa) == 7 && verificarletras(placa) && verificardigitos(placa + 3)) {
            valido = 1;
        } else {
            printf("Placa inválida. Tente novamente.\n");
        }
    } while (!valido);
}


Veiculo* cadastrarveiculo(const char* proprietario, const char* combustivel, const char* modelo, const char* cor, const char* chassi, int ano, const char* placa) {
    Veiculo* nveiculo = (Veiculo*)malloc(sizeof(Veiculo));
    strcpy(nveiculo->proprietario, proprietario);
    strcpy(nveiculo->combustivel, combustivel);
    strcpy(nveiculo->modelo, modelo);
    strcpy(nveiculo->cor, cor);
    strcpy(nveiculo->chassi, chassi);
    nveiculo->ano = ano;
    strcpy(nveiculo->placa, placa);
    nveiculo->proximo = NULL;
    return nveiculo;
}

void adicionar(Veiculo** lista, Veiculo* nveiculo) {
    if (*lista == NULL) {
        *lista = nveiculo;
    } else {
        Veiculo* atual = *lista;
        while (atual->proximo != NULL) {
            atual = atual->proximo;
        }
        atual->proximo = nveiculo;
    }
}

void listarproprietarios(Veiculo* lista) {
    printf("Proprietarios de veiculos diesel a partir de 2010:\n");
    printf("\n");
    int encontrou = 0;
    while (lista != NULL) {
        if (lista->ano >= 2010 && strcmp(lista->combustivel, "diesel") == 0) {
            printf("%s\n", lista->proprietario);
            encontrou = 1;
        }
        lista = lista->proximo;
    }
    if (!encontrou) {
        printf("Nenhum veiculo encontrado.\n");
    }
  printf("\nAperte qualquer tecla para continuar.\n");
  flush_stdin();
  getchar();
}

void listarplacas(Veiculo* lista) {
    printf("Placas que comecam com J e terminam com 0, 2, 4 ou 7:\n");
    int encontrou = 0;
    while (lista != NULL) {
        char primeiraLetra = lista->placa[0];
        int comprimento = strlen(lista->placa);
        if ((comprimento == 7 && primeiraLetra == 'J') || (comprimento == 7 && primeiraLetra == 'j')) {
            int digitosValidos = 1;
            for (int i = 3; i < 7; i++) {
                if (!isdigit(lista->placa[i])) {
                    digitosValidos = 0;
                    break;
                }
            }
            if (digitosValidos) {
                int ultimodigito = lista->placa[6] - '0';
                if (ultimodigito == 0 || ultimodigito == 2 || ultimodigito == 4 || ultimodigito == 7) {
                    printf("%s - %s\n", lista->placa, lista->proprietario);
                    encontrou = 1;
                }
            }
        }
        lista = lista->proximo;
    }
    if (!encontrou) {
        printf("Nenhum veiculo encontrado.\n");
    }
    printf("\nAperte qualquer tecla para continuar.\n");
    flush_stdin();
    getchar();
}


void listarmodeloecor(Veiculo* lista) {
    printf("Modelo e cor dos veiculos com placa cuja segunda letra é vogal e a soma dos numeros é par:\n");
    int encontrou = 0;
    while (lista != NULL) {
        char letra2 = lista->placa[1];
        int soma = 0;
        for (int i = 3; i < 7; i++) {
            soma += lista->placa[i] - '0';
        }
        if (strchr("AEIOUaeiou", letra2) != NULL && soma % 2 == 0) {
            printf("Modelo: %s | Cor: %s\n", lista->modelo, lista->cor);
            encontrou = 1;
        }
        lista = lista->proximo;
    }
    if (!encontrou) {
        printf("Nenhum veiculo encontrado.\n");
    }
  printf("\nAperte qualquer tecla para continuar.\n");
  flush_stdin();
  getchar();
}

void trocarproprietario(Veiculo** lista, const char* chassi, const char* nproprietario) {
    int encontrou = 0;
    Veiculo* atual = *lista;
    while (atual != NULL) {
        if (strcmp(atual->chassi, chassi) == 0 && strcspn(atual->placa, "0") == strlen(atual->placa)) {
            strcpy(atual->proprietario, nproprietario);
            encontrou = 1;
            break;
        }
        atual = atual->proximo;
    }
    if (!encontrou) {
        printf("\nNenhum veiculo com o chassi fornecido encontrado ou a placa possui um digito zero.\n");
      sleep(2);
    } else {
        printf("\nProprietario atualizado com sucesso.\n");
       sleep(2);
    }
}

int main() {
    Veiculo* listaveiculos = NULL;
    int opcao;

    do {
        printf("MENU:\n");
        printf("1 - Cadastrar veiculo\n");
        printf("2 - Listar proprietarios de veiculos diesel a partir de 2010\n");
        printf("3 - Listar placas que comecam com J e terminam com 0, 2, 4 ou 7\n");
        printf("4 - Listar modelo e cor dos veiculos com placa cuja segunda letra é vogal e a soma dos numeros da placa e par\n");
        printf("5 - Trocar proprietario por chassi\n");
        printf("0. Sair\n");
        scanf("%d", &opcao);
        printf("\033c");
        switch (opcao) {
            case 1: {
                char proprietario[50], combustivel[20], modelo[50], cor[20], chassi[50], placa[8];
                int ano;
                printf("Digite o proprietario: ");
                scanf(" %[^\n]s", proprietario);
                printf("Digite o combustivel (alcool, diesel, gasolina): ");
                scanf(" %[^\n]s", combustivel);
                while (strcasecmp(combustivel, "alcool") != 0 && strcasecmp(combustivel, "diesel") != 0 && 
              strcasecmp(combustivel, "gasolina") != 0) {
                  printf("Digite o combustivel (alcool, diesel, gasolina): ");
                  scanf(" %[^\n]s", combustivel);
                }
                printf("Digite o modelo: ");
                scanf(" %[^\n]s", modelo);
                printf("Digite a cor: ");
                scanf(" %[^\n]s", cor);
                printf("Digite o chassi: ");
                scanf(" %[^\n]s", chassi);
                printf("Digite o ano: ");
                scanf("%d", &ano);
                printf("Digite a placa:\t");
                verificarplaca(placa);

                Veiculo* nveiculo = cadastrarveiculo(proprietario, combustivel, modelo, cor, chassi, ano, placa);
                adicionar(&listaveiculos, nveiculo);

                printf("Veiculo cadastrado com sucesso!\n\n");
                sleep(2);
                printf("\033c");
                break;
            }
            case 2:
                listarproprietarios(listaveiculos);
                printf("\n");
                printf("\033c");             
                break;
            case 3:
                listarplacas(listaveiculos);
                printf("\n");
                printf("\033c");
                break;
            case 4:
                listarmodeloecor(listaveiculos);
                printf("\n");
                printf("\033c");
                break;
            case 5: {
                char chassi[50], nproprietario[50];
                printf("Digite o chassi do veiculo: ");
                scanf(" %[^\n]s", chassi);
                printf("Digite o novo proprietario: ");
                scanf(" %[^\n]s", nproprietario);

                trocarproprietario(&listaveiculos, chassi, nproprietario);
                printf("\n");
                printf("\033c");
                break;
            }
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n\n");
                break;
        }
    } while (opcao != 0);

    return 0;
}
