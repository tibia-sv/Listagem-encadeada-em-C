#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int inicialMenu();
void addAnimal(bool tester, char n[32], int codigo, int idade, int peso,
               int consumo, int producao);
void removeAnimal();
void updateAnimal();
bool searchAnimal(int a, bool b);
void listOrder();

typedef struct list {
  char nome[32];
  int codigo, consumo, peso, idade, producao;
  struct list *anterior;
  struct list *proximo;
} lista_animais;

lista_animais *inicio_lista;

lista_animais *inicializarLista() {
  lista_animais *l = malloc(sizeof(lista_animais));

  l->codigo = 0;
  l->consumo = 0;
  l->peso = 0;
  l->idade = 0;
  l->producao = 0;

  l->proximo = NULL;
  l->anterior = NULL;

  return l;
}

int inicialMenu() {

  int option;

  printf("======== Controle de Produção ========\n\n");
  printf("Selecione uma opção:\n");
  printf("1 - Adicionar novo animal\n");            // addAnimal
  printf("2 - Remover animal\n");                   // removeAnimal
  printf("3 - Buscar animal por Codigo\n");         // searchAnimal
  printf("4 - Atualizar registro\n");               // updateAnimal
  printf("5 - Listar todos animais registrados\n"); // listOrder
  printf("9 - Encerrar programa\n");
  printf("-> ");
  scanf("%d", &option);

  return option;
}

void addAnimal(bool tester, char n[32], int codigo, int idade, int peso,
               int consumo, int producao) {

  lista_animais *aux = malloc(sizeof(lista_animais));
  lista_animais *atual_lista = inicio_lista;

  if (!tester) {
    printf("======== Adicionando novo Animal ========\n\n");

    printf("Codigo do animal -> ");
    scanf("%d", &codigo);
  }

  if (!tester) {
    if (!searchAnimal(aux->codigo, false) && codigo <= 1024) {
      aux->codigo = codigo;
      printf("Nome: ");
      getchar();
      scanf("%[^\n]", aux->nome);

      printf("Idade (em anos): ");
      scanf("%d", &aux->idade);

      printf("Peso (em Kg): ");
      scanf("%d", &aux->peso);

      printf("Consumo (em Kg): ");
      scanf("%d", &aux->consumo);

      printf("Producao (em litros): ");
      scanf("%d", &aux->producao);
    } else {
      printf("\nCodigo ja cadastrado ou acima do limite (1024)\n");
    }
  } else {
    strcpy(aux->nome, n);
    aux->idade = idade;
    aux->codigo = codigo;
    aux->peso = peso;
    aux->consumo = consumo;
    aux->producao = producao;
  }

  if (atual_lista->proximo == NULL) {
    aux->anterior = inicio_lista;
    aux->proximo = NULL;
    inicio_lista->proximo = aux;
  } else {
    aux->proximo = inicio_lista->proximo;
    aux->anterior = inicio_lista;
    inicio_lista->proximo->anterior = aux;
    inicio_lista->proximo = aux;
  }

  if (!tester) {
    printf("\nRegistro completo");
  }  
}

void removeAnimal() {

  int codigoR = -1;

  lista_animais *remover = inicio_lista;

  printf("======== Deletando Animal ========\n\n");

  printf("Codigo do animal a ser deletado: ");
  scanf("%d", &codigoR);

  if (remover != NULL) {
    while (remover != NULL) {
      if (codigoR == remover->codigo) {
        lista_animais *atual = remover->proximo;

        if (remover->anterior != NULL) {
          remover->anterior->proximo = atual;
        }
        if (atual != NULL) {
          atual->anterior = remover->anterior;
        }

        remover->anterior = NULL;
        remover->proximo = NULL;

        free(remover);
        printf("Registro deletado!\n");
        return;
      }
      remover = remover->proximo;
    }
    printf("Animal não encontrado!");
  }
}

