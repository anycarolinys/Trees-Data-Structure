#include <stdio.h>
#include <stdlib.h>
#include "arvoreAVL.h"

int nodeHeight(struct NODE *no) {
    if (no == NULL)
        return -1;
    else
        return no->h;
}

int balFactor(struct NODE *no) {
    return abs(nodeHeight(no->left) - nodeHeight(no->right)); // 'labs' returns the absolute value of the subtraction
}

int bigger(int x, int y) {
    if (x > y)
        return x;
    else
        return y;
}

// Rotação simples à direita
int rotationLL(AVLTree *root) {
    struct NODE *aux;
    
    /* Nó auxiliar é o filho à esquerda da raiz */
    aux = (*root)->left;        
    /* A raiz aponta para o nó que antes estava à direita do nó à sua esquerda*/
    (*root)->left = aux->right; 
    /* A raiz torna-se filha à direita do nó que antes estava à sua esquerda*/
    aux->right = *root;

    /* A altura da raiz é o maior valor entre as alturas das suas subárvores*/
    (*root)->h = bigger((*root)->left->h, (*root)->right->h) + 1;

    /* O nó que estava à esquerda da raiz passa a ser a raiz */
    *root = aux;
}

// Rotação simples à esquerda
int rotationRR(AVLTree *root) {
    struct NODE *aux;

    /* Nó auxiliar é o filho à direita da raiz */
    aux = (*root)->right;

    /*A raiz aponta para o valor que antes estava à esquerda do valor à sua direita*/
    (*root)->right = aux->left;

    /* A raiz torna-se filha à esquerda do nó que antes estava à sua direita */
    aux->left = *root;

    /* A altura da raiz é o maior valor entre as alturas das suas subárvores*/ 
    (*root)->h = bigger((*root)->left->h, (*root)->right->h);

    /* O nó que estava à direita da raiz passa a ser a raiz*/
    *root = aux;

}

// Rotação dupla à direita
void rotationLR(AVLTree *root) {
    int r;
    /* Rotação à esquerda para o nó à esquerda da raiz*/
    r = rotationRR(&(*root)->left);
    /* Rotação à direita na raiz da árvore*/
    r = rotationLL(root); 
}

// Rotação dupla à esquerda
void rotationRL(AVLTree *root) {
    int r;
    /* Rotação simples à direita para o nó à direita da raiz */
    r = rotationLL(&(*root)->right);
    /* Rotação à esquerda na raiz da árvore */
    r = rotationRR(root);
}

int insertAVL(AVLTree *root, int k) {
    
    int r; // Variável que recebe o retorno das funções de inserção
    
    /* Árvore vazia ou chegou-se ao nó folha*/
    if (*root == NULL) {
        struct NODE *new;
        new = (struct NODE *) malloc(sizeof(struct NODE));
        
        if (new == NULL) // Alocação inválida
            return 0;
        
        new->key = k;       // Copiar valor da chave
        new->h = 0;         // Zerar altura
        new->left = NULL;   // Subárvore à esquerda indefinida
        new->right = NULL;  // Subárvore à direita indefinida
        *root = new;        // Raiz aponta para novo nó
        return 1;           // Inserção realizada com sucesso
    }

    /* A árvore não é vazia nem se chegou a um nó folha*/
    struct NODE *aux = *root;
    /* O valor a ser inserido é menor que o valor atual */
    if (k < aux->key) {
        /* Inserção à esquerda */
        if ((r = insertAVL(&(aux->left), k)) == 1) { // RECURSIVIDADE
            /* Caso a inserção tenha causado desbalanceamento, é necessário balancear*/ 
            if (balFactor(aux) >= 2) {
                if (k < (*root)->left->key)
                    rotationLL(root);       // Rotação à direita
                else
                    rotationLR(root);       // Rotação dupla à direita
            }
        }
    } else { /* O valor a ser inserido é maior que o valor atual */
        if (k > aux->key) {
            /* Inserção à direita */
            if ((r = insertAVL(&(aux->right), k) == 1)) { // RECURSIVIDADE
                /* Caso a inserção tenha causado desbalanceamento, é necessário balancear*/ 
                if (balFactor(aux) >= 2) {
                    if ((*root)->right->key < k) 
                        rotationRR(root);
                    else
                        rotationRL(root);
                }
            }
        } else {
            printf("Valor duplicado!\n");
            return 0;
        }
    }

    aux->h = bigger(aux->left->h, aux->right->h) + 1;
    return r; //Retorna valor da última inserção realizada
}

