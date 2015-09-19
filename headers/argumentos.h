/* Biblioteca de funcoes para reconhecer tipos de argumentos. */

/* Verifica se eh uma palavra. */
int isWord(char *dado);

/* Verifica se eh um numero decimal. */
int isDec(char *dado, int min, unsigned int max);

/* Verifica se eh um numero hexacimal.
 * Retorna 0: nao eh hexadecimal
 *         -1: hexadecimal incorreto
 *         1: eh um hexadecimal
 */
int isHex(char *dado);

/* Verifica se eh uma diretiva */
int isDiretiva(char* dado);

/* Verifica se um argumento eh valido. 
 * Codigo 1: Symbol
 * Codigo 2: Hex | Dec
 * Codigo 3: Dec
 * COdigo 4: Hex | Dec | Rot | Symbol*/
int isArg(int codigo, char* dado, int linha, int min, unsigned int max);

/* Verifica se o argumento de uma instrucao eh valido. */
int isInstArg(char* dado, int linha, int min, unsigned int max);

char* decToHex(long int decimal);
