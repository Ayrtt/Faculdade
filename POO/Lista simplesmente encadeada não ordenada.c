#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct sNODE
{
  int dado;
  struct sNODE *prox;
}node;

struct sNODE *ini = NULL, *fim = NULL;

void inserir_ini(int dado);
void inserir(int dado);
void remover(int dado);
int obter(struct sNODE *node);
struct sNODE *buscar(int dado);
int tamanho();
void imprimir();
void apagar();

int main()
{
  while(1)
  {
    node lst;
    int dado = 0, indice = 0, menu = 0;
    printf("-------------------------------\n");
    printf("Lista simplesmente encadeada não ordenada.\n");
    printf("\n");
    printf("1. Inserir dado no início;\n");
    printf("2. Inserir dado no fim;\n");
    printf("3. Remover dado;\n");
    printf("4. Obter ponteiro do dado;\n");
    printf("5. Buscar dado;\n");
    printf("6. Tamanho da lista;\n");
    printf("7. Exibir lista;\n");
    printf("8. Apagar lista;\n");
    printf("9. Sair.\n");
    printf("-------------------------------\n");
    printf("\n");
    printf("Escolha uma opção: ");
    scanf("%d", &menu);
    setbuf(stdin, NULL);

    switch( menu )
    {
      case 1:
        printf("\n1) Dado: ");
        scanf("%d", &dado);
        inserir_ini(dado);
        printf("Dado inserido.\n\n\n");
        break;
        
        
      case 2:
        printf("\n2) Dado: ");
        scanf("%d", &dado);
        inserir(dado);
        printf("Dado inserido.\n\n\n");
        break;
      
      case 3:
        printf("\n3) Dado: ");
        scanf("%d", &dado);
        remover(dado);
        printf("Dado removido.\n\n\n");
        break;

      case 4:
        printf("\n4) Dado: ");
        scanf("%d", &dado);
        if (buscar(dado) == NULL)
          printf("Dado não encontrado.\n\n\n");
        else     
        {
          printf("\nO dado %d se encontra em %p.\n\n\n", dado, buscar(dado));
          break;
        }
      
      case 5:
        printf("\n5) Dado: ");
        scanf("%d", &dado);
        printf("\nResultado: %d\n\n\n", obter(buscar(dado)));
        break;
      
      case 6:
        printf ("\n6) Tamanho da lista: %d\n\n", tamanho());
        break;
      
      case 7:
        printf("\n7)");
        imprimir();
        printf("\n\n");
        break;
      
      case 8:
        apagar();
        printf("\n8) Lista apagada.\n\n");
        break;

      case 9:
        printf("\n9) Até a próxima!\n\n");
        return 0;

      default:
        printf("\nValor inválido!\n\n");
        break;        
    }
  }
  return 0;
}

void inserir_ini(int dado)
{
  struct sNODE *novo = (struct sNODE*) malloc(sizeof(struct sNODE));

  novo->dado = dado; 
  novo->prox = NULL;

  if (!ini)
	  ini = fim = novo;
  else
  {
    novo->prox = ini;
	  ini = novo;
  }
}

void inserir(int dado)
{
  struct sNODE *novo = (struct sNODE*) malloc(sizeof(struct sNODE));
  novo->dado = dado;
  novo->prox = NULL;

  if (!ini)
	  ini = fim = novo;
  else
  {
	  fim->prox = novo;
	  fim = novo;
  }
}

void remover(int dado)
{
  struct sNODE *aux = ini, *ant = NULL;

  while (aux)
  {
    if (dado == aux->dado)
    {
  	  if (aux == ini)
    	  ini = ini->prox;
  	  else if(aux == fim)
      {
    	  ant->prox = NULL;
    	  fim = ant;
  	  } else
    	  ant->prox = aux->prox;
 	 
  	  free(aux);
  	  return;
	  }
    
    ant = aux;
    aux = aux->prox;
  }
}

struct sNODE *buscar(int dado)
{
  struct sNODE *aux = ini;

  while (aux)
  {
	  if (dado == aux->dado)
  	  return aux;
	  aux = aux->prox;
  }

  return NULL;
}

int obter(struct sNODE *node)
{
  if (!node)
  {
	  printf("Erro ao obter dado. Ponteiro invalido.");
	  exit(0);
  }
 
  return node->dado;
}

int tamanho()
{
  struct sNODE *aux = ini;
  int tam = 0;
 
  while (aux)
  {
	  tam++;
	  aux = aux->prox;
  }
 
  return tam;
}

void imprimir()
{
  struct sNODE *aux = ini;
 
  printf("[ ");
  while (aux)
  {
	  printf("%d ", aux->dado);
	  aux = aux->prox;
  }
  printf("]\n");
}

void apagar()
{
  struct sNODE *aux = ini, *ant;
 
  while (aux)
  {
    ant = aux;
    aux = aux->prox;
    free(ant);
  }
  ini = fim = NULL;
}