/* Função responsável por tratar a remoção de um nó com 2 filhos */
/* Retorna o nó mais à esquerda da subárvore à direita */
/* struct NODE *searchLowest(struct NODE *no) {
    struct NODE *r = (struct NODE *) malloc(sizeof(struct NODE));

    while (r->left != NULL) {
        r = searchLowest(no->left);
    }
    
    return r;
} */

struct NODE *searchLowest(struct NODE *no) {
    struct NODE *node1 = no, *node2 = no->left;

    while (node2 != NULL) {
        node1 = node2;
        node2 = node2->left;
    }

    return node1;
}

/* Função responsável pela busca do nó a ser removido */
int removeAVL(AVLTree *root, int k) {

    int r; // Variável que recebe o retorno das funções de inserção
    
    if (*root == NULL) // Árvore vazia
        return 0;
    
    /* Nó a ser removido está na subárvore esquerda*/  
    if (k < (*root)->key) {
        /* Recursão para encontrar a posição (subárvore esquerda) do nó a ser removido */
        if ((r = removeAVL(&((*root)->left), k)) == 1) {
            /* Após remover verificar se houve desbalanceamento */
            if (balFactor(*root) >= 2) {
                /* Remover nó à esquerda, gera desbalanceamento à direita */
                /* Se a altura da subárvore à esquerda do lado direito for menor*/
                if (nodeHeight((*root)->right->left) <= nodeHeight((*root)->right->right))
                    rotationRR(root); // Rotação simples à esquerda 
                else
                    rotationRL(root); // Rotação dupla à esquerda
            }
        }
    } else { /* Nó a ser removido está na subárvore direita */
        if (k > (*root)->key) {
            /* Recursão para encontrar a posição (subárvore direita) do nó a ser removido */
            if ((r = removeAVL(&((*root)->right), k)) == 1) {
                /* Após remover verificar se houve desbalanceamento */
                if (balFactor(*root) >= 2) {
                    /* Remover nó à esquerda, gera desbalanceamento à direita */
                    if (nodeHeight((*root)->left->right) <= nodeHeight((*root)->left->left))
                        rotationLL(root); //Rotação simples à direita
                     else
                        rotationLR(root); // Rotação dupla à esquerda
                }
            } 
        }
    }
    
    /* Se a chave não é maior nem menor que o valor da raiz, a raiz é o nó a ser removido */
    if ((*root)->key == k) {
        /* Verificar se a raiz possui filho à esquerda/direita */
        if ((*root)->left == NULL || (*root)->right == NULL) {
            struct NODE *oldNode = *root; // Copiando conteúdo da raiz em nó "auxiliar"
            
            if ((*root)->left != NULL) // Raiz possui filho à esquerda
                *root = (*root)->left; // A raiz passa a ser o nó à sua esquerda
            else                        // Raiz possui filho à direita
                *root = (*root)->right; // A raiz passa a ser o nó à sua direita
            free(oldNode);              // Limpar memória do nó da antiga raiz
        } else {                        // Raiz possui dois filhos (esquerda e direita) 
            /* Procurar o nó mais à esquerda (FOLHA) da subárvore à direita */
            struct NODE *temp = searchLowest((*root)->right); 
            /* Copiando a chave da nova raiz */
            (*root)->key = temp->key;                       
            /* Removendo da subárvore direita o seu nó mais à esquerda, o qual agora é a raiz */
            removeAVL(&(*root)->right, (*root)->key) ;
            /* Verificar se essa remoção gerou desbalanceamento na subárvore à esquerda (remoção à direita) */
            if (balFactor(*root) >= 2) {
                if (nodeHeight((*root)->left->right) < nodeHeight((*root)->left->left))
                    rotationLL(root); // Rotação simples à direita
                else
                    rotationLR(root); // Rotação dupla à direita
            }
        }
        return 1;
    }
    return r;
}

int main(void) {

    return 0;

}