/* Biblioteca de funcoes para reconhecer tipos de argumentos. */

/* Verifica se um argumento esta errado, ou seja, nao eh nenhum tipo de argumento
 * valido.
 * Retorna 0: nenhum tipo
 *         1: palavra valida
 *         2: decimal valido
 *         3: hexadecimal invalido
 *         4: hexadecimal valido
 */
int isWrong(char *dado);

/* Verifica se eh uma palavra. */
int isWord(char *dado);

/* Verifica se eh um numero decimal. */
int isDec(char *dado);

/* Verifica se eh um numero hexacimal.
 * Retorna 0: nao eh hexadecimal
 *         1: hexadecimal incorreto
 *         2: eh um hexadecimal
 */
int isHex(char *dado);

/* Verifica se eh um numero.
 * Retorna 0: nao eh numero
 *         1: decimal
 *         2: hexadecimal invalido
 *         3: hexadecimal valido
 */
int isNumber(char *dado);
