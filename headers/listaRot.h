/* Biblioteca de funcoes para gerenciamento de lista duplamente ligada. */

/* Estrutura que representa um rotulo na linguagem de maquina. */
struct Rotulo {
	char *nome;
	int palavra;
	int lado;
};
typedef struct Rotulo Rotulo;

/* Estrutura da lista ligada que contem rotulos. */
struct NoLstRot {
	Rotulo *local;
	struct NoLstRot *prox, *ant;
};
typedef struct NoLstRot NoLstRot;

/* Remove um rotulo da lista. */
void lstRot_remover(NoLstRot *alvo);

/* Procura o rotulo com um nome especifico e retorna-o. */
NoLstRot* lstRot_procurar(NoLstRot* lista, char *nome);

/* Insere um novo no aa lista, o que corresponde a um novo rotulo.
 * Retorna o endereco do novo elemento. */
NoLstRot* lstRot_inserir(NoLstRot *lista, char *nomeDado, int pal, int lad);

/* Inicializa a lista criando um no cabeca. */
void lstRot_inicializar(NoLstRot** lista);

/* Imprime o rotulo presente em cada no da lista. */
void lstRot_imprimir(NoLstRot *lista);

/* Remove todos os nos da lista. */
void lstRot_removerTudo(NoLstRot* lista);
