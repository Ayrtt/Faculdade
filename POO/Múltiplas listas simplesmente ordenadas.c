#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct sNODE
{
  int dado;
  struct sNODE *prox;
}node;

typedef struct sLISTA
{
  struct sNODE *ini, *fim;
}LISTA;


void inicializar(LISTA *lst);
void inserir_ord(LISTA *lst, int dado);
void remover(LISTA *lst, int dado);
struct sNODE *buscar(LISTA *lst, int dado);
int obter(struct sNODE *node);
int tamanho(LISTA *lst);
void imprimir(LISTA *lst);
void apagar(LISTA *lst);
LISTA juntar_ord(LISTA * lst1, LISTA * lst2);

int main(void) 
{
  node temp;
  LISTA lst1, lst2, nova_lst;
 
  while(1)
  {
    int dado, indice = 0, menu = 0;
    printf("-------------------------------\n");
    printf("Lista encadeada ordenada.\n");
    printf("\n");
    printf("1. Criar lista;\n");
    printf("2. Inserir dado;\n");
    printf("3. Remover dado;\n");
    printf("4. Obter ponteiro do dado;\n");
    printf("5. Buscar dado;\n");
    printf("6. Tamanho da lista;\n");
    printf("7. Exibir lista;\n");
    printf("8. Apagar lista;\n");
    printf("9. Juntar listas;\n");
    printf("10. Sair\n");
    printf("-------------------------------\n");
    int lista;
    printf("Escolha a lista: 1 / 2\n\n");
    scanf("%d", &lista);
    if ((lista != 1) && (lista !=2))
      printf("\nDado inválido.\n\n");
    else
    {
      printf("\n");
      printf("Escolha uma opção: ");
      if (lista == 1)
      {
        scanf("%d", &menu);
        setbuf(stdin, NULL);

        switch( menu )
        {
          case 1:
            inicializar(&lst1);
            printf("\n\n1) Lista criada.\n\n");
            break;

          case 2:
            printf("\n2) Dado: ");
            scanf(" %d", &dado);
            setbuf(stdin, NULL);
            inserir_ord(&lst1, dado);
            printf("Dado inserido.\n\n");
            break;
          
          case 3:
            printf("\n3) Dado: ");
            scanf(" %ds", &dado);
            remover(&lst1, dado);
            printf("Dado removido.\n\n");
            break;

          case 4:
            printf("\n4) Dado: ");
            scanf(" %d", &dado);
            if (buscar(&lst1, dado) == NULL)
              printf("Dado não encontrado.\n\n\n");
            else     
            {
              printf("\nO dado %d se encontra em %p.\n\n\n", dado, buscar(&lst1, dado));
              break;
            }
          
          case 5:
            printf("\n5) Dado: ");
            scanf("%d", &dado);
            printf("\nResultado: %d\n\n", obter(buscar(&lst1, dado)));            
            break;
          
          case 6:
            printf ("\n6) Tamanho da lista: %d\n\n", tamanho(&lst1));
            break;
          
          case 7:
            printf("\n7)\n");
            imprimir(&lst1);
            printf("\n\n");
            break;
          
          case 8:
            apagar(&lst1);
            printf("\n8) Lista apagada.\n\n");
            break;
          
          case 9:
            nova_lst = juntar_ord(&lst1, &lst2);
            imprimir(&nova_lst);
            apagar(&nova_lst);
            break;
          
          case 10:
            printf("\n10) Até a próxima!\n\n");
            return 0;

          default:
            printf("\nDado inválido!\n\n");
            break; 
          
        }
      }
      else
      {
        scanf("%d", &menu);
        setbuf(stdin, NULL);

        switch( menu )
        {
          case 1:
            inicializar(&lst2);
            printf("\n\n1) Lista criada.\n\n");
            break;

          case 2:
            printf("\n2) Dado: ");
            scanf(" %d", &dado);
            setbuf(stdin, NULL);
            inserir_ord(&lst2, dado);
            printf("Dado inserido.\n\n");   
            break;
          
          case 3:
            printf("\n3) Dado: ");
            scanf(" %ds", &dado);
            remover(&lst2, dado);
            printf("Dado removido.\n\n");
            break;

          case 4:
            printf("\n4) Dado: ");
            scanf(" %d", &dado);
            if (buscar(&lst2, dado) == NULL)
              printf("Dado não encontrado.\n\n\n");
            else     
            {
              printf("\nO dado %d se encontra em %p.\n\n\n", dado, buscar(&lst2, dado));
              break;
            }
          
          case 5:
            printf("\n5) Dado: ");
            scanf("%d", &dado);
            printf("\nResultado: %d\n\n", obter(buscar(&lst2, dado)));            
            break;
          
          case 6:
            printf ("\n6) Tamanho da lista: %d\n\n", tamanho(&lst2));
            break;
          
          case 7:
            printf("\n7)\n");
            imprimir(&lst2);
            printf("\n\n");
            break;
          
          case 8:
            apagar(&lst2);
            printf("\n8) Lista apagada.\n\n");
            break;
          
          case 9:
            nova_lst = juntar_ord(&lst1, &lst2);
            imprimir(&nova_lst);

            apagar(&nova_lst);
            break;
          
          case 10:
            printf("\n10) Até a próxima!\n\n");
            return 0;

          default:
            printf("\nDado inválido!\n\n");
            break; 
          
        }
      }
    }
  }
  return 0;
}

