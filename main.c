#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "/home/mateus/Unicamp/MC404/trab01/headers/listaRot.h"
#include "/home/mateus/Unicamp/MC404/trab01/headers/listaPal.h"
#include "/home/mateus/Unicamp/MC404/trab01/headers/dados.h"
#include "/home/mateus/Unicamp/MC404/trab01/headers/saida.h"
#include "/home/mateus/Unicamp/MC404/trab01/headers/metodos.h"

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
			lstPal_ordenar(lstPal);
			if(argc == 2)
				imprimirTela(lstPal);
			else if(argc == 3)
				codigo = imprimirArquivo(lstPal, argv[2]);
		}
	}
		
	lstPal_removerTudo(lstPal);
	
	return codigo; 
}
