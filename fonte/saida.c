#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "/home/mateus/Unicamp/MC404/trab01/headers/listaPal.h"
#include "/home/mateus/Unicamp/MC404/trab01/headers/argumentos.h"
#include "/home/mateus/Unicamp/MC404/trab01/headers/saida.h"

void imprimirTela(NoLstPal *lstPal) {
	NoLstPal *aux;
	char *auxS, *auxS2;
	
	for(aux = lstPal -> prox; aux != NULL; aux = aux -> prox) {
		auxS = aux -> local -> conteudo;
		auxS2 = decToHex(aux -> local -> palavra, 3);
		printf("%s ", auxS2);
		if(strcmp(auxS2, "000") != 0)
			free(auxS2);
		printf("%c%c %c%c%c ", auxS[0], auxS[1], auxS[2], auxS[3], auxS[4]);
		printf("%c%c %c%c%c\n", auxS[5], auxS[6], auxS[7], auxS[8], auxS[9]);
	}
}

int imprimirArquivo(NoLstPal *lstPal, char *nomeArq) {
	FILE *saida;
	NoLstPal *aux;
	char *auxS, *auxS2;
	
	saida = fopen(nomeArq, "w");
	if(saida == NULL)
		return -1;
		
	for(aux = lstPal -> prox; aux != NULL; aux = aux -> prox) {
		auxS = aux -> local -> conteudo;
		auxS2 = decToHex(aux -> local -> palavra, 3);
		fprintf(saida, "%s ", auxS2);
		if(strcmp(auxS2, "000") != 0)
			free(auxS2);
		fprintf(saida, "%c%c %c%c%c ", auxS[0], auxS[1], auxS[2], auxS[3], auxS[4]);
		fprintf(saida, "%c%c %c%c%c\n", auxS[5], auxS[6], auxS[7], auxS[8], auxS[9]);
	}
	fclose(saida);
	return 0;
}
