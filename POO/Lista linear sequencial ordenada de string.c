#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const unsigned MAX = 10;
int pos = 0;
char l[MAX][21];

void inserir_ord(char * string);

void remover(char * string);
int buscar(char * string);
void obter(int indice);
int tamanho();

void imprimir(char l[pos][21]);
void apagar();

int main(void) 
{
  while(1)
  {
    char string[21];
    int indice = 0, menu = 0;
    printf("-------------------------------\n");
    printf("Lista sequenciada ordenada de strings.\n");
    printf("\n");
    printf("1. Inserir string;\n");
    printf("2. Remover string;\n");
    printf("3. Obter índice da string;\n");
    printf("4. Buscar string;\n");
    printf("5. Tamanho da lista;\n");
    printf("6. Exibir lista;\n");
    printf("7. Apagar lista;\n");
    printf("8. Sair.\n");
    printf("-------------------------------\n");
    printf("\n");
    printf("Escolha uma opção: ");
    scanf("%d", &menu);
    setbuf(stdin, NULL);

    switch( menu )
    {
      case 1:
        printf("\n1) String: ");
        scanf(" %[^\n]s", string);
        setbuf(stdin, NULL);
        inserir_ord(string);
        printf("\n\n");        
        break;
       
      case 2:
        printf("\n2) String: ");
        scanf(" %[^\n]s", string);
        remover(string);
        printf("\n\n");
        break;
      
      case 3:
        printf("\n3) String: ");
        scanf(" %[^\n]s", string);
        if (buscar(string) == -1)
          printf("String não encontrada.\n\n");
        else      
          printf("Índice: %d\n\n", buscar(string)+1);
        break;

      case 4:
        printf("\n4) Índice: ");
        scanf("%d", &indice);
        printf("\n\n");
        obter(indice-1);
        break;
      
      case 5:
        printf ("\n5) Tamanho da lista: %d\n\n", tamanho());
        break;
      
      case 6:
        printf("\n6)\n");
        imprimir(l);
        printf("\n\n");
        break;
      
      case 7:
        apagar();
        printf("\n7) Lista apagada.\n\n");
        break;
      
      case 8:
        printf("\n8) Até a próxima!\n\n");
        return 0;

      default:
        printf("\nDado inválido!\n\n");
        break; 
      
    }
  }
  return 0;
}

void inserir_ord(char * string)
{
  int i, p;
  if (pos < MAX)
  {
	  for (i = 0 ; i < pos ; i++)
  	  if (strcmp(l[i], string) >= 0)
    	  break;
    
	  for (p = pos ; p > i ; p--)
  	  strcpy(l[p], l[p-1]);
    
	  strcpy(l[i], string);
    char zero = '\0';
    strcpy(l[pos+1], &zero);

	  pos ++;
  }
  else 
  {
	printf("Não foi possível inserir %s. Lista cheia.\n", string);
  }
}

void remover(char * string)
{
  int p = buscar(string);
 
  if (p == -1)
	  return;
 
  for (int i = p ; i < pos -1; i++)
	  strcpy(l[i], l[i+1]);
  pos--;
}

int buscar(char * string)
{  
  for (int i = 0 ; i < pos ; i++)
  {
	  if (strcmp(l[i], string) == 0)
  	  return i;
  }
  return -1;
}

void obter(int indice)
{
  if (indice < 0 || indice >= pos) 
  {
	  printf("Indice %d fora dos limites da Lista.\n", indice);
	  exit(1);
  }
  printf("String: '%s'\n\n", l[indice]);
}

int tamanho()
{
  return pos;
}

void imprimir(char l[pos][21])
{
  for (int i = 0 ; i < pos ; i++)
  {  
    printf("'%s'", l[i]);
    printf("\n");
  }
  printf("\n");
}

void apagar()
{
  pos = 0;
