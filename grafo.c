#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"
#include "lista_encadeada.h"

#define BRANCO 0
#define CINZA 1
#define PRETO 2


Lista* inicializaLista(){
    return NULL;
}

Lista* inserirLista(Lista* l, char i){

    Lista *novo = (Lista*) malloc(sizeof(Lista));

    novo->info = i;

    novo->prox = l;

    //printf("Inserido!\n");
    return novo;
}

void imprimeLista(Lista *l){
    Lista *p;
    for(p = l; p != NULL; p = p->prox){
            printf("%c ", p->info);

    }
}

Lista* buscarLista(Lista *l, char elemento){
    Lista *p;
    for(p = l; p != NULL; p = p->prox){
        if(p->info == elemento){
            return p;
        }
    }
    return NULL;
}

void liberarLista(Lista *l){
    Lista *p = l;
    while(p != NULL){
        Lista *t = p->prox;
        free(p);
        p = t;
    }
}

Lista* retirarLista(Lista *l, char v){
    Lista *ant; //Guarda o anterior
    Lista *p = l; //Procura o elemento guardando a lista original
    while(p != NULL && p->info != v){
        ant = p;
        p = p->prox;
    }
    if(p == NULL){
        return l; //Não achou e retorna a lista original
    }
    if(ant == NULL){
        l = p->prox; //Retira elemento do inicio
    }
    else{
        ant->prox = p->prox;
    }
    free(p);
    return l;
}


void inicializar (grafo *g, int tamanho) {
	int i,j;
	g->v = tamanho;
	g->mapa = (char *) malloc(sizeof(char) * tamanho);
	g->lista = (Lista **) malloc(sizeof(Lista*) * tamanho);
	
}


void imprimir(grafo *g) {
		int i,j;
		Lista **aux;

		aux = g->lista;

		for(i =0; i < g->v; i++) {
				printf("\t%c: ", g->mapa[i]);
				imprimeLista(g->lista[i]);					
				printf("\n");
		}
}

void lerMapa(grafo *g){
	char vertice;
	int i;

	for(i = 0; i < g->v; i++){
		scanf(" %c", &vertice);
		g->mapa[i] = vertice;		
	}	
}

void lerArestas(grafo *g, int a){
	char aresta[3];
	char aresta1, aresta2;
	int i, j;

	for(i = 0; i < a; i++){
		scanf(" %s", aresta);
		adicionarAresta(g, aresta[0],aresta[1]);
							
	}	

}
void adicionarAresta(grafo *g, char v1, char v2){
	int j, chave1, chave2;

	//Busca pela primeira chave				
	for(j = 0; j < g->v; j++){
		if(g->mapa[j] == v1){
			chave1 = j;	
		}		
	}
	//Busca pela segunda chave		
	for(j = 0; j < g->v; j++){
		if(g->mapa[j] == v2){
			chave2 = j;	
		}		
	}
					
	g->lista[chave1] = inserirLista(g->lista[chave1], v2);
	g->lista[chave2] = inserirLista(g->lista[chave2], v1);	
}

void imprimirBusca(grafo *g, int posicao, int cor){
	if(cor == 1){
		printf("%c foi pintado de CINZA\n", g->mapa[posicao]);		
	}else if(cor == 2){
		printf("%c foi pintado de PRETO\n", g->mapa[posicao]);
	}

	

		
}

void visitar(grafo *g, int i, int *cor, int *cont, int *d, int *f){
	int j, chave;	
	cor[i] = CINZA;
	imprimirBusca(g, i, 1);
	*cont = *cont + 1;
	d[i] = *cont;
	
	Lista *v = g->lista[i];
 	while(v != NULL){
		//Busca a posição do elemento no mapa
		for(j = 0; j < g->v; j++){
			if(g->mapa[j] == v->info){
				chave = j;	
			}		
		}		
				
		if(cor[chave] == BRANCO){
			visitar(g, chave, cor, cont, d, f);		
		}
		v = v->prox;
	}

	cor[i] = PRETO;
	imprimirBusca(g, i, 2);
	*cont = *cont + 1;	
	f[i] = *cont;
	
}

void buscaProfundidade(grafo *g){
	//Inicializo o array de cor de acordo com o número de vértices		
	int *cor = (int *) malloc(sizeof(int) * g->v);
	int i; 
	int cont = 0;
	int *d = (int *) malloc(sizeof(int) * g->v);
	int *f = (int *) malloc(sizeof(int) * g->v);
	
	//Inicializa todos os elementos dos marcadores com zero
	//for(i = 0; i < g->v; i++){
	//	d[i] = 0;
	//	f[i] = 0;
	//}
		
	//Inicializa todos os elementos com a cor branca
	for(i = 0; i < g->v; i++){
		cor[i] = BRANCO;
	}
	//Garante que hajam reinícios
	for(i = 0; i < g->v; i++){
		if(cor[i] == BRANCO){
			visitar(g, i, cor, &cont, d, f);		
		}	
	}

	//Imprime os Arrays de marcadores Descoberto e Finalizado
	printf("\tDescoberto\n");	
	for(i = 0; i < g->v; i++){
		printf("\t%d", d[i]); 
	}
	printf("\n\tFinalizado\n");	
	for(i = 0; i < g->v; i++){
		printf("\t%d", f[i]); 
	}
	printf("\n");
}


int main(int argc, int* argv) {
	grafo g;
	int v, a, i;
	char cod_vertice;
	char aresta[3];
	char a1, a2;

	scanf("%d%d", &v, &a);
	
	inicializar(&g, v);
	
	lerMapa(&g);

	lerArestas(&g, a);
	
	imprimir(&g);

	buscaProfundidade(&g);

   return 0;

}
