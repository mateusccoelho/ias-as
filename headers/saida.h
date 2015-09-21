/* Biblioteca de saida de dados. */

/* Imprime o mapa de memoria na saida padrao. */
void imprimirTela(NoLstPal *lstPal);

/* Imprime o mapa de memoria em um arquivo de texto. Retorna -1 se o arquivo
 * nao puder ser criado. */
int imprimirArquivo(NoLstPal *lstPal, char *nomeArq);
