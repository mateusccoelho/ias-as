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
	NoLstPal *aux, *aux2;
	
	for(aux = lista -> prox; aux != NULL; aux = aux2) {
		aux2 = aux -> prox;
		lstPal_remover(aux);
	}
	free(lista);
}

void lstPal_ordenar(NoLstPal *lista) {
	NoLstPal *aux, *aux2, *menor, *antM, *auxD;
	
	for(aux = lista -> prox; aux != NULL; aux = aux -> prox) {
		menor = aux;
		/* Busca pelo no com o menor ID */
		for(aux2 = aux -> prox; aux2 != NULL; aux2 = aux2 -> prox)
			if(aux2 -> local -> palavra < menor -> local -> palavra)
				menor = aux2;
		/* Troca */
		/*printf("menor %d\n", menor -> local -> palavra);*/
		if(menor != aux) {
			aux -> ant -> prox = menor;
			antM = menor -> ant;
			menor -> ant = aux -> ant;
			if(aux -> prox != menor) {
				aux -> ant = antM;
				auxD = aux -> prox;
				aux -> prox -> ant = menor;
				if(menor -> prox != NULL)
					menor -> prox -> ant = aux;
				aux -> prox = menor -> prox;
				menor -> prox = auxD;
				antM -> prox = aux;
			}
			else {
				if(menor -> prox != NULL)
					menor -> prox -> ant = aux;
				aux -> prox = menor -> prox;
				menor -> prox = aux;
				aux -> ant = menor;
			}
			aux = menor;
		}
		/*lstPal_imprimir(lista);*/
	}
}
