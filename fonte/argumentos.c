#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "/home/mateus/Unicamp/MC404/trab01/headers/argumentos.h"
/*
long int toDecimal(char *dado) {
	int i, j, valor;
	for(i = 11, j = 0; i > 1; i--, j++) {
		if(dado[i] != '0')
	}
}*/

int isDiretiva(char* dado) {
	return (dado[0] == '.');
}

int isHex(char *dado) {
	int i;
	
	/* Verificar erro de tamanho de numero errado. */
	if(dado[0] == '0' && dado[1] == 'x') {
		for(i = 0; i < 10; i++) {
			if(!((dado[2 + i] >= 48 && dado[2 + i] <= 57) || (dado[2 + i] >= 65 && dado[2 + i] <= 70) || (dado[2 + i] >= 97 && dado[2 + i] <= 102))) {
				return -1;
			}
		}
		return 1;
	}
	else
		return 0;
}

int isDec(char *dado, int min, unsigned int max) {
	int i;
	long int numero;
	
	if(!((dado[0] >= 48 && dado[0] <= 57) || dado[0] == '-'))
		return 0;
	else {
		for(i = 1; dado[i] != '\0'; i++) {
			if(!(dado[i] >= 48 && dado[i] <= 57)) {
				return 0;
			}
		}
	}
	/*verificar se o numero esta no intervalo apropriado */
	numero = atol(dado);
	if(numero >= min && numero <= max)
		return 1;
	else
		return -1;
}

int isWord(char *dado) {
	int i;
	
	if(!((dado[0] >= 65 && dado[0] <= 90) || (dado[0] >= 97 && dado[0] <= 122) || dado[0] == '_'))
		return 0;
	else {
		for(i = 1; dado[i] != '\0'; i++) {
			if(!((dado[i] >= 65 && dado[i] <= 90) || (dado[i] >= 97 && dado[i] <= 122) || (dado[i] >= 48 && dado[i] <= 57) || dado[i] == '_'))
				return 0;
		}	
	}
	return 1; /*Eh palavra */
}

int isNumber(char *dado) {
	int aux;
	
	if(isDec(dado, 00, 00) == 0) {
		aux = isHex(dado);
		if(aux == 0)
			return 0; /* Nada */
		else if(aux == -1)
			return 2; /* hex invalid */
		else
			return 3; /* hex valid */
	}
	else 
		return 1; /* decimal valido*/ 
}

int isWrong(char *dado) {
	int aux;
	
	if(isWord(dado) == 0) {
		aux = isNumber(dado);
		if(aux == 0)
			return 0;
		else if(aux == 1)
			return 2;
		else if(aux == 2)
			return 3;
		else
			return 4;
	}
	else
		return 1;
}

int isRotulo(char *dado) {
	int aux;
	
	for(aux = 0; dado[aux] != '\0'; aux++);
	if(dado[aux - 1] == ':') {
		return 1;
	}
	return 0;
}

/*Funcao certinha*/
int isArg(int codigo, char* dado, int linha, int min, unsigned int max) {
	int aux;
	
	if(codigo == 1) { /* SYM*/
		if(isWord(dado)) {
			printf("Erro na linha %d: \"%s\" nao eh uma palavra valida\n", linha, dado);
			return 0;
		}
		else
			return 1;
	}
	else if(codigo == 2) { /* Numero: hex, dec*/
		aux = isHex(dado);
		if(aux == 1)
			return 1;
		if(aux == -1) {
			printf("Erro na linha %d: \"%s\" eh um numero hexadecimal invalido\n", linha, dado);
			return 0;
		}
		aux = isDec(dado, min, max);
		if(aux == 1)
			return 1;
		if(aux == -1) {
			printf("Erro na linha %d: \"%s\" eh um numero decimal fora do padrao de tamanho\n", linha, dado);
			return 0;
		}
		printf("Erro na linha %d: \"%s\" nao eh um argumento de numero valido\n", linha, dado);
		return 0;
	}
	else if(codigo == 3) { /* Decimal */
		aux = isDec(dado, min, max);
		if(aux == 1)
			return 1;
		else if(aux == -1) {
			printf("Erro na linha %d: \"%s\" eh um numero decimal fora do padrao de tamanho\n", linha, dado);
			return 0;
		}
		else {
			printf("Erro na linha %d: \"%s\" nao eh um numero decimal\n", linha, dado);
		}
	}
	else if(codigo == 4) { /* Tudo: hex, dec, rot, SYM */
		aux = isHex(dado);
		if(aux == 1)
			return 1;
		if(aux == -1) {
			printf("Erro na linha %d: \"%s\" eh um numero hexadecimal invalido\n", linha, dado);
			return 0;
		}
		aux = isDec(dado, min, max);
		if(aux == 1)
			return 1;
		if(aux == -1) {
			printf("Erro na linha %d: \"%s\" eh um numero decimal fora do padrao de tamanho\n", linha, dado);
			return 0;
		}
		aux = isRotulo(dado);
		if(aux == 1) {
			for(aux = 0; dado[aux] != '\0'; aux++);
			dado[aux - 1] = '\0';
			if(isWord(dado) == 1)
				return 1;
			else {
				printf("Erro na linha %d: \"%s\" eh um rotulo nao valido\n", linha, dado);
				return 0;
			} 
		}
		aux = isWord(dado);
		if(aux == 1)
			return 1;
		printf("Erro na linha %d: \"%s\" eh um argumento nao valido\n", linha, dado);
		return 0;
	}
}

int isInstArg(char* dado, int linha, int min, unsigned int max) {
	int aux;

	for(aux = 0; dado[aux] != '\0'; aux++);
	if(dado[0] == '"' && dado[aux - 1] == '"') {
		/*Deixando a string usavel para as funcoes de analise*/
		dado[aux - 1] = '\0';
		dado++; 
		/* Decimal */
		aux = isDec(dado, min, max);
		if(aux == 1)
			return 1;
		if(aux == -1) {
			printf("Erro na linha %d: \"%s\" eh um numero decimal fora do padrao de tamanho\n", linha, dado);
			return 0;
		}
		/* Hexadecimal */
		aux = isHex(dado);
		printf("A verif: %d\n", aux);
		if(aux == 1)
			return 1;
		if(aux == -1) {
			printf("Erro na linha %d: \"%s\" eh um numero hexadecimal invalido\n", linha, dado);
			return 0;
		}
		aux = isWord(dado);
		if(aux == 1)
			return 1;
		printf("Erro na linha %d: \"%s\" eh um argumento de instrucao nao valido\n", linha, dado);
		return 0;
	}
	else {
		printf("Erro na linha %d: \"%s\" nao eh um argumento de instrucao\n", linha, dado);
		return 0;
	}	
}
