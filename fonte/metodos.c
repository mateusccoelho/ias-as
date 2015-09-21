#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "/home/mateus/Unicamp/MC404/trab01/headers/listaRot.h"
#include "/home/mateus/Unicamp/MC404/trab01/headers/listaCon.h"
#include "/home/mateus/Unicamp/MC404/trab01/headers/dados.h"
#include "/home/mateus/Unicamp/MC404/trab01/headers/argumentos.h"
#include "/home/mateus/Unicamp/MC404/trab01/headers/leitura.h"
#include "/home/mateus/Unicamp/MC404/trab01/headers/listaPal.h"
#include "/home/mateus/Unicamp/MC404/trab01/headers/metodos.h"

/* To-Do:
 * 1. implementar conversao de numero decimal negativo
 * 3. bugs de sobrescrever linhas e palavra ultrapassar 1024
 * 4. implementar saida na sterro
 * OK 5. revisao no metodos.c
 * OK 6. revisao nos headers
 * 7. Passa valgrind 
 */

int gerarMapa(char *nomeArq, NoLstRot *lstRot, NoLstPal *lstPal) {
	FILE *ent;
	NoLstCon *lstCon, *auxC;
	NoLstRot *auxR;
	char letra, comando[6], *argGen, *argGen2, *auxS, *auxS2, cod[3], end[4], memoria[11];
	int i, aux, palavra = 0, lado = 0, codigoErro = 0, linha = 1, pulou;
	long int argNum;
	
	ent = fopen(nomeArq, "r");
	if(ent == NULL)
		return -1;
	
	lstCon_inicializar(&lstCon);
	memoria[0] = '\0';
	
	while(fscanf(ent, "%c", &letra) != EOF && codigoErro == 0) {
		if(letra == '.') {
			fscanf(ent, "%s", comando);
			if(strcmp(comando, "align") == 0) {
				/* OK */
				ler(ent, &argGen, &pulou, linha);
				if(lado == 1) {
					strcat(memoria, "00000");
					lstPal_inserir(lstPal, palavra, memoria);
					memoria[0] = '\0';
				}
				argNum = atol(argGen);
				for(aux = 0; aux < palavra; aux += argNum);
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
				if(pulou == 1)
					linha++;
				free(argGen);
			}
			else if(strcmp(comando, "set") == 0) {
				/* OK */
				ler(ent, &argGen, &pulou, linha);
				ler(ent, &argGen2, &pulou, linha);
				lstCon_inserir(lstCon, argGen, argGen2);
				if(pulou == 1)
					linha++;
				free(argGen2);
				free(argGen);
			}
			else if(strcmp(comando, "org") == 0) {
				/* OK */
				ler(ent, &argGen, &pulou, linha);
				if(lado == 1) {
					strcat(memoria, "00000");
					lstPal_inserir(lstPal, palavra, memoria);
					memoria[0] = '\0';
				}
				if(argGen[1] == 'x') {
					sscanf(argGen, "%x", &aux);
					palavra = aux;
					lado = 0;
				}
				else {
					palavra = atoi(argGen);
					lado = 0;
				}
				if(pulou == 1)
					linha++;
				free(argGen);
			}
			else if(strcmp(comando, "word") == 0) {
				/* OK */
				ler(ent, &argGen, &pulou, linha);
				if(argGen[0] == '0' && argGen[1] == 'x')
					lstPal_inserir(lstPal, palavra, argGen+2);
				else if(argGen[0] >= 48 && argGen[0] <= 57) {
					auxS = decToHex(atol(argGen), 10);
					lstPal_inserir(lstPal, palavra, auxS);
					if(strcmp(auxS, "0000000000") != 0)
						free(auxS);
				}
				else if(isRotulo(argGen) == 1) {
					auxR = lstRot_procurar(lstRot, argGen);
					if(auxR == NULL) {
						printf("Erro na linha %d: o rotulo \"%s\" nao foi encontrado\n", linha, argGen);
						codigoErro = -1;
					}
					else {
						auxS = decToHex(auxR -> local -> palavra, 10);
						lstPal_inserir(lstPal, palavra, auxS);
						if(strcmp(auxS, "0000000000") != 0)
							free(auxS);
					}
				}
				else {
					auxC = lstCon_procurar(lstCon, argGen);
					if(auxC == NULL) {
						printf("Erro na linha %d: a constante \"%s\" nao foi encontrada\n", linha, argGen);
						codigoErro = -1;
					}
					else {
						if((auxC -> local -> real)[0] == '0' && (auxC -> local -> real)[1] == 'x')
							lstPal_inserir(lstPal, palavra, (auxC -> local -> real)+2);
						else {
							auxS = decToHex(atol(auxC -> local -> real), 10);
							lstPal_inserir(lstPal, palavra, auxS);
							if(strcmp(auxS, "0000000000") != 0)
								free(auxS);
						}
					}
				}
				palavra++;
				if(pulou == 1)
					linha++;
				free(argGen);
			}
			else if(strcmp(comando, "wfill") == 0) {
				/* OK */
				ler(ent, &argGen, &pulou, linha);
				ler(ent, &argGen2, &pulou, linha);
				aux = atoi(argGen);
				for(i = 0; i < aux; i++) {
					if(argGen2[0] == '0' && argGen2[1] == 'x')
						lstPal_inserir(lstPal, palavra, argGen2+2);
					else if(argGen2[0] >= 48 && argGen2[0] <= 57) {
						auxS = decToHex(atol(argGen2), 10);
						lstPal_inserir(lstPal, palavra, auxS);
						if(strcmp(auxS, "0000000000") != 0)
							free(auxS);
					}
					else if(isRotulo(argGen2) == 1) {
						auxR = lstRot_procurar(lstRot, argGen2);
						if(auxR == NULL) {
							printf("Erro na linha %d: o rotulo \"%s\" nao foi encontrado\n", linha, argGen2);
							codigoErro = -1;
							break;
						}
						else {
							auxS = decToHex(auxR -> local -> palavra, 10);
							lstPal_inserir(lstPal, palavra, auxS);
							if(strcmp(auxS, "0000000000") != 0)
								free(auxS);
						}
					}
					else {
						auxC = lstCon_procurar(lstCon, argGen2);
						if(auxC == NULL) {
							printf("Erro na linha %d: a constante \"%s\" nao foi encontrada\n", linha, argGen2);
							codigoErro = -1;
							break;
						}
						else {
							if((auxC -> local -> real)[0] == '0' && (auxC -> local -> real)[1] == 'x')
								lstPal_inserir(lstPal, palavra, (auxC -> local -> real)+2);
							else {
								auxS = decToHex(atol(auxC -> local -> real), 10);
								lstPal_inserir(lstPal, palavra, auxS);
								if(strcmp(auxS, "0000000000") != 0)
									free(auxS);
							}
						}
					}
					palavra++;
				}
				if(pulou == 1)
					linha++;
				free(argGen2);
				free(argGen);
			}
		}
		else if(letra == '#') {
			while(fscanf(ent, "%c", &letra) != EOF && letra != '\n');
			linha++;
		}
		else if((letra >= 65 && letra <= 90) || (letra >= 97 && letra <= 122) || (letra >= 48 && letra <= 57) || letra == '_') {
			aux = 0;
			argGen = malloc(65 * sizeof(char));			
			
			do{
				argGen[aux] = letra;
				aux++;
				fscanf(ent, "%c", &letra);
			} while(letra != ' ' && letra != '\n');
			argGen[aux] = '\0';
			
			if(argGen[aux - 1] == ':') {
				if(letra == '\n')
					linha++;
			}		
			else {
				for(aux = 0; aux < 17; aux++) {
					if(strcmp(argGen, instrucoes[aux].mnemonico) == 0) {
						/*  OK  dentro do condicional: ajustar parametros, cod e end */
						if(aux != 3 && aux != 12 && aux != 13) {
							/* Instrucoes COM parametros*/
							ler(ent, &argGen2, &pulou, linha);
							
							auxS = malloc(65 * sizeof(char));
							strcpy(auxS, argGen2+1);
							for(i = 0; auxS[i] != '\0'; i++);
							auxS[i - 1] = '\0';
								
							if(auxS[0] == '0' && auxS[1] == 'x') {
								strcpy(cod, instrucoes[aux].hex);
								strcpy(end, auxS+9);
							}
							else if(auxS[0] >= 48 && auxS[0] <= 57) {
								auxS2 = decToHex(atoi(auxS), 3);
								strcpy(cod, instrucoes[aux].hex);
								strcpy(end, auxS2);
								if(strcmp(auxS2, "000") != 0)	
									free(auxS2);
							}
							else {   /*Um rotulo */
								auxS[i - 1] = ':';
								auxR = lstRot_procurar(lstRot, auxS);
								if(auxR == NULL) {
									printf("Erro na linha %d: o rotulo \"%s\" nao foi encontrado\n", linha, auxS);
									codigoErro = -1;
								}
								else{
									auxS2 = decToHex(auxR -> local -> palavra, 3);
									strcpy(end, auxS2);
									if(strcmp(auxS2, "000") != 0)
										free(auxS2);
									if(aux >=  14 && aux <= 16) {
										if(auxR -> local -> lado == 0)
											strcpy(cod, instrucoes[aux].hex);
										else {
											if(aux == 14) strcpy(cod, "10");
											else if(aux == 15) strcpy(cod, "0E");
											else strcpy(cod, "13");
										}
									}
									else
										strcpy(cod, instrucoes[aux].hex); 
								}
							}
							if(pulou == 1)
								linha++;
							free(auxS);
							free(argGen2);
							
						}
						else {
							/* Instrucoes SEM parametros */
							strcpy(cod, instrucoes[aux].hex);
							strcpy(end, "000");
							if(letra == '\n')
								linha++;
						}
						/* processamento de palavra */
						strcat(memoria, cod);
						strcat(memoria, end);
						if(lado == 1) {
							lstPal_inserir(lstPal, palavra, memoria);
							memoria[0] = '\0';
							palavra++;
							lado = 0;
						}
						else
							lado = 1;
						break;
					}
				}
			}
			free(argGen);
		}
		else if(letra == '\n')
			linha++;
	}
	
	/*Verifica o termino da leitura com palavra meio preenchida.*/
	if(lado == 1) {
		strcat(memoria, "00000");
		lstPal_inserir(lstPal, palavra, memoria);
	}
	
	lstCon_removerTudo(lstCon);
	lstRot_removerTudo(lstRot);
	fclose(ent);
	return codigoErro;
}

