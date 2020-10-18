#ifndef LISTA_H
#define LISTA_H

struct lista{
    char info;
    struct lista *prox;
}; typedef struct lista Lista;


Lista* inicializaLista();

Lista* inserirLista(Lista* l, char i);

void imprimeLista(Lista *l);

Lista* buscarLista(Lista *l, char elemento);

void liberarLista(Lista *l);

Lista* retirarLista(Lista *l, char v);
#endif
