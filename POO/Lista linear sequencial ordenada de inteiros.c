#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
 unsigned MAX;
 int *arr, pos;
} LISTA;

void criar(LISTA *lst, int tam_MAX);
void apagar(LISTA *lst);

void inserir_ord(LISTA *lst, int elemento);
void remover(LISTA *lst, int elemento);
int buscar(LISTA *lst, int elemento);

int obter(LISTA *lst, int indice);
int tamanho(LISTA *lst);
void imprimir(LISTA *lst);

int main(void) 
{
  LISTA lst1, lst2;
  while(1)
  {
    int elemento, indice = 0, menu = 0;
    printf("-------------------------------\n");
    printf("Lista sequenciada ordenada.\n");
    printf("\n");
    printf("1. Criar lista;\n");
    printf("2. Inserir elemento;\n");
    printf("3. Remover elemento;\n");
    printf("4. Obter índice do elemento;\n");
    printf("5. Buscar elemento;\n");
    printf("6. Tamanho da lista;\n");
    printf("7. Exibir lista;\n");
    printf("8. Apagar lista;.\n");
    printf("9. Sair\n");
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
            lst1.pos = 0;
            printf("\n1)Tamanho da lista: ");
            scanf("%d", &lst1.MAX);
            criar(&lst1, lst1.MAX);
            printf("\n\nLista criada.\n\n");
            break;

          case 2:
            printf("\n2) Elemento: ");
            scanf(" %d", &elemento);
            setbuf(stdin, NULL);
            inserir_ord(&lst1, elemento);
            printf("\n\n");        
            break;
          
          case 3:
            printf("\n3) Elemento: ");
            scanf(" %ds", &elemento);
            remover(&lst1, elemento);
            printf("\n\n");
            break;

          case 4:
            printf("\n4) Elemento: ");
            scanf(" %d", &elemento);
            if (buscar(&lst1, elemento) == -1)
              printf("Elemento não encontrado.\n\n");
            else      
              printf("Índice: %d\n\n", buscar(&lst1, elemento)+1);
            break;
          
          case 5:
            printf("\n5) Índice: ");
            scanf("%d", &indice);
            printf("\n\n");
            obter(&lst1, indice-1);
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
            printf("\n9) Até a próxima!\n\n");
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
            lst2.pos = 0;
            printf("\n1)Tamanho da lista: ");
            scanf("%d", &lst2.MAX);
            criar(&lst2, lst2.MAX);
            printf("\n\nLista criada.\n\n");
            break;

          case 2:
            printf("\n2) Elemento: ");
            scanf(" %d", &elemento);
            setbuf(stdin, NULL);
            inserir_ord(&lst2, elemento);
            printf("\n\n");        
            break;
          
          case 3:
            printf("\n3) Elemento: ");
            scanf(" %ds", &elemento);
            remover(&lst2, elemento);
            printf("\n\n");
            break;

          case 4:
            printf("\n4) Elemento: ");
            scanf(" %d", &elemento);
            if (buscar(&lst2, elemento) == -1)
              printf("Elemento não encontrado.\n\n");
            else      
              printf("Índice: %d\n\n", buscar(&lst2, elemento)+1);
            break;
          
          case 5:
            printf("\n5) Índice: ");
            scanf("%d", &indice);
            printf("\n\n");
            obter(&lst2, indice-1);
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
            printf("\n9) Até a próxima!\n\n");
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

void criar(LISTA * lst, int tam_MAX)
{
  lst->arr = (int *) malloc(sizeof(int) * lst->MAX);
}

void inserir_ord(LISTA * lst, int elemento)
{
  int i, p;
  if (lst->pos < lst->MAX) {
	for (i = 0 ; i < lst->pos ; i++)
  	if (lst->arr[i] >= elemento)
    	break;
    
	for (p = lst->pos ; p > i ; p--)
  	lst->arr[p] = lst->arr[p-1];
    
	lst->arr[i] = elemento;

	lst->pos ++;
  }
  else 
  {
	  printf("Não foi possível inserir %d. Lista cheia.\n", elemento);
  }
}

void remover(LISTA * lst, int elemento)
{
  int p = buscar(lst, elemento);
 
  if (p == -1)
	  return;
 
  for (int i = p ; i < lst->pos -1; i++)
	  lst->arr[i] = lst->arr[i+1];
  lst->pos--;
}

int buscar(LISTA * lst, int elemento)
{  
  for (int i = 0 ; i < lst->pos ; i++)
  {
	  if (lst->arr[i] == elemento)
  	  return i;
  }
  return -1;
}

int obter(LISTA * lst, int indice)
{
  if (indice < 0 || indice >= lst->pos) 
  {
	  printf("Indice %d fora dos limites da Lista.\n", indice);
	  exit(1);
  }
  printf("Elemento: '%d'\n\n", lst->arr[indice]);

  return 0;
}

int tamanho(LISTA * lst)
{
  return lst->pos;
}

void imprimir(LISTA * lst)
{
  printf("[ ");
  for (int i = 0 ; i < lst->pos ; i++)
  {  
    printf("%d ", lst->arr[i]);
  }
  printf("]");
  printf("\n");
}

void apagar(LISTA * lst)
{
  free(lst->arr);
}
