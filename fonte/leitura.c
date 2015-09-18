#include <stdio.h>
#include <stdlib.h>
#include "/home/mateus/Unicamp/MC404/trab01/headers/leitura.h"

/* Retorna se a leitura foi bem sucedida ou nao.
 * Vetor guarda o parametro lido. */
int ler(FILE *ent, char **vetor, int *pulou, int linha) {
	int aux = 0, start = 0;
	char letra;
	(*vetor) = malloc(65 * sizeof(char));
	(*pulou) = 0;
	
	while(fscanf(ent, "%c", &letra) != EOF) {
		if(letra == '\n') {
			(*pulou) = 1;
			if(start) {
				/*Temos fim da linha e algo lido = SUCESSO*/
				(*vetor)[aux] = '\0';
				return 1; 
			}
			else {
				/*Temos fim da linha e nada lido = DEU PAU*/	
				free((*vetor));
				printf("Erro na linha %d: leitura de parametro de diretiva ou instrucao mal sucedida\n", linha);
				return 0;
			}
		}
		else if(letra == ' ' || letra == '	') {
			if(start == 0)
				continue;
			else {
				/*Algo lido = SUCESSO*/
				(*vetor)[aux] = '\0';
				return 1;
			}
		}
		start = 1;
		(*vetor)[aux] = letra;
		aux++;
	}
	if(start) {
		/*Temos fim da linha e algo lido = SUCESSO*/
		(*vetor)[aux] = '\0';
		return 1; 
	}
	else {
		/*Temos fim da linha e nada lido = DEU PAU*/	
		free((*vetor));
		printf("Erro na linha %d: leitura de parametro de diretiva ou instrucao mal sucedida\n", linha);
		return 0;
	}
}