void inicializar(LISTA * lst)
{
  lst->ini = NULL;
  lst->fim = NULL;
}

void inserir_ord(LISTA *lst, int dado)
{
  struct sNODE *aux = lst->ini, *ant = NULL;
  struct sNODE *novo = (struct sNODE*) malloc(sizeof(struct sNODE ));
  novo->dado = dado;
  novo->prox = NULL;

  while(aux && dado > aux->dado)
  {
    ant = aux;
    aux = aux->prox;
  }

  if (!lst->ini)
	  lst->ini = lst->fim = novo;
  else if (aux == lst->ini)
  {
    novo->prox = lst->ini;
    lst->ini = novo;
  } 
  else if (!aux)
  {
    lst->fim->prox = novo;
    lst->fim = novo;
  } 
  else 
  {
    ant->prox = novo;
    novo->prox = aux;
  }
}

void remover(LISTA * lst, int dado)
{
  struct sNODE *aux = lst->ini, *ant = NULL;

  while (aux)
  {
    if (dado == aux->dado)
    {
  	  if (aux == lst->ini)
    	  lst->ini = lst->ini->prox;
  	  else if(aux == lst->fim)
      {
    	  ant->prox = NULL;
    	  lst->fim = ant;
  	  } else
    	  ant->prox = aux->prox;
 	 
  	  free(aux);
  	  return;
	  }
    
    ant = aux;
    aux = aux->prox;
  }
}

struct sNODE *buscar(LISTA * lst, int dado)
{
  struct sNODE *aux = lst->ini;

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

int tamanho(LISTA * lst)
{
  struct sNODE *aux = lst->ini;
  int tam = 0;
 
  while (aux)
  {
	  tam++;
	  aux = aux->prox;
  }
 
  return tam;
}

void imprimir(LISTA * lst)
{
  struct sNODE *aux = lst->ini;
 
  printf("[ ");
  while (aux)
  {
	  printf("%d ", aux->dado);
	  aux = aux->prox;
  }
  printf("]\n");
}

void apagar(LISTA *lst)
{
  struct sNODE *aux = lst->ini, *ant;
 
  while (aux)
  {
    ant = aux;
    aux = aux->prox;
    free(ant);
  }
  lst->ini = lst->fim = NULL;
}

LISTA juntar_ord(LISTA * lst1, LISTA * lst2)
{
  LISTA lst3;
  inicializar(&lst3);
  struct sNODE *aux = lst1->ini;
  struct sNODE *aux2 = lst2->ini;
  while(aux)
  {
    inserir_ord(&lst3, aux->dado);
    aux = aux->prox;
  }

  while(aux2)
  {
    inserir_ord(&lst3, aux2->dado);
    aux2 = aux2->prox;
  }

  return lst3;
}
