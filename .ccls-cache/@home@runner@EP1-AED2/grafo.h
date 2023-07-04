#include <malloc.h>

#define MAX_SIZE 100

struct Graph *grafo;
struct Graph *gr;
int stack[MAX_SIZE], top;

// Estrutura de um no
struct list_adj_no {
  int dest;
  int peso;
  struct list_adj_no *prox;
};

// Estrutura representa lista adjacencia
struct adj_list {
  struct list_adj_no *head;
};

// Estrutura representacao do grafo
struct Graph {
  int V;
  int *visitado;
  struct adj_list *array;
};


//Lista de associacao nome-indice vertices
char** nomes;
void defineNomes(char** valores){
  nomes = valores;
}


//*FUNCOES FUNCIONAMENTO GRAFO*//

//Cria no para lista de adjacencia
struct list_adj_no *new_list_adj_no(int dest, int peso) {
  struct list_adj_no *novoNo =
      (struct list_adj_no *)malloc(sizeof(struct list_adj_no));
  novoNo->dest = dest;
  novoNo->peso = peso;
  novoNo->prox = NULL;
  return novoNo;
}

// Funcao cria grafo com V vertices
struct Graph *criaGrafo(int V) {
  struct Graph *grafo = (struct Graph *)malloc(sizeof(struct Graph));
  grafo->V = V;
  grafo->array = (struct adj_list *)malloc(V * sizeof(struct adj_list));
  int i;
  for (i = 0; i < V; ++i)
    grafo->array[i].head = NULL;
  return grafo;
}

// Função para inverter arestas do grafo em "gr"
void transporGrafo(struct Graph *gr, int src, int dest, int peso) {
  struct list_adj_no *novoNo = new_list_adj_no(src, peso);
  novoNo->prox = gr->array[dest].head;
  gr->array[dest].head = novoNo;
}

// Função para adicionar arestas entre dois vertices
void addAresta(struct Graph *grafo, struct Graph *gr, int src, int dest,
              int peso) {
  struct list_adj_no *novoNo = new_list_adj_no(dest, peso);
  novoNo->prox = grafo->array[src].head;
  grafo->array[src].head = novoNo;
  transporGrafo(gr, src, dest, peso);
}
// Função para imprimir o grafo
void imprimeGrafo(struct Graph *grafo) {
  printf("Vertices= %d\n", grafo->V);
  for (int v = 0; v < grafo->V; v++) {
    printf("%s->", nomes[v]);
    struct list_adj_no *temp = grafo->array[v].head;
    while (temp) {
      printf(" %s", nomes[temp->dest]);
      if (temp->prox)
        printf(",");
      else
        printf("");
      temp = temp->prox;
    }
    printf("\n");
  }
  printf("\n");
}

//*Implementação da Pilha*//

void push(int x) {
  if (top >= MAX_SIZE - 1) {
  } else {
    top++;
    stack[top] = x;
  }
}

void pop() {
  if (top <= -1) {
    printf("\n\tPilha vazia!");
  } else {
    top--;
  }
} 

// Funçao para preencher a pilha
void set_fill_order(struct Graph *grafo, int v, bool visitado[], int *stack) {
  visitado[v] = true;
  struct list_adj_no *temp = grafo->array[v].head;
  while (temp) {
    if (!visitado[temp->dest]) {
      set_fill_order(grafo, temp->dest, visitado, stack);
    }
    temp = temp->prox;
  }
  push(v);
}

// Funcao DFS recursivo a partir de v
void dfs_recursivo(struct Graph *gr, int v, bool visitado[]) {
  visitado[v] = true;
  printf(" %s  ", nomes[v]);
  struct list_adj_no *temp = gr->array[v].head;
  while (temp) {
    if (!visitado[temp->dest]) {
      dfs_recursivo(gr, temp->dest, visitado);
    }
    temp = temp->prox;
  }
}


//*VERIFICACAO ELEMENTOS FORTEMENTE CONEXOS*//

//Kosaraju//
void kosaraju(struct Graph *grafo, struct Graph *gr,
                                   int V) {
  bool visitado[V];
  for (int i = 0; i < V; i++)
    visitado[i] = false;
  for (int i = 0; i < V; i++) {
    if (visitado[i] == false) {
      set_fill_order(grafo, i, visitado, stack);
    }
  }
int count = 1;
  for (int i = 0; i < V; i++)
    visitado[i] = false;
  while (top != -1) {
    int v = stack[top];
    pop();
    if (visitado[v] == false) {
      printf("Componente [%d]: ", count++);
      dfs_recursivo(gr, v, visitado);
      printf("\n");
    }
  }
  if ((count) == 2) printf("Sim, grafo é fortemente conexo.\n");
  else printf("Nao, o grafo nao é  fortemente conexo.\n");
  printf("Numero de componentes: %d\n", count - 1);
}