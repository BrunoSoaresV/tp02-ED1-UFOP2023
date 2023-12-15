#ifndef GRAFO_H
#define GRAFO_H

// Definição da estrutura No, representando um nó em uma lista de adjacência.
typedef struct No {
    int destino;        // Armazena o destino do nó (vértice adjacente).
    int peso;           // Armazena o peso da aresta que conecta o nó ao seu destino.
    struct No* proximo;  // Ponteiro para o próximo nó na lista.
} No;

// Definição da estrutura ListaAdj, representando uma lista de adjacência para um vértice em um grafo ponderado.
typedef struct ListaAdj {
    No* cabeca;  // Ponteiro para a cabeça da lista de adjacência.
} ListaAdj;

// Definição da estrutura GrafoPonderado, representando um grafo ponderado.
typedef struct GrafoPonderado {
    int numCidades;         // Número de cidades no grafo.
    ListaAdj* listaAdjacencia;  // Vetor de listas de adjacência para cada cidade.
} GrafoPonderado;

// Protótipos das funções definidas no arquivo "grafo.c".
GrafoPonderado* alocarGrafo(int numCidades);
void desalocarGrafo(GrafoPonderado* grafo);
void leGrafo(GrafoPonderado* grafo);
void encontraCaminho(GrafoPonderado* grafo, int* melhorCaminho);
void imprimeCaminho(GrafoPonderado* grafo, int* caminho, int distancia);
void ordenaLista(GrafoPonderado* grafo);
void imprimeOrdenado(GrafoPonderado* grafo);
int obterDistancia(GrafoPonderado* grafo, int cidadeOrigem, int cidadeDestino);

#endif
