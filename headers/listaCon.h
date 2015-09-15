/* Biblioteca de funcoes para gerenciamento de lista duplamente ligada de
 * constantes declaradas pela diretiva .set */

/* Estrutura que representa uma constante na linguagem de maquina. */
struct Constante {
	char *apelido, *real;
};
typedef struct Constante Constante;

/* Estrutura da lista ligada que contem constantes. */
struct NoLstCon {
	Constante *local;
	struct NoLstCon *prox, *ant;
};
typedef struct NoLstCon NoLstCon;

/* Remove uma constante da lista. */
void lstCon_remover(NoLstCon *alvo);

/* Procura o constante com um nome apelido especifico e retorna-o. */
NoLstCon* lstCon_procurar(NoLstCon* lista, char *nome);

/* Insere um novo no aa lista, o que corresponde a uma nova constante.
 * Retorna o endereco do novo elemento. */
NoLstCon* lstCon_inserir(NoLstCon *lista, char *apelidoDado, char *realDado);

/* Inicializa a lista criando um no cabeca. */
void lstCon_inicializar(NoLstCon** lista);

/* Imprime a constante presente em cada no da lista. */
void lstCon_imprimir(NoLstCon *lista);

/* Remove todos os nos da lista. */
void lstCon_removerTudo(NoLstCon* lista);
