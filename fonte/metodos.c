#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "/home/mateus/Unicamp/MC404/trab01/headers/listaRot.h"
#include "/home/mateus/Unicamp/MC404/trab01/headers/listaCon.h"
#include "/home/mateus/Unicamp/MC404/trab01/headers/dados.h"
#include "/home/mateus/Unicamp/MC404/trab01/headers/argumentos.h"
#include "/home/mateus/Unicamp/MC404/trab01/headers/leitura.h"

int mapearRotulos(char *nomeArq, NoLstRot *lstRot, NoLstCon *lstCon) {
	FILE *ent;
	char letra, comando[6], *argGen/*[65]*/, argGen2[65], argStrNum[13];
	int i, aux, palavra = 0, lado = 0, codigoErro = 0, linha = 1, pulou;
	long int argNum;
	ent = fopen(nomeArq, "r");
	if(ent == NULL)
		return -1;
	
	/* To-do: 
	 * 1. Implementar palavras e lado para reconhecer outros erros e implementar
	 * a gravacao completa de um rotulo.
	 * align OK
	 * 2. Tratar erro de fim de arquivo ou quebra de linha no meio de uma
	 * declaracao de rotulo, diretiva ou instrucao. 
	 * 3. Implementar erro de mais de um instrucao ou diretiva por linha.
	 */
	while(fscanf(ent, "%c", &letra) != EOF && codigoErro == 0) {
		if(letra == '.') {
			fscanf(ent, "%s", comando);
			if(strcmp(comando, "align") == 0) {
				fscanf(ent, "%*c%s", argStrNum);
				if(isDec(argStrNum) == 0) {
					printf("Erro na linha %d: %s eh um numero decimal invalido\n", linha, argStrNum);
					codigoErro = -1;
				}
				else {
					argNum = atol(argStrNum);
					if(argNum > 1023) {
						printf("Erro na linha %d: %ld eh um numero decimal muito grande\n", linha, argNum);
						codigoErro = -1;
					}
					else { 
						for(aux = 0; aux <= palavra; aux += argNum);
						if(lado == 0) {
							if(aux != palavra)
								palavra = aux;
						}
						else {
							if(aux == palavra) {
								palavra = aux + argNum;
								lado = 0;
							}
							else {
								palavra = argNum;
								lado = 0;
							}
						} 
					}
				}
			}
			else if(strcmp(comando, "set") == 0) {
				fscanf(ent, "%*c%s%*c%s", argGen, argStrNum);
				if(isWord(argGen) == 0) {
					printf("Erro na linha %d: %s eh uma constante ou rotulo invalida\n", linha, argGen);
					codigoErro = -1;
				}
				else {
					aux = isNumber(argStrNum);
					if(aux == 0) {
						printf("Erro na linha %d: %s eh um numero invalido\n", linha, argStrNum);
						codigoErro = -1;
					}
					else if(aux == 2) {
						printf("Erro na linha %d: %s eh um numero hexadecimal invalido\n", linha, argStrNum);
						codigoErro = -1;
					}
				}
				lstCon_inserir(lstCon, argGen, argStrNum);
			}
			else if(strcmp(comando, "org") == 0) {
				fscanf(ent, "%*c%s", argStrNum);
				aux = isNumber(argStrNum);
				if(aux == 0) {
					printf("Erro na linha %d: %s eh um numero invalido\n", linha, argStrNum);
					codigoErro = -1;
				}
				else if(aux == 2) {
					printf("Erro na linha %d: %s eh um numero hexadecimal invalido\n", linha, argStrNum);
					codigoErro = -1;
				}
			}/*
			else if(strcmp(comando, "word") == 0) {
				fscanf(ent, "%*c%s", argGen);
				printf("a string: %s", argGen);
				aux = isWrong(argGen);
				if(aux == 0) {
					printf("Erro na linha %d: %s eh um argumento invalido\n", linha, argGen);
					codigoErro = -1;
				}
				else if(aux == 3) {
					printf("Erro na linha %d: %s eh um numero hexadecimal invalido\n", linha, argGen);
					codigoErro = -1;
				}
			}*/
			else if(strcmp(comando, "word") == 0) {
				if(ler(ent, &argGen, &pulou) == 0) {
					printf("deu pau\n");
				}
				else {
					printf("a string: %s\n", argGen);	
				}
			}
			else if(strcmp(comando, "wfill") == 0) {
				fscanf(ent, "%*c%s%*c%s", argStrNum, argGen);
				if(isDec(argStrNum) == 0) {
					printf("Erro na linha %d: %s eh um numero decimal invalido\n", linha, argStrNum);
					codigoErro = -1;
				}
				else {
					aux = isWrong(argGen);
					if(aux == 0) {
						printf("Erro na linha %d: %s eh um argumento invalido\n", linha, argGen);
						codigoErro = -1;
					}
					else if(aux == 3) {
						printf("Erro na linha %d: %s eh um numero hexadecimal invalido\n", linha, argGen);
						codigoErro = -1;
					}
				}
			}
			else {
				printf("Erro na linha %d: %s diretiva nao encontrada\n", linha, comando);
				codigoErro = -1;
			}
		}
		else if(letra == '#') {
			while(fscanf(ent, "%c", &letra) != EOF && letra != '\n');
			linha++;
		}
		else if((letra >= 65 && letra <= 90) || (letra >= 97 && letra <= 122) || (letra >= 48 && letra <= 57) || letra == '_') {
			aux = 0;			
			do{
				argGen[aux] = letra;
				aux++;
				fscanf(ent, "%c", &letra);
			} while(letra != ' ' && letra != '\n');
			if(letra == '\n')
				linha++;
			argGen[aux] = '\0';
			if(argGen[aux - 1] == ':') {
				argGen[aux - 1] = '\0';
				if(isWord(argGen) == 0) {
					printf("Erro na linha %d: %s eh um rotulo invalido\n", linha, argGen);
					codigoErro = -1;
				}
				/*lstRot_inserir(lstRot, argGen, XX, YY);*/
			}
			else {
				if(isWord(argGen) == 0) {
					printf("Erro na linha %d: %s eh uma instrucao invalida\n", linha, argGen);
					codigoErro = -1;
				}
				else {
					for(aux = 0; aux < 17; aux++) {
						if(strcmp(argGen, instrucoes[aux].mnemonico) == 0) {
							if(aux != 3 && aux != 12 && aux != 13) {
								fscanf(ent, "%*c");
								i = 0;
								do{
									fscanf(ent, "%c", &letra);
									argGen2[i] = letra;
									i++;
								} while(letra != '"');
								argGen2[i - 1] = '\0';
								i = isWrong(argGen2);
								if(i == 0) {
									printf("Erro na linha %d: %s eh um argumento invalido\n", linha, argGen2);
									codigoErro = -1;
								}
								else if(i == 3) {
									printf("Erro na linha %d: %s eh um numero hexadecimal invalido\n", linha, argGen2);
									codigoErro = -1;
								}
							}
							break;
						}
					}
					if(aux == 17) {
						printf("Erro na linha %d: %s instrucao nao encontrada\n", linha, argGen);
						codigoErro = -1;
					}
				}
			}
		}
		else if(letra == '\n') {
			linha++;
			printf("Palavra: %d, lado: %d\n", palavra, lado);
		}
		else if(letra != '	' && letra != ' ') {
			printf("Erro na linha %d: %c eh um caractere invalido\n", linha, letra);
			codigoErro = -1;
		}
	}
	
	fclose(ent);
	return codigoErro;
}