bool searchAnimal(int searchCode, bool isSearching) {
  int k = 0;
  bool normalSearch = false;

  if (isSearching && searchCode == -1) {
    printf("======== Busca dos Animais ========\n\n");
    printf("Codigo do animal -> ");
    scanf("%d", &searchCode);
    normalSearch = true;
  }

  lista_animais *atual = inicio_lista;

  while (atual != NULL) {
    if (searchCode == atual->codigo) {
      if (isSearching) {
        printf("\nCodigo: %d\n", atual->codigo);
        printf("Nome: %s\n", atual->nome);
        printf("Idade: %d ano(s)\n", atual->idade);
        printf("Peso: %d kg\n", atual->peso);
        printf("Consumo: %d kg\n", atual->consumo);
        printf("Producao: %d litros", atual->producao);
      }
      return true;
    }
    atual = atual->proximo;
  }
  if(normalSearch) {
    printf("Codigo não encontrado");
  }
  return false;
}

void updateAnimal() {

  lista_animais *atual = inicio_lista;

  int codigo = -1;
  int nPeso, nConsumo, nIdade, nProducao;

  printf("======== Atualizando cadastro ========\n\n");
  printf("Codigo do animal -> ");
  scanf("%d", &codigo);

  if (atual->codigo != -1) {
    while (atual != NULL) {
      if (atual->codigo == codigo) {

        printf("Idade atual (em anos): ");
        scanf("%d", &nIdade);
        printf("Novo peso (em kg): ");
        scanf("%d", &nPeso);
        printf("Novo valor de consumo (em kg): ");
        scanf("%d", &nConsumo);
        printf("Novo valor de produção (em litros): ");
        scanf("%d", &nProducao);

        atual->idade = nIdade;
        atual->peso = nPeso;
        atual->consumo = nConsumo;
        atual->producao = nProducao;

        printf("\nRegistro atualizado");
        return;
      }
      atual = atual->proximo;
    }
  } 
  printf("\nRegistro nao encontrado");
}

void listOrder() {

  lista_animais *atual = inicio_lista;
  int codigoMAX = -1;

  while (atual != NULL) {
    if (atual->codigo > codigoMAX) {
      codigoMAX = atual->codigo;
    }
    atual = atual->proximo;
  }

  printf("Registros encontrados:\n");
  for (int i = 1; i <= codigoMAX; i++) {
    if (searchAnimal(i, true)) {
      printf("\n");
    }
  }
}

void tester() {
  char nome[32];

  strncpy(nome, "Aninha", 32);
  addAnimal(true, nome, 322, 5, 750, 15, 30);
  strncpy(nome, "Beterraba", 32);
  addAnimal(true, nome, 969, 7, 800, 12, 25);
  strncpy(nome, "Diana", 32);
  addAnimal(true, nome, 531, 4, 680, 10, 16);
  strncpy(nome, "Bessy", 32);
  addAnimal(true, nome, 437, 6, 880, 17, 32);
  strncpy(nome, "Daisy", 32);
  addAnimal(true, nome, 127, 3, 380, 12, 10);
}

int main() {

  inicio_lista = inicializarLista();
  tester();

  int option = 0;
  while (1 == 1) {
    system("clear");
    option = inicialMenu();
    switch (option) {
    case 1:
      system("clear");
      addAnimal(false, NULL, 0, 0, 0, 0, 0);
      fflush(stdin);
      getchar();
      getchar();
      break;
    case 2:
      system("clear");
      removeAnimal();
      fflush(stdin);
      getchar();
      getchar();
      break;
    case 3:
      system("clear");
      searchAnimal(-1, true);
      fflush(stdin);
      getchar();
      getchar();
      break;
    case 4:
      system("clear");
      updateAnimal();
      fflush(stdin);
      getchar();
      getchar();
      break;
    case 5:
      system("clear");
      listOrder();
      fflush(stdin);
      getchar();
      getchar();
      break;
    case 9:
      exit(0);
    default:
      return 0;
    }
  }
  return 0;
}