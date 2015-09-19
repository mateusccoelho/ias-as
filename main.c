#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "/home/mateus/Unicamp/MC404/trab01/headers/listaRot.h"
#include "/home/mateus/Unicamp/MC404/trab01/headers/listaPal.h"
#include "/home/mateus/Unicamp/MC404/trab01/headers/dados.h"

int mapearRotulos(char *nomeArq, NoLstRot *lstRot);
int gerarMapa(char *nomeArq, NoLstRot *lstRot, NoLstPal *lstPal);
int verificarLinha(int *tipos, char* ordem, int linha, int ordemNum);
char* decToHex(char* decimal);

int main (int argc, char *argv[]) {
	
	int codigo = 0;
	NoLstRot *lstRot;
	NoLstPal *lstPal;
	
	lstRot_inicializar(&lstRot);
	lstPal_inicializar(&lstPal);
	inicializarDados();
	
	codigo = mapearRotulos(argv[1], lstRot);
	if(codigo == 0) {
		codigo = gerarMapa(argv[1], lstRot, lstPal);
		if(codigo == 0) {
			/*if(argc == 2) {
				codigo = mapearRotulos(argv[1], lstRot);
			}
			else if(argc == 3) {
				codigo = mapearRotulos(argv[1], lstRot);
			}*/
		}
	}
		
	
	return codigo; 
}
