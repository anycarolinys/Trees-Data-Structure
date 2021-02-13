struct NODE {
    int key, h; // h de 'height'
    struct NODE *left, *right;
};

typedef struct NODE *AVLTree;

AVLTree *r; // 'r' de root 
int nodeHeight(struct NODE *no); // Retorna a altura do nó passado como parâmetro
int balFactor(struct NODE *no); // Retorna o fator de balanceamento do nó, considerando a altura das subárvores do nó em questão
int bigger(int x, int y); // Compara dois inteiros