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

NoLstPal* lstPal_inserir(NoLstPal *lista, char *nomeDado, int pal, int lad) {
	NoLstRot *novo;
	Rotulo *rot;
	
	/* Criacao do rotulo. */
	rot = malloc(sizeof(Rotulo));
	rot -> nome = malloc(65 * sizeof(char));
	strcpy(rot -> nome, nomeDado);
	rot -> palavra = pal;
	rot -> lado = lad;
	
	/* Atualizacao do encadeamento da lista */
	novo = malloc(sizeof(NoLstRot));
	novo -> local = rot;
	if(lista -> prox != NULL)
		lista -> prox -> ant = novo;
	novo -> ant = lista;
	novo -> prox = lista -> prox;
	lista -> prox = novo;

	return novo;
}

/* Arruma o encadeamento da lista e libera a memoria. */
void lstRot_remover(NoLstRot *alvo) {
	if(alvo -> prox == NULL) {
		alvo -> ant -> prox = NULL;	
	}
	else {
		alvo -> ant -> prox = alvo -> prox;
		alvo -> prox -> ant = alvo -> ant;
	}
	free(alvo -> local -> nome);
	free(alvo -> local);
	free(alvo);
}

/* Retorna o rotulo cujo nome eh igual ao dado na funcao. */
NoLstRot* lstRot_procurar(NoLstRot* lista, char *nome) {
	NoLstRot *aux, *procurado = NULL;
	
	for(aux = lista -> prox; aux != NULL; aux = aux -> prox) {
		if(strcmp(nome, aux -> local -> nome	) == 0)
			procurado = aux;
	}
	return procurado;
}

/* Percorre a lista imprimindo os dados de cada rotulo. */
void lstRot_imprimir(NoLstRot *lista) {
	NoLstRot *aux;
	
	for(aux = lista -> prox; aux != NULL; aux = aux -> prox) {
		printf("Rotulo: %s, palavra: %d, lado %d\n", aux -> local -> nome, aux -> local -> palavra, aux -> local -> lado);
	}
}

/* Remove todos os nos da lista. */
void lstPal_removerTudo(NoLstRot* lista) {
	NoLstRot *aux;
	
	for(aux = lista -> prox; aux != NULL; aux = aux -> prox) {
		lstRot_remover(aux);
	}
}
