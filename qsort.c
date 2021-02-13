/* 
* Protótipo da função qsort:
* void qsort(void *base, size_t num, size_t size,* int (*compar) (const void*, const void*));
* Parâmetros:
* "base": endereço do array a ser ordenado
* "num": tamanho do array
* "size": tamanho, em bytes, de cada posição do 
* array
* "compar": ponteiro para a função de comparação
* 
*/

#include <stdio.h>
#include <stdlib.h>

int compar(const void *p1, const void *p2) {

    if (*(int *)p1 == *(int *)p2)
        return 0;
    else if (*(int *)p1 < *(int *)p2)
        return -1;
    else
        return 1;
}

int main(void) {

    int i, vet[8] = {9, 3, 4, 1, 2, 7, 3, 9};

    qsort(vet, 8, sizeof(int), compar);

    for (i = 0; i < 8; i++) {
        printf("%d ", vet[i]);
    }
    
    return 0;
}