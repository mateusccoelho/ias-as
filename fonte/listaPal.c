#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "/home/mateus/Unicamp/MC404/trab01/headers/listaPal.h"

/* Inicializa a lista criando um no cabeca. */
void lstPal_inicializar(NoLstPal** lista) {
	*lista = malloc(sizeof(NoLstPal));
	(*lista) -> local = NULL;
	(*lista) -> ant = NULL;
	(*lista) -> prox = NULL;
}

NoLstPal* lstPal_inserir(NoLstPal *lista, int numPal, char *c1, char *e1, char *c2, char *e2) {
	NoLstPal *novo;
	Palavra *pal;
	
	/* Criacao da palavra. */
	pal = malloc(sizeof(Palavra));
	pal -> palavra = numPal;
	pal -> cod1 = malloc(3 * sizeof(char));
	pal -> cod2 = malloc(3 * sizeof(char));
	pal -> end1 = malloc(4 * sizeof(char));
	pal -> end2 = malloc(4 * sizeof(char));
	strcpy(pal -> cod1, c1);
	strcpy(pal -> cod2, c2);
	strcpy(pal -> end1, e1);
	strcpy(pal -> end2, e2);
		
	/* Atualizacao do encadeamento da lista */
	novo = malloc(sizeof(NoLstPal));
	novo -> local = pal;
	if(lista -> prox != NULL)
		lista -> prox -> ant = novo;
	novo -> ant = lista;
	novo -> prox = lista -> prox;
	lista -> prox = novo;

	return novo;
}

/* Arruma o encadeamento da lista e libera a memoria. */
void lstPal_remover(NoLstPal *alvo) {
	if(alvo -> prox == NULL) {
		alvo -> ant -> prox = NULL;	
	}
	else {
		alvo -> ant -> prox = alvo -> prox;
		alvo -> prox -> ant = alvo -> ant;
	}
	free(alvo -> local -> cod1);
	free(alvo -> local -> end1);
	free(alvo -> local -> cod2);
	free(alvo -> local -> end2);
	free(alvo -> local);
	free(alvo);
}

/* Retorna a palavra cujo ID eh igual ao dado na funcao. */
NoLstPal* lstPal_procurar(NoLstPal* lista, int key) {
	NoLstPal *aux, *procurado = NULL;
	
	for(aux = lista -> prox; aux != NULL; aux = aux -> prox) {
		if(aux -> local -> palavra == key)
			procurado = aux;
	}
	return procurado;
}

/* Percorre a lista imprimindo os dados de cada palavra. */
void lstPal_imprimir(NoLstPal *lista) {
	NoLstPal *aux;
	Palavra *aux2;
	
	for(aux = lista -> prox; aux != NULL; aux = aux -> prox) {
		aux2 = aux -> local;
		printf("Palavra: %d, Memoria: %s %s %s %s\n", aux2 -> palavra, aux2 -> cod1, aux2 -> end1, aux2 -> cod2, aux2 -> end2);
	}
}

/* Remove todos os nos da lista. */
void lstPal_removerTudo(NoLstPal* lista) {
	NoLstPal *aux;
	
	for(aux = lista -> prox; aux != NULL; aux = aux -> prox) {
		lstPal_remover(aux);
	}
}
