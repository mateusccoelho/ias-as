#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "listaCon.h"

/* Inicializa a lista criando um no cabeca. */
void lstCon_inicializar(NoLstCon** lista) {
	*lista = malloc(sizeof(NoLstCon));
	(*lista) -> local = NULL;
	(*lista) -> ant = NULL;
	(*lista) -> prox = NULL;
}

/* Cria uma nova constante e a coloca no comeco da lista. */
NoLstCon* lstCon_inserir(NoLstCon *lista, char *apelidoDado, char *realDado) {
	NoLstCon *novo;
	Constante *con;
	
	/* Criacao da constante. */
	con = malloc(sizeof(Constante));
	con -> apelido = malloc(65 * sizeof(char));
	strcpy(con -> apelido, apelidoDado);
	con -> real = malloc(13 * sizeof(char));
	strcpy(con -> real, realDado);
	
	/* Atualizacao do encadeamento da lista */
	novo = malloc(sizeof(NoLstCon));
	novo -> local = con;
	if(lista -> prox != NULL)
		lista -> prox -> ant = novo;
	novo -> ant = lista;
	novo -> prox = lista -> prox;
	lista -> prox = novo;

	return novo;
}

/* Arruma o encadeamento da lista e libera a memoria. */
void lstCon_remover(NoLstCon *alvo) {
	if(alvo -> prox == NULL) {
		alvo -> ant -> prox = NULL;	
	}
	else {
		alvo -> ant -> prox = alvo -> prox;
		alvo -> prox -> ant = alvo -> ant;
	}
	free(alvo -> local -> apelido);
	free(alvo -> local -> real);
	free(alvo -> local);
	free(alvo);
}

/* Retorna a constante cujo apelido eh igual ao dado na funcao. */
NoLstCon* lstCon_procurar(NoLstCon* lista, char *nome) {
	NoLstCon *aux, *procurado = NULL;
	
	for(aux = lista -> prox; aux != NULL; aux = aux -> prox) {
		if(strcmp(nome, aux -> local -> apelido) == 0)
			procurado = aux;
	}
	return procurado;
}

/* Percorre a lista imprimindo os dados de cada constante. */
void lstCon_imprimir(NoLstCon *lista) {
	NoLstCon *aux;
	
	for(aux = lista -> prox; aux != NULL; aux = aux -> prox) {
		printf("Apelido: %s, real: %s\n", aux -> local -> apelido, aux -> local -> real);
	}
}

/* Remove todos os nos da lista. */
void lstCon_removerTudo(NoLstCon* lista) {
	NoLstCon *aux;
	
	for(aux = lista -> prox; aux != NULL; aux = aux -> prox) {
		lstCon_remover(aux);
	}
}
