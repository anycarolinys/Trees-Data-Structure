#include <stdio.h>
#include <stdlib.h>
#include "arvoreBinaria.h"


BinaryTree *allocatesTree(void) {
    BinaryTree *root = (BinaryTree *) malloc(sizeof(BinaryTree));

    if (root != NULL) // memória alocada com sucesso
        *root = NULL;
    
    return root; 
}


void freeNode(struct NODE *no) {

/* O processo de liberar nós só é encerrado
* quando uma folha (nó sem filhos) é encontrada */
    if (no != NULL) {
        // Chamadas recursivas
        freeNode(no->left);
        freeNode(no->right);
        free(no);
        no = NULL;
    }
}

void freeTree(BinaryTree *root) {
    
    if (root != NULL) {
        freeNode(*root); // '*raiz' é o conteúdo do nó raiz
        free(root); 
    }
} 

int isEmpty(BinaryTree *root) {
    // Árvore não foi alocada ou nenhum nó foi adicionado
    if (root == NULL || *root == NULL)
        return 1;
    else
        return 0;
}

int treeHeight(BinaryTree *root) {
    if (root == NULL || *root == NULL) {
        return 0;
    } else {
        // A subárvore maior pode estar à direita ou à esquerda
        int heightLeft, heightRight;
        heightLeft = treeHeight(&((*root)->left));
        heightRight = treeHeight(&((*root)->right));

        if (heightLeft > heightRight)
            return (heightLeft + 1);
        else
            return (heightRight + 1);
    }
}

/* int treeHeight(BinaryTree root) {
    if (root == NULL) {
        return 0;
    } else {
        int heightLeft = treeHeight(root->left);
        int heightRight = treeHeight(root->right);

        if (heightLeft > heightRight)
            return heightLeft;
        else
            return heightRight;
    }
} */



int altura(BinaryTree raiz) {
    if (raiz == NULL) {
        return 0;        
    } else {
        int esq = altura(raiz->left);
        int dir = altura(raiz->right);

        if (esq > dir) 
            return esq + 1;
        else 
            return dir + 1;
    }
}

int totalTreeNodes(BinaryTree *root) {
    
    if (root == NULL || *root == NULL) {
        return 0;
    } else {
        int totalLeft, totalRight;
        totalLeft = totalTreeNodes(&((*root)->left));
        totalRight = totalTreeNodes(&((*root)->right));

        return (totalLeft + totalRight + 1);
    }
}

int depthNode(BinaryTree *root, int value) {
    struct NODE *aux = *root;
    int depth = 0;
    while (aux->value != value) {
        // if (value == aux->value) {
        if (value < aux ->value) {
            aux = aux->left;
            depth++;   
        } else {
            aux = aux->right;
            depth++;   
        }
    }
        return depth;
}

void preOrder(BinaryTree *root) {
    
    int v, level;
    BinaryTree *aux = root;
    if (root == NULL || *root == NULL) {
        return;
    } else {
        printf("%d\n", (*root)->value);
        // v = (*root)->value;
        // level = depthNode(root, v);
        // printf("Nível %d\n", level);
        
        preOrder(&((*root)->left)); 
        preOrder(&((*root)->right));
    }
} 

void inOrder(BinaryTree *root) {
    if (root == NULL || *root == NULL) {
        return;
    } else {
        inOrder(&((*root)->left));
        printf("%d\n", (*root)->value);
        inOrder(&((*root)->right));
    }
}

void postOrder(BinaryTree *root) {  
    if (root == NULL || *root == NULL) {
        return;
    } else {
        postOrder(&((*root)->left));
        postOrder(&((*root)->right));
        printf("%d\n", (*root)->value);
    }
}

int insertTree(BinaryTree *root, int value) {
    
    // Verifiação de árvore válida
    if (root == NULL) {
        return 0;
    } 

    struct NODE *new;
    new = (struct NODE *) malloc(sizeof(struct NODE));
    if (new == NULL)
        return 0;
    new->value = value; // Copiando valor inserido
    new->left = NULL;
    new->right = NULL;
    
    // As condicionais a seguir definem onde o nó será inserido
    if (*root == NULL) {
        *root = new; // Árvore vazia
    } else {
        // Nós auxiliares
        struct NODE *current = *root;
        struct NODE *previous = NULL;
        
        while (current != NULL) {
            previous = current;    
            // Verifica se o elemento já existe na árvore
            // Se sim, não deve ser inserido
            if (value == current->value) {
                free(new);
                return 0;
            }
            
            // Verifica se o valor será adicionado na subárvore
            // esquerda ou direita
            if (value > current->value) 
                current = current->right;
            else
                current = current->left;
        }
        
        // 'previous' guardava o conteúdo do último nó
        // sendo um valor menor que a folha, deve
        // ser inserido à esquerda, caso contrário
        // deve ser inserido à direita
        if (value > previous->value)
            previous->right = new;
        else
            previous->left = new;
    }
    return 1;
}

