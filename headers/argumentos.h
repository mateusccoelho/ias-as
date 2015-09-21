/* Biblioteca de funcoes para reconhecer tipos de argumentos. */

/* Funcoes auxiliares de conversao de tipos */

/* Transforma um numero decimal em hexadecimal dentro de um vetor de
 * caracteres. "tam" indica quantos algarismos o numero deve ter. */
char* decToHex(long int decimal, int tam);

/* Funcoes de verificacao de tipos */

/* Verifica se eh uma palavra. */
int isWord(char *dado);

/* Verifica se eh um numero decimal e se esta dentro do tamanho permitido.*/
int isDec(char *dado, int min, unsigned int max);

/* Verifica se eh um numero hexacimal.
 * Retorna 0: nao eh hexadecimal
 *         -1: hexadecimal incorreto
 *         1: eh um hexadecimal
 */
int isHex(char *dado);

/* Verifica se eh uma diretiva */
int isDiretiva(char* dado);

/* Veridica se eh uma instrucao */
int isInstr(char *dado);

/* Verifica se o dado tem : no final, indicando que eh rotulo. */
int isRotulo(char *dado);

/* Funcoes de verificacao do tipo de um argumento dada alguma restricao. */

/* Verifica se um argumento eh valido dentre as seguintes opcoes: 
 * Codigo 1: Symbol
 * Codigo 2: Hex | Dec
 * Codigo 3: Dec
 * COdigo 4: Hex | Dec | Rot | Symbol*/
int isArg(int codigo, char* dado, int linha, int min, unsigned int max);

/* Verifica se o argumento de uma instrucao eh valido. */
int isInstArg(char* dado, int linha, int min, unsigned int max);
