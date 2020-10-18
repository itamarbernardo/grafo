#ifndef GRAFO_H
#define GRAFO_H
#include "lista_encadeada.h"

typedef struct grafo {
	int v;
	char *mapa;
	Lista **lista;
} grafo;

void inicializar (grafo *g, int tamanho);

void imprimir(grafo *g);

void adicionarAresta(grafo *g, char v1, char v2);

#endif
