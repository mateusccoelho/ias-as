#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "/home/mateus/Unicamp/MC404/trab01/headers/dados.h"

Instrucao instrucoes[17];

void inicializarDados() {

	/* Inicializacao do vetor de instrucoes */
	strcpy(instrucoes[0].mnemonico, "LD");
	strcpy(instrucoes[0].hex, "01");
	strcpy(instrucoes[1].mnemonico, "LD-");
	strcpy(instrucoes[1].hex, "02");
	strcpy(instrucoes[2].mnemonico, "LD|");
	strcpy(instrucoes[2].hex, "03");
	strcpy(instrucoes[3].mnemonico, "LDmq");
	strcpy(instrucoes[3].hex, "0A");
	strcpy(instrucoes[4].mnemonico, "LDmq_mx");
	strcpy(instrucoes[4].hex, "09");
	strcpy(instrucoes[5].mnemonico, "ST");
	strcpy(instrucoes[5].hex, "21");
	strcpy(instrucoes[6].mnemonico, "ADD");
	strcpy(instrucoes[6].hex, "05");
	strcpy(instrucoes[7].mnemonico, "ADD|");
	strcpy(instrucoes[7].hex, "07");
	strcpy(instrucoes[8].mnemonico, "SUB");
	strcpy(instrucoes[8].hex, "06");
	strcpy(instrucoes[9].mnemonico, "SUB|");
	strcpy(instrucoes[9].hex, "08");
	strcpy(instrucoes[10].mnemonico, "MUL");
	strcpy(instrucoes[10].hex, "0B");
	strcpy(instrucoes[11].mnemonico, "DIF");
	strcpy(instrucoes[11].hex, "0C");
	strcpy(instrucoes[12].mnemonico, "LSH");
	strcpy(instrucoes[12].hex, "14");
	strcpy(instrucoes[13].mnemonico, "RSH");
	strcpy(instrucoes[13].hex, "15");
	strcpy(instrucoes[14].mnemonico, "JUMP");
	strcpy(instrucoes[14].hex, "01");
	strcpy(instrucoes[15].mnemonico, "JMP");
	strcpy(instrucoes[15].hex, "01");
	strcpy(instrucoes[16].mnemonico, "LD");
	strcpy(instrucoes[16].hex, "01");

}
