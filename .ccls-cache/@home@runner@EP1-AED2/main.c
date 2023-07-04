#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "grafo.h"

#define TAMANHO 100

int TAMANHOENTRADA = 1000;
int NumVertices;
int maxVertices;
int z = 0;

//Verifica se caracter é uma letra ou ";" ":"
int comparaCaracter(char caracter){
  if(('A'<=caracter && caracter <= 'Z')
   ||('a'<=caracter && caracter <= 'z')
   ||(caracter==':')||(caracter==';'))
    {return 1;}
  else
    {return 0;}
}

//Mede tamanho da string
int tamString(char* s1){
  int i;
  for (i = 0; s1[i] != '\0'; i++){}
  return i;
}

//Esvazia string
void esvaziaString(char * s){
  for (int i = tamString(s); i >= 0 ; i--){
    s[i] = '\0';}
}

//Compara se duas strings são iguais 1(==), 0(!=)
int comparaString(char* s1, char* s2){
  int a = 0;
  if (tamString(s1) == tamString(s2)){
    for (int i=0; i<tamString(s1); i++){
      if (s1[i] == s2[i])  {a++;}
    }
    if (a == tamString(s1)) {return 1;}
    else {return 0;}
  }
  else 
    return 0;
}


//Confere se vertice esta registrado em arranjo de relação nome-indice, se nao estiver, registra-o
int verificaPalavra(char * s, char ** nomes){

    for (int i = 0; i < z && z > 0; i++){
    if (comparaString(s, nomes[i]) == 1) 
      return i;
  }
nomes[z] = (char*) malloc((tamString(s) + 1) * sizeof(char));
if (nomes[z] == NULL) {
  printf("Erro ao alocar memória para a palavra.\n");
  return -1; // ou outra ação apropriada em caso de erro
}
  strcpy(nomes[z], s);
  z++;
  return z-1;
}


int main(int argc, char **argv){


  //array, armazena arquivo de entrada como string
  char *arrayEntrada = (char *)malloc(sizeof(char) * TAMANHOENTRADA);
	FILE *arquivo;
	arquivo = fopen(argv[1], "r");

	if (arquivo == NULL){
		return -1;
	}

	int i = -1;
	while (!feof(arquivo))
	{
		if (i == -1){
			fscanf(arquivo, "%d", &maxVertices);
			
		} else{
      if (arrayEntrada[i] == '1' || arrayEntrada[i] == '2') break;
			fscanf(arquivo, "%c", &arrayEntrada[i]);
		}
		i++;
	}

//Declara grafo "graph" e grafo "gr" que armazena seu transposto 
struct Graph *graph = criaGrafo(maxVertices);
struct Graph *gr = criaGrafo(maxVertices);

//Arranjo de relação nome vertice-indice
char** nomes = (char**) malloc (sizeof(char*)*maxVertices);
  
  
char vertice_temp[30]; // guarda uma palavra temporariamente
  
int aux = 0;
int aux2 = 0;
int a;
int b;

//Funcao separa string "arrayEntrada" em elementos separados por espaços,";", ":", etc.
while (arrayEntrada[aux] != '\0'){
  if(comparaCaracter(arrayEntrada[aux]) == 1){
    while (comparaCaracter(arrayEntrada[aux]) == 1){
      vertice_temp[aux2] = arrayEntrada[aux];
      if((vertice_temp[aux2] == ';' || vertice_temp[aux2] == ':')             &&  tamString(vertice_temp) > 1){
        aux++;
        aux2++;
        break;
        }
      aux++;
      aux2++;
      }
      for(int u=tamString(vertice_temp); u>=0; u--){
        if((comparaCaracter(vertice_temp[u])) == 0)
          vertice_temp[u]='\0';
        else
          break;
      }
      if (vertice_temp[aux2-1] == ':'){
        vertice_temp[tamString(vertice_temp) - 1] = '\0';
        a = verificaPalavra(vertice_temp, nomes);
        }
      if (vertice_temp[aux2-1] == ';'){
        vertice_temp[tamString(vertice_temp) - 1] = '\0';
        b = verificaPalavra(vertice_temp, nomes);

        addAresta(graph, gr, a, b, 0);
        }
  }
  else
    {aux++;}
  esvaziaString(vertice_temp);
  aux2=0;
}
  
defineNomes(nomes);
imprimeGrafo(graph);
kosaraju(graph, gr, maxVertices);

return 0;
}

