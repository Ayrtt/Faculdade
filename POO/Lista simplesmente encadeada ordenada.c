#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct sNODE
{
  char estudante[31];
  float nota1, nota2, media;
  struct sNODE *prox;
}node;

struct sNODE *ini = NULL, *fim = NULL;

void inserir_ord(char * estudante, float nota1, float nota2);
void remover(char * estudante);
struct sNODE * buscar(char * estudante);
struct sNODE obter(struct sNODE *node);
int tamanho();
void imprimir();
void apagar();

int main()
{
  while(1)
  {
    node lst;
    node temp;
    int indice = 0, menu = 0;
    char nome[31];
    float n1, n2;
    printf("-------------------------------\n");
    printf("Lista simplesmente encadeada ordenada.\n");
    printf("\n");
    printf("1. Inserir estudante;\n");
    printf("2. Remover estudante;\n");
    printf("3. Obter ponteiro do(a) estudante;\n");
    printf("4. Buscar estudante;\n");
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
        printf("\n1) Nome: ");
        scanf(" %[^\n]s", nome);
        setbuf(stdin, NULL);
        printf("Primeira nota: ");
        scanf("%f", &n1);
        printf("Segunda nota: ");
        scanf("%f", &n2);
        inserir_ord(nome, n1, n2);
        printf("\n\nEstudante inserido(a).\n\n\n");
        break;     
        
      case 2:
        printf("\n2) Nome: ");
        scanf(" %[^\n]s", nome);
        setbuf(stdin, NULL);
        remover(nome);
        printf("Estudante removido(a).\n\n\n");
        break;
      
      case 3:
        printf("\n3) Nome: ");
        scanf(" %[^\n]s", nome);
        setbuf(stdin, NULL);
        if (buscar(nome) == NULL)
          printf("Dado não encontrado.\n\n\n");
        else     
        {
          printf("\nO(A) estudante '%s' se encontra em %p.\n\n\n", nome, buscar(nome));
          break;
        }

      case 4:
        printf("\n4) Nome: ");
        scanf(" %[^\n]s", nome);
        setbuf(stdin, NULL);
        temp = obter(buscar(nome));
        printf("\n\nNome: %s", temp.estudante);
        printf("\nNota 1: %g", temp.nota1);
        printf("\nNota 2: %g", temp.nota2);
        printf("\nMédia: %g\n\n\n", temp.media);
        break;
      
      case 5:
        printf ("\n5) Tamanho da lista: %d\n\n\n", tamanho());
        break;
      
      case 6:
        printf("\n6)");
        imprimir();
        printf("\n\n\n");
        break;
      
      case 7:
        apagar();
        printf("\n7) Lista apagada.\n\n\n");
        break;
      
      case 8:
        printf("\n8) Até a próxima!\n\n\n");
        return 0;

      default:
        printf("\nValor inválido!\n\n\n");
        break;        
    }
  }
  
  return 0;
}

void inserir_ord(char * estudante, float nota1, float nota2)
{
  struct sNODE *aux = ini, *ant = NULL;
  struct sNODE *novo = (struct sNODE*) malloc(sizeof(struct sNODE ));
  strcpy(novo->estudante, estudante);
  novo->nota1 = nota1;
  novo->nota2 = nota2;
  float media = ((nota1 + nota2)/2);
  novo->media = media;
  novo->prox = NULL;

  while(aux && media < aux->media)
  {
    ant = aux;
    aux = aux->prox;
  }

  if (!ini)
	  ini = fim = novo;
  else if (aux == ini)
  {
    novo->prox = ini;
    ini = novo;
  } 
  else if (!aux)
  {
    fim->prox = novo;
    fim = novo;
  } 
  else 
  {
    ant->prox = novo;
    novo->prox = aux;
  }
}

void remover(char * nome)
{
  struct sNODE *aux = ini, *ant = NULL;

  while (aux)
  {
    if (strcmp(aux->estudante, nome) == 0)
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

struct sNODE * buscar(char * nome)
{
  struct sNODE *aux = ini;

  while (aux)
  {
	  if (strcmp(aux->estudante, nome) == 0)
  	  return aux;
	  aux = aux->prox;
  }

  return NULL;
}

struct sNODE obter(struct sNODE * node)
{
  if (!node)
  {
	  printf("Erro ao obter estudante. Ponteiro invalido.");
	  exit(0);
  }
 
  return *node;
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
 
  while (aux)
  {
	  printf("\nNome: %s", aux->estudante);
    printf("\nNota 1: %g", aux->nota1);
    printf("\nNota 2: %g", aux->nota2);
    printf("\nMédia: %g\n\n\n", aux->media);
	  aux = aux->prox;
  }
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
