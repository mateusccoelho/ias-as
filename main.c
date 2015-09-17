#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "/home/mateus/Unicamp/MC404/trab01/headers/listaRot.h"
#include "/home/mateus/Unicamp/MC404/trab01/headers/listaCon.h"
#include "/home/mateus/Unicamp/MC404/trab01/headers/dados.h"

int mapearRotulos(char *nomeArq, NoLstRot *lstRot, NoLstCon *lstCon);

int main (int argc, char *argv[]) {
	
	int codigo = 0;
	NoLstRot *lstRot;
	NoLstCon *lstCon;
	
	lstRot_inicializar(&lstRot);
	lstCon_inicializar(&lstCon);
	inicializarDados();
	codigo = mapearRotulos(argv[1], lstRot, lstCon);
	/*if(argc == 2) {
		codigo = mapearRotulos(argv[1], lstRot);
	}
	else if(argc == 3) {
		codigo = mapearRotulos(argv[1], lstRot);
	}*/
	
	return codigo; 
}
