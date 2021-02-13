#include <stdio.h>
#include <stdlib.h>

void troca(int a, int b) {
    int aux = a;
    a = b;
    b = aux;
}

/* 
* Função que rearranja um vetor vet[1..n] de 
* modo a transformá-lo em heap. Isto é, um vetor
* em que v[f/2] >= v[f].
*/
void constroiHeap(int n, int vet[]) {
    
    int i;
    for (i = 1; i < n; ++i) {
        // v [1..k] é um heap
        int f = i + 1;
        while (f > 1 && vet[f/2] < vet[f]) {
            troca(vet[f/2], vet[f]);
            f /= 2;
        }
    }
}

/* 
* Recebe um vetor vet[1..n] que é um heap
* exceto talvez por um ou dois índices e rearranja
* o vetor de modo a transformá-lo em heap.
*/

// void peneira(int n, int vet[]) {

//     int p = 1, f = 2, x = vet[1]; 
//     // vet[1] é o segundo valor no vetor

//     while (f <= n) {
//         if (f < n && (vet[f] < vet[f+1]))
//             ++f;
//         if (x >= vet[f])
//             break;
//         vet[p] = vet[f];
//         p = f;
//         f = p * 2;
//     }
//     vet[p] = x;
// }

void peneira(int n, int vet[]) {
    int f = 2;
    while (f <= n) {
        if (f < n && (vet[f] < vet[f+1]))
            ++f;
        if (vet[f/2] >= vet[f])
            break;
        troca(vet[f/2], vet[f]);
        f *= 2;
    }   
}


/* 
* Função que transforma o vetor em heap
* e, em seguida, rearranja o heap em ordem 
* crescente.
*/
void heapSort(int n, int vet[]) {

    constroiHeap(n, vet);
    for (int m = n; m >= 2; --m) {
        troca(vet[1], vet[m]);
        peneira(m - 1, vet);
    }
    
}
 
int main(void) {
    
    int i;
    int vetor[5] = {1, 5, 7, 0, 3};

    heapSort(5, vetor);

    for (i = 0; i < 5; i++) {
        printf("%d ", vetor[i]);
    }
    
    return 0;
}