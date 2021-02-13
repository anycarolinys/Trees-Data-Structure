#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int key;
    int bal; // balancing
    struct node *left, *right; // pointers to left and rights 
} no;

int insertAVL(int k, no **p) {
    int grownUp;
    
    if (*p == NULL) { // Empty tree
        
        *p = (no *) malloc(sizeof(no));
        (*p)->key = k; 
        (*p)->right = (*p)->left = NULL; // Double attribution
        (*p)->bal = 0;
        grownUp = 1;

    } else if ((*p)->key > k) {
        grownUp = insertAVL(k, &(*p)->left);
        if (grownUp) {
            switch ((*p)->bal) {
            case 1:
                (*p)->bal = 0;
                grownUp = 0;
                break;
            case 0:
                (*p)->bal = -1;
                grownUp = 1;
                break;
            case -1:
                if ((*p)->left->bal == -1) {
                    // rot_right(p);
                    (*p)->bal = (*p)->right->bal = 0;
                } else {
                    // rot_left(&(*p)->left);
                    // rot_right(p);

                    if ((*p)->bal == -1) {
                        (*p)->left->bal = 0;
                        (*p)->right->bal = 1;
                    } else {
                        (*p)->right->bal =  0;
                        (*p)->left->bal = -(*p)->bal; // (-1) * (*p)->bal;
                    }
                grownUp = 0;
                }
            }
        }
    } else if((*p)->key < k) {
        grownUp = insertAVL(k, &(*p)->right);
        if (grownUp) {
            switch ((*p)->bal) {
            case -1:
                (*p)->bal = 0;
                grownUp = 0;
                break;
            case 0:
                (*p)->bal = 1;
                grownUp = 1;
                break;
            case 1:
                if ((*p)->right->bal == 1) {
                    // rot_left(p);
                    (*p)->bal = (*p)->left->bal = 0;
                } else {
                    // rot_right(&(*p)->right);
                    // rot_left(p);

                    if ((*p)->bal == -1) {
                        (*p)->left->bal = 0;
                        (*p)->right->bal = 1;
                    } else {
                        (*p)->right->bal = 0;
                        (*p)->left->bal = -(*p)->bal;
                    }
                    (*p)->bal = 0;
                }
                grownUp = 0;
            }
        }
    } else {
        grownUp = 0;
    }
    return grownUp;
}