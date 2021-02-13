#include <stdio.h>
#include <stdlib.h>

void criaHeap(int vet[], int ini, int fim) {
    int aux = vet[ini];
    // Condição para ser um heap
    int j = ini * 2 + 1; 

    while (j <= fim) {
        
        if (j < fim) {
            if (vet[j] < vet[j+1])
                j++;
        }

        if (aux < vet[j]) {
            vet[ini] = vet[j];
            ini = j;
            j = ini * 2 + 1;
        } else {
            j = fim + 1;
        }

        vet[ini] = aux;
    }
} 

void heapSort(int vet[], int n) {
    int i, aux;
    
    for (i = (n - 1)/2; i >= 0; i--)
        criaHeap(vet, i, n-1);
    
    for (i = n - 1; i >= 1; i--) {
        aux = vet[0];
        vet[0] = vet[i];
        vet[i] = aux;
        criaHeap(vet, 0, i - 1);
    }
}

int main(void) {
        int i;
    int vetor[5] = {1, 5, 7, 0, 3};

    heapSort(vetor, 5);

    for (i = 0; i < 5; i++) {
        printf("%d ", vetor[i]);
    }
    return 0;
}