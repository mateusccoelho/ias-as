/* Biblioteca de funcoes para gerenciamento de lista duplamente ligada. */

/* Estrutura que representa uma palavra de memoria na linguagem de maquina. */
struct Palavra {
	int palavra;
	char *cod1, *end1, *cod2, *end2;
};
typedef struct Palavra Palavra;

/* Estrutura da lista ligada que contem rotulos. */
struct NoLstPal {
	Palavra *local;
	struct NoLstRot *prox, *ant;
};
typedef struct NoLstPal NoLstPal;

/* Remove um rotulo da lista. */
void lstPal_remover(NoLstPal *alvo);

/* Procura o rotulo com um nome especifico e retorna-o. */
NoLstPal* lstPal_procurar(NoLstPal* lista, char *nome);

/* Insere um novo no aa lista, o que corresponde a um novo rotulo.
 * Retorna o endereco do novo elemento. */
NoLstPal* lstPal_inserir(NoLstPal *lista, char *nomeDado, int pal, int lad);

/* Inicializa a lista criando um no cabeca. */
void lstPal_inicializar(NoLstPal** lista);

/* Imprime o rotulo presente em cada no da lista. */
void lstPal_imprimir(NoLstPal *lista);

/* Remove todos os nos da lista. */
void lstPal_removerTudo(NoLstPal* lista);
