/* Biblioteca de funcoes que fazer o grosso do montador, ou seja, ler e
 * interpretar cada palavra e gerar o mapa de memoria.  */

/* Importante: todas as funcoes abaixo retornam 0 ou -1. */

/* Faz a leitura do programa armazenando rotulos e tratando 90% dos possiveis
 * erros que o usuario pode cometer. */ 
int mapearRotulos(char *nomeArq, NoLstRot *lstRot);

/* Auxiliar a mapearRotulos: busca erros na disposicao dos rotulos, diretivas ou
 * instrucoes em uma linha do arquivo de entrada. */
int verificarLinha(int *tipos, char* ordem, int linha, int ordemNum);

/* Percorre o arquivo de entrada montando o mapa de memoria em uma lista ligada.
 * Tambem trata outros 5% dos possiveis erros do usuario. */
int gerarMapa(char *nomeArq, NoLstRot *lstRot, NoLstPal *lstPal);