struct NODE *removeNode(struct NODE *no) {
    struct NODE *n1, *n2;

    // O nó possui filho à esquerda?
    if (no->left == NULL) {
        n2 = no->right; // O nó a ser apontado está à direita
        free(no);
        return n2;
    }
 
   /* Possuindo filho à esquerda deve-se 
   * percorrer a subárvore esquerda até a folha 
   * mais à direita da mesma */
    
    n1 = no;
    n2 = no->left;
    while (n2->right != NULL) {
        n1 = n2; 
        n2 = n2->right;
    }
    
    /* Verifica se houve mais de um avanço
    * até o nó mais à direita, se houve,
    * os valores devem ser trocados */
    if (n1 != no) {
        n1->right = n2->left; // n2->left e n2->right até aqui apontam para NULL
        n2->left = no->left;
    }

    n2->right = no->right;
    free(no);
    return n2;
}


int removeTree(BinaryTree *root, int value) {
    
    if (root == NULL || *root == NULL) // Árvore inválida ou vazia
        return 0;
    
    struct NODE *previous = NULL;
    struct NODE *current = *root;

    previous = current;

    while (current != NULL) {

    /* Este bloco trata da posição do nó a ser removido
    * - Nó é a raiz
    * - Nó está à direita/esquerda
    * */
        if (value == current->value) {
            if (current == *root) {
                *root = removeNode(current); // Remoção da raiz
            } else {
                if (previous->right == current)
                    previous->right = removeNode(current);
                else 
                    previous->left = removeNode(current);
            }    
            return 1; // A remoção ocorreu sob alguma condição
        /* Observações:
        * 'previous->left' e 'previous->right':
        * recebem o novo nó a ser apontado após a
        * remoção do nó 'current' antigo
        * */
        }
    
        previous = current;
    /* Este bloco percorre a árvore à procura do 
    * nó a ser removido */
        if (value > current->value) 
            current = current->right;
        else
            current = current->left;
    }
    return 0;
}

/* int searchTree(BinaryTree *root, int value) {

int test;
if (root == NULL || *root == NULL) {
    return 0;
}

if (value == (*root)->value) {
    return 1;
} else if (value <= (*root)->value) {
    test = searchTree((*root)->left, value);
    return 1;
} else {
    searchTree((*root)->right, value);
    return 1;
}
return 0;
} */


int searchTree(BinaryTree *root, int value) {
    if (root == NULL || *root == NULL)
        return 0;

    struct NODE *aux = *root;

    while (aux != NULL) {
        if (value == aux->value)
            return 1;
        if (value < aux->value)
            aux = aux->left;
        else
            aux = aux->right;   
    }
    return 0;
}


int menu(void) {
    int opcao;
    printf("\nÁRVORE BINÁRIA DE BUSCA\n");
    printf("0. ENCERRAR PROGRAMA\n");
    printf("1. INSERIR NÓ\n");
    printf("2. REMOVER NÓ\n");
    printf("3. CONSULTAR VALOR\n");
    printf("4. IMPRIMIR ÁRVORE\n");
    printf("5. PROFUNDIDADE DE NÓ\n");
    printf("OPÇÃO: ");
    scanf("%1d", &opcao);
    return opcao;
    // getchar();
}

void opcao(BinaryTree *root, int opcao) {
    
    int try,v;
    switch (opcao) {
    case 0:
        break;
    case 1:
        printf("Valor = ");
        scanf("%d", &v);
        try = insertTree(root, v);
        if (try == 1)
            printf("Nó inserido!\n");
        else
            printf("Falha ao inserir nó!");
        break;
    case 2:
        printf("Valor = ");
        scanf("%d", &v);
        try = removeTree(root, v);
        if (try == 1)
            printf("Nó removido!\n");
        else
            printf("Falha ao remover nó!");
        break;
    case 3:
        printf("Valor = ");
        scanf("%d", &v);
        try = searchTree(root, v);
        if (try == 1)
            printf("Valor encontrado!\n");
        else
            printf("Valor não encontrado!");
        break;
    case 4:
        preOrder(root);
        // if (try == 0)
        //     printf("Árvore vazia!\n");
        break;
    case 5:
        printf("Valor = ");
        scanf("%d", &v);
        try = depthNode(root, v);
        printf("Nível %d\n", try);
        break;
    default:
        break;
    }
}

int main(void) {
    
    int op;
    
    BinaryTree *root = allocatesTree();
    do {
        op = menu();
        opcao(root, op);
    } while (op);
    
    freeTree(root);
    return 0;
}