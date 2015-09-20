/* Biblioteca de funcoes para gerenciamento de lista duplamente ligada. */

/* Estrutura que representa uma palavra de memoria na linguagem de maquina. */
struct Palavra {
	int palavra;
	char *conteudo;
};
typedef struct Palavra Palavra;

/* Estrutura da lista ligada que contem palavras de memoria. */
struct NoLstPal {
	Palavra *local;
	struct NoLstPal *prox, *ant;
};
typedef struct NoLstPal NoLstPal;

/* Remove uma palavra da lista. */
void lstPal_remover(NoLstPal *alvo);

/* Procura uma palavra especifica e retorna-a. */
NoLstPal* lstPal_procurar(NoLstPal* lista, int key);

/* Insere um novo no aa lista, o que corresponde a uma nova palavra.
 * Retorna o endereco do novo elemento. */
NoLstPal* lstPal_inserir(NoLstPal *lista, int numPal, char *cont);

/* Inicializa a lista criando um no cabeca. */
void lstPal_inicializar(NoLstPal** lista);

/* Imprime a palavra presente em cada no da lista. */
void lstPal_imprimir(NoLstPal *lista);

/* Remove todos os nos da lista. */
void lstPal_removerTudo(NoLstPal* lista);

/* Ordena as palavras pelo seu ID. */
void lstPal_ordenar(NoLstPal *lista);