/* vetor Tipos:       rotulo || diretiva || instrucao*/
int verificarLinha(int *tipos, char* ordem, int linha, int ordemNum) {
	int i;
	for(i = 0; i < 3; i++) {
		if(tipos[i] > 1) {
			if(i = 0)	
				printf("Erro na linha %d: linha com mais de um rotulo\n", linha);
			else if(i = 1)
				printf("Erro na linha %d: linha com mais de uma diretiva\n", linha);
			else
				printf("Erro na linha %d: linha com mais de uma instrucao\n", linha);
			return -1;
		}
	}
	if(tipos[1] == 1 && tipos[2] == 1) {
		printf("Erro na linha %d: linha com uma instrucao e uma diretiva\n", linha);
		return -1;
	}

	if(ordemNum > 1 && (ordem[0] == 'd' || ordem[0] == 'i')) {
		printf("Erro na linha %d: diretiva ou instrucao antes do rotulo\n", linha);
		return -1;
	}
	for(i = 0; i < 3; i++)
		tipos[i] = 0;
	return 0;
}

int mapearRotulos(char *nomeArq, NoLstRot *lstRot) {
	FILE *ent;
	char letra, comando[6], *argGen, *argGen2, ordem[2];
	int i, aux, palavra = 0, lado = 0, codigoErro = 0, linha = 1, pulou, tipos[3], ordemNum = 0;
	long int argNum;
	ent = fopen(nomeArq, "r");
	if(ent == NULL)
		return -1;
	
	for(i = 0; i < 3; i++)
		tipos[i] = 0;
		
	while(fscanf(ent, "%c", &letra) != EOF && codigoErro == 0) {
		if(letra == '.') {
			fscanf(ent, "%s", comando);
			if(strcmp(comando, "align") == 0) {
				if(ler(ent, &argGen, &pulou, linha) == 0)
					codigoErro = -1;
				else {
					if(isArg(3, argGen, linha, 0, 1023) == 0)
						codigoErro = -1;
					else {
						argNum = atol(argGen);
						for(aux = 0; aux < palavra; aux += argNum);
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
						tipos[1]++;
						if(ordemNum < 2)
							ordem[ordemNum] = 'd';
						ordemNum++;
						if(pulou == 1) {
							codigoErro = verificarLinha(tipos, ordem, linha, ordemNum);
							linha++;
							ordemNum = 0;
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
							if(isArg(2, argGen2, linha, 0, 2147483647) == 0)
								codigoErro = -1;
							else {
								tipos[1]++;
								if(ordemNum < 2)
									ordem[ordemNum] = 'd';
								ordemNum++;
								if(pulou == 1) {
									codigoErro = verificarLinha(tipos, ordem, linha, ordemNum);								
									linha++;
									ordemNum = 0;
								}							
							}
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
					if(isArg(2, argGen, linha, 0, 1023) == 0)
						codigoErro = -1;
					else {
						if(argGen[1] == 'x') {
							sscanf(argGen, "%x", &aux);
							if(aux > 1023) {
								printf("Erro na linha %d: numero hexacimal \"%s\" ultrapassa o valor aceitavel de um endereco de palavra\n", linha, argGen);
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
						if(codigoErro == 0) {
							tipos[1]++;
							if(ordemNum < 2)
								ordem[ordemNum] = 'd';
							ordemNum++;
							if(pulou == 1) {
								codigoErro = verificarLinha(tipos, ordem, linha, ordemNum);
								linha++;
								ordemNum = 0;
							}
						}
					}
					free(argGen);
				}
			}
			else if(strcmp(comando, "word") == 0) {
				if(ler(ent, &argGen, &pulou, linha) == 0)
					codigoErro = -1;
				else {
					if(isArg(4, argGen, linha, 0, 4294967295) == 0)
						codigoErro = -1;
					else {
						if(lado == 1) {
							printf("Erro na linha %d: alocacao de dado na memoria irregular, use align\n", linha);
							codigoErro = -1;
						}
						else {
							palavra++;
							tipos[1]++;
							if(ordemNum < 2)
								ordem[ordemNum] = 'd';
							ordemNum++;
							if(pulou == 1) {
								codigoErro = verificarLinha(tipos, ordem, linha, ordemNum);
								linha++;
								ordemNum = 0;
							}
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
							if(isArg(4, argGen2, linha, -2147483648, 2147483647) == 0)
								codigoErro = -1;
							else {
								if(lado == 1) {
									printf("Erro na linha %d: alocacao de dado na memoria irregular, use align\n", linha);
									codigoErro = -1;
								}	
								else {
									palavra += atoi(argGen);
									tipos[1]++;
									if(ordemNum < 2)
										ordem[ordemNum] = 'd';
									ordemNum++;
									if(pulou == 1) {
										codigoErro = verificarLinha(tipos, ordem, linha, ordemNum);
										linha++;
										ordemNum = 0;
									}									
								}
							}
							free(argGen2);
						}
					}
					free(argGen);
				}
			}
			else {
				printf("Erro na linha %d: diretiva \"%s\" nao encontrada\n", linha, comando);
				codigoErro = -1;
			}
		}
		else if(letra == '#') {
			while(fscanf(ent, "%c", &letra) != EOF && letra != '\n');
			codigoErro = verificarLinha(tipos, ordem, linha, ordemNum);
			linha++;
			ordemNum = 0;
		}
		else if((letra >= 65 && letra <= 90) || (letra >= 97 && letra <= 122) || (letra >= 48 && letra <= 57) || letra == '_') {
			aux = 0;
			argGen = malloc(65 * sizeof(char));
			/* Le alguma coisa */			
			do{
				argGen[aux] = letra;
				aux++;
				fscanf(ent, "%c", &letra);
			} while(letra != ' ' && letra != '\n');
			argGen[aux] = '\0';
			/* Verifica se eh rotulo */
			if(argGen[aux - 1] == ':') {
				argGen[aux - 1] = '\0';
				if(isArg(1, argGen, linha, 0, 0) == 0)
					codigoErro = -1;
				else {
					argGen[aux - 1] = ':';
					lstRot_inserir(lstRot, argGen, palavra, lado);
					
					tipos[0]++;
					if(ordemNum < 2)
						ordem[ordemNum] = 'r';
					ordemNum++;
					if(letra == '\n' && codigoErro == 0) {
						codigoErro = verificarLinha(tipos, ordem, linha, ordemNum);
						linha++;
						ordemNum = 0;
					}
				}
			}
			/* caso contrario eh instrucao */		
			else {
				if(isArg(5, argGen, linha, 0, 0) == 0)
					codigoErro = -1;
				else {
					for(aux = 0; aux < 17; aux++) {
						if(strcmp(argGen, instrucoes[aux].mnemonico) == 0) {
							if(aux != 3 && aux != 12 && aux != 13) {
								if(ler(ent, &argGen2, &pulou, linha) == 0)
									codigoErro = -1;
								else {
									if(isInstArg(argGen2, linha, 0, 1023) == 0)
										codigoErro = -1;
									else {
										if(lado == 1) {
											palavra++;
											lado = 0;
										}
										else {
											lado = 1;
										}
										tipos[2]++;
										if(ordemNum < 2)
											ordem[ordemNum] = 'i';
										ordemNum++;
										if(pulou == 1) {
											codigoErro = verificarLinha(tipos, ordem, linha, ordemNum);
											linha++;
											ordemNum = 0;
										}
									}
									free(argGen2);	
								}
							}
							else {
								if(lado == 1) {
									palavra++;
									lado = 0;
								}
								else {
									lado = 1;
								}
								tipos[2]++;
								if(ordemNum < 2)
									ordem[ordemNum] = 'i';
								ordemNum++;
								if(letra == '\n') {
									codigoErro = verificarLinha(tipos, ordem, linha, ordemNum);
									linha++;
									ordemNum = 0;
								}
							}
							break;
						}
					}
					if(aux == 17) {
						printf("Erro na linha %d: instrucao \"%s\" nao encontrada\n", linha, argGen);
						codigoErro = -1;
					}
				}
			}
			free(argGen);
		}
		else if(letra == '\n') {
			codigoErro = verificarLinha(tipos, ordem, linha, ordemNum);
			linha++;
			ordemNum = 0;
		}
		else if(letra != '	' && letra != ' ') {
			printf("Erro na linha %d: %c eh um caractere invalido\n", linha, letra);
			codigoErro = -1;
		}
	}
	fclose(ent);
	return codigoErro;
}
