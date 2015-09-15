/* Arquivo que contem todos as constantes necessarias no interpretador e as 
 * inicializa na memoria principal. */

/* Estrutura que modela as instrucoes na linguagem IAS. */
struct Instrucao {
	char mnemonico[6], hex[3];
};
typedef struct Instrucao Instrucao;

/* Variaveis globais com os dados fixos do programa, como instrucoes e diretivas. */
extern Instrucao instrucoes[17];

/* Funcao que inicializa as estruturas anteriores na memoria. */
void inicializarDados();
