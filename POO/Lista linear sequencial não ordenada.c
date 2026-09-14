#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const unsigned MAX = 10;
int l[MAX], pos = 0;

void inserir_ini(int elemento);
void inserir(int elemento);
void remover(int elemento);
int buscar(int elemento);
int obter(int indice);
int tamanho();
void imprimir();
void apagar();

int main(void) {
  while(1) {
    int elemento = 0, indice = 0, menu = 0;
    printf("-------------------------------\n");
    printf("Lista sequenciada não ordenada.\n");
    printf("\n");
    printf("1. Inserir elemento no início da lista;\n");
    printf("2. Inserir elemento no fim da lista;\n");
    printf("3. Remover elemento;\n");
    printf("4. Obter índice do elemento;\n");
    printf("5. Buscar elemento;\n");
    printf("6. Tamanho da lista;\n");
    printf("7. Exibir lista;\n");
    printf("8. Apagar lista;\n");
    printf("9. Sair.\n");
    printf("-------------------------------\n");
    printf("\n");
    printf("Escolha uma opção: ");
    scanf("%d", &menu);
    setbuf(stdin, NULL);

    switch( menu ) {
      case 1:
        printf("\n1) Elemento: ");
        scanf("%d", &elemento);
        inserir_ini(elemento);
        printf("\n\n");
        break;
        
      case 2:
        printf("\n2) Elemento: ");
        scanf("%d", &elemento);
        inserir(elemento);
        printf("\n\n");
        break;
      
      case 3:
        printf("\n3) Elemento: ");
        scanf("%d", &elemento);
        remover(elemento);
        printf("\n\n");
        break;

      case 4:
        printf("\n4) Elemento: ");
        scanf("%d", &elemento);
        if (buscar(elemento) == -1)
          printf("Elemento não encontrado.\n\n");
        else      
          printf("Índice: %d\n\n", buscar(elemento)+1);
        break;
      
      case 5:
        printf("\n5) Índice: ");
        scanf("%d", &indice);
        printf("\n\n");
        printf("Elemento: %d\n\n", obter(indice-1));
        break;
      
      case 6:
        printf ("\n6) Tamanho da lista: %d\n\n", tamanho());
        break;
      
      case 7:
        printf("\n7)\n");
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

void inserir_ini(int elemento)
{ 
  int x = 0;
  if (pos < MAX)
    x = l[pos];
	  l[pos++] = x;
  for (int i = pos-1; i >= 0; i--)
    l[i] = l[i-1];
  l[0] = elemento;
}

void inserir(int elemento)
{
  int x = pos;
  if (pos < MAX)
  {
    for (int i = 0; i < x; i++)
    {
      if (l[i] == elemento)
      {
        printf("\nElemento já existente na lista.\n\n");
        return;
      }
    }
    l[pos++] = elemento;
  }
  else 
  {
    printf("Não foi possível inserir %d. Lista cheia.\n",elemento);
  }
}

void remover(int elemento)
{
  int contador = 0;
  for (int a = 0; a < pos; a++)
  {
    if (l[a] == elemento)
      contador++;
  }

  for (int b = 0; b < contador; b++)
  {
    int p = buscar(elemento);
  
    if (p == -1)
      return;
  
    for (int i = p ; i < pos -1; i++)
      l[i] = l[i+1];
    pos--;
  }
}

int buscar(int elemento)
{
  for (int i = 0 ; i < pos ; i++)
  {
	  if (l[i] == elemento)
  	  return i;
  }
  return -1;
}

int obter(int indice)
{
  if (indice < 0 || indice >= pos) 
  {
	  printf("Indice %d fora dos limites da Lista.\n", indice);
	  exit(1);
  }
  return l[indice];
}

int tamanho()
{
  return pos;
}

void imprimir()
{
  printf("[ ");
  for (int i = 0 ; i < pos ; i++)
	  printf("%d ", l[i]);
  printf("]");
  printf("\n");
}

void apagar()
{
  pos = 0;
}
