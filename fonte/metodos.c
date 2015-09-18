#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "/home/mateus/Unicamp/MC404/trab01/headers/listaRot.h"
#include "/home/mateus/Unicamp/MC404/trab01/headers/listaCon.h"
#include "/home/mateus/Unicamp/MC404/trab01/headers/dados.h"
#include "/home/mateus/Unicamp/MC404/trab01/headers/argumentos.h"
#include "/home/mateus/Unicamp/MC404/trab01/headers/leitura.h"

void verificarLinha() {

}

int mapearRotulos(char *nomeArq, NoLstRot *lstRot, NoLstCon *lstCon) {
	FILE *ent;
	char letra, comando[6], *argGen, *argGen2;
	int i, aux, palavra = 0, lado = 0, codigoErro = 0, linha = 1, pulou, tipos[4];
	long int argNum;
	ent = fopen(nomeArq, "r");
	if(ent == NULL)
		return -1;
	
	for(i = 0; i < 4; i++)
		tipos[i] = 0;
	
	/* To-do:
	 * 1. Verificar se as linhas estao sendo contadas direito 
	 * 2. Verificar erro de instrucao sem argumento que recebe argumento.
	 * 3. Implementar erro de mais de um instrucao ou diretiva por linha.
	 */
	while(fscanf(ent, "%c", &letra) != EOF && codigoErro == 0) {
		printf("Palavra: %d Lado: %d\n", palavra, lado);
		if(letra == '.') {
			fscanf(ent, "%s", comando);
			if(strcmp(comando, "align") == 0) {
				if(ler(ent, &argGen, &pulou, linha) == 0)
					codigoErro = -1;
				else {
					if(pulou == 1)
						linha++;
					if(isArg(3, argGen, linha, 0, 1023) == 0)
						codigoErro = -1;
					else {
						/*Verificar se eh isso mesmo*/
						argNum = atol(argGen);
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
					free(argGen);
				}
			}
			else if(strcmp(comando, "set") == 0) {
				if(ler(ent, &argGen, &pulou, linha) == 0)
					codigoErro = -1;
				else {
					if(pulou == 1) {
						printf("Erro na linha %d: a diretiva tem apenas um parametro nesse linha\n", linha);
						codigoErro = -1;
					}
					else if(isArg(1, argGen, linha, 0, 0) == 0)
						codigoErro = -1;
					else {
						if(ler(ent, &argGen2, &pulou, linha) == 0)
							codigoErro = -1;
						else {
							if(pulou == 1)
								linha++;
							if(isArg(2, argGen2, linha, 0, 2147483647) == 0)
								codigoErro = -1;
							else
								lstCon_inserir(lstCon, argGen, argGen2);
							free(argGen2);
						}
					}
					free(argGen);
				}
			}
			else if(strcmp(comando, "org") == 0) {
				if(ler(ent, &argGen, &pulou, linha) == 0)
					codigoErro = -1;
				else {
					if(pulou == 1)
						linha++;
					if(isArg(2, argGen, linha, 0, 1023) == 0)
						codigoErro = -1;
					else {
						if(argGen[1] == 'x') {
							sscanf(argGen, "%x", &aux);
							if(aux > 1023) {
								printf("Erro na linha %d: \"%s\" ultrapassa o valor aceitavel de um endereco de palavra\n", linha, argGen);
								codigoErro = -1;
							}
							else {
								palavra = aux;
								lado = 0;
							}
						}
						else {
							palavra = atoi(argGen);
							lado = 0;
						}
					}
					free(argGen);
				}
			}
			else if(strcmp(comando, "word") == 0) {
				if(ler(ent, &argGen, &pulou, linha) == 0)
					codigoErro = -1;
				else {
					if(pulou == 1)
						linha++;
					if(isArg(4, argGen, linha, 0, 4294967295) == 0)
						codigoErro = -1;
					else {
						if(lado == 0)
							palavra++;
						else {
							printf("Erro na linha %d: alocacao de dado na memoria irregular, use align\n", linha);
							codigoErro = -1;
						}
					}
					free(argGen);
				}
			}
			else if(strcmp(comando, "wfill") == 0) {
				if(ler(ent, &argGen, &pulou, linha) == 0)
					codigoErro = -1;
				else {
					if(pulou == 1) {
						printf("Erro na linha %d: a diretiva tem apenas um parametro nesse linha\n", linha);
						codigoErro = -1;
					}
					else if(isArg(3, argGen, linha, 0, 1023) == 0)
						codigoErro = -1;
					else {
						if(ler(ent, &argGen2, &pulou, linha) == 0)
							codigoErro = -1;
						else {
							if(pulou == 1)
								linha++;
							if(isArg(4, argGen2, linha, -2147483648, 2147483647) == 0)
								codigoErro = -1;
							else {
								if(lado == 0)
									palavra = palavra + atoi(argGen) - 1;
								else {
									printf("Erro na linha %d: alocacao de dado na memoria irregular, use align\n", linha);
									codigoErro = -1;
								}
							}
							free(argGen2);
						}
					}
					free(argGen);
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
				if(isArg(1, argGen, linha, 0, 0) == 0) {
					printf("Erro na linha %d: %s eh um rotulo invalido\n", linha, argGen);
					codigoErro = -1;
				}
				else
					lstRot_inserir(lstRot, argGen, palavra, lado);
			}
			else {
				if(isArg(1, argGen, linha, 0, 0) == 0) {
					printf("Erro na linha %d: %s eh uma instrucao invalida\n", linha, argGen);
					codigoErro = -1;
				}
				else {
					for(aux = 0; aux < 17; aux++) {
						if(strcmp(argGen, instrucoes[aux].mnemonico) == 0) {
							if(aux != 3 && aux != 12 && aux != 13) {
								if(ler(ent, &argGen2, &pulou, linha) == 0)
									codigoErro = -1;
								else {
									if(pulou == 1)
										linha++;
									if(isInstArg(argGen2, linha, 0, 1023) == 0)
										codigoErro = -1;
									else {
										/* avancar */
										if(lado == 1) {
											palavra++;
											lado = 0;
										}
										else {
											lado = 1;
										}
									}
									free(argGen2);	
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
			free(argGen);
		}
		else if(letra == '\n') {
			linha++;
		}
		else if(letra != '	' && letra != ' ') {
			printf("Erro na linha %d: %c eh um caractere invalido\n", linha, letra);
			codigoErro = -1;
		}
	}
	
	fclose(ent);
	return codigoErro;
}
