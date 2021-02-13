struct NODE {
    int value;
    struct NODE *left;
    struct NODE *right;
};

typedef struct NODE *BinaryTree;

BinaryTree *r; // ponteiro para ponteiro

/* Observações:
- UM PROVÁVEL ***ERRO*** ESTÁ NA NOMEAÇÃO DA VARIÁVEL DE PARÂMETRO COMO SENDO 'value'
- Todas as funções com retorno 'int' constituem um retorno de teste
*/
BinaryTree *allocatesTree(void); // Aloca árvore dinamicamente
void freeTree(BinaryTree *root); // Libera memória alocada por uma árvore
void freeNode(struct NODE *no); // Libera memória alocada por um único nó
int isEmpty(BinaryTree *root); // Retorna se a árvore está vazia ou não
int treeHeight(BinaryTree *root); // Retorna a altura da árvore 
int altura(BinaryTree raiz); // Função alternativa para calcular altura
int totalTreeNodes(BinaryTree *root); // Retorna a altura da árvore
void preOrder(BinaryTree *root); // Percorre a árvore no formato pré ordem
void inOrder(BinaryTree *root); // Percorre a árvore no formato "ordenado"
void postOrder(BinaryTree *root); // Percorre a árvore no formato pós ordem
int insertTree(BinaryTree *root, int value); // Insere valor do parâmetro na árvore de acordo com as propriedades
int removeTree(BinaryTree *root, int value); // Determina a configuração do nó a ser removido de acordo com o seu grau
struct NODE *removeNode(struct NODE *no); // Determina qual a manipulação a ser executada na árvore para remoção
int searchTree(BinaryTree *root, int value); // Consulta de valor na árvore

// void preOrder(BinaryTree *root) {
    
//     if (root == NULL || *root == NULL) {
//         return;
//     } else {
//         printf("%d\n", (*root)->value);
//         preOrder(&((*root)->left));
//         preOrder(&((*root)->right));
//     }
// } 