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

NoLstPal* lstPal_inserir(NoLstPal *lista, int numPal, char *cont) {
	NoLstPal *novo;
	Palavra *pal;
	
	/* Criacao da palavra. */
	pal = malloc(sizeof(Palavra));
	pal -> palavra = numPal;
	pal -> conteudo = malloc(11 * sizeof(char));
	strcpy(pal -> conteudo, cont);
		
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
	free(alvo -> local -> conteudo);
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
		printf("Palavra: %d, Memoria: %s\n", aux2 -> palavra, aux2 -> conteudo);
	}
}

/* Remove todos os nos da lista. */
void lstPal_removerTudo(NoLstPal* lista) {
	NoLstPal *aux;
	
	for(aux = lista -> prox; aux != NULL; aux = aux -> prox) {
		lstPal_remover(aux);
	}
}

void lstPal_ordenar(NoLstPal *lista) {
	/* Ordenacao */
}
