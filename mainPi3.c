#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int* vetor_aleatorio(int n){

    srand(time(0));

    int * _vetor = malloc(n * sizeof(int));

    for(int i = 0; i < n; i++){
        _vetor[i] = rand() % n*2 + 1;  
    }

    return _vetor;
}

void troca(int vetor[], int i, int j) {
    int aux = vetor[i];
    vetor[i] = vetor[j];
    vetor[j] = aux;
}

void bubble_sort(int v[], int n) {
    int i;
    int houve_troca;
    do {
        houve_troca = 0;

        for (i = 0; i < n-1; i++) {
            if (v[i] > v[i+1]) {
                troca(v, i, i+1);
                houve_troca = 1;
            }
        }
    } while (houve_troca);
}

void intercala(int v[], int ini, int meio, int fim) {
    int esq, dir; 

    int i; 
    int n = (fim-ini+1); 
    int * novo = malloc(n*sizeof (int));

    i = 0;
    esq = ini;
    dir = meio+1; 
    
    while (esq <= meio && dir <= fim) {
        if (v[esq] < v[dir]) {
            novo[i] = v[esq];
            esq++;
        }
        else {
            novo[i] = v[dir];
            dir++;
        }
        i++;
    }

    while (esq <= meio) novo[i++] = v[esq++];

    while (dir <= fim) novo[i++] = v[dir++];

    for (i = 0; i < n; i++)
        v[ini+i] = novo[i]; 

    free(novo);
}


void merge_sort(int v[], int ini, int fim) {
    int meio;

    if (ini < fim) {
        meio = (ini+fim)/2;       
        merge_sort(v, ini, meio); 
        merge_sort(v, meio+1, fim); 
        intercala(v, ini, meio, fim); 
    }
}

int particiona(int v[], int ini, int fim) {
    int i, j;
    int pivo = v[fim];
    
    i = ini;

    for (j = ini; j < fim; j++) {
        if (v[j] < pivo) {
            troca(v, i, j);
            i++; 
        }
    }
    
    troca(v, i, fim); 
    return i;
}

void quicksort(int v[], int ini, int fim) {
    if ((fim-ini+1) <= 1) return;

    int i = particiona(v, ini, fim);

    quicksort(v, ini, i-1);
    quicksort(v, i+1, fim);
}


void imprime(int v[], int n) {
    int i;
    for (i = 0; i < n; i++) printf("%d ", v[i]);
    printf("\n");
}

int main(void) {

    clock_t inicio, final;
    double tempo, soma_tempo[11], soma_tempo_2[11], soma_tempo_3[11], media_tempo=0;

    int* vetor;
    int i;

    int n[] = {10, 100,
200, 1000, 2000, 10000, 20000, 100000, 200000, 1000000, 2000000};

    for(i=0; i<11; i++){ 
        printf("Teste %d:\n", i+1);
        if(i<7){
            for(int j = 0; j < 10; j++){
                vetor = vetor_aleatorio(n[i]);

                inicio = clock();
                bubble_sort(vetor, n[i]);
                final = clock();

                tempo = ((double) (final-inicio)/CLOCKS_PER_SEC);

                soma_tempo[i] += tempo;
            }
            media_tempo = soma_tempo[i] / 10;

            printf("Bubble Sort - Média de tempo para ordenar %d valores: %f\n", n[i], media_tempo);
        }

        for(int j = 0; j < 10; j++){
                vetor = vetor_aleatorio(n[i]);

                inicio = clock();
                merge_sort(vetor, 0, n[i]-1);
                final = clock();

                tempo = ((double) (final-inicio)/CLOCKS_PER_SEC);

                soma_tempo_2[i] += tempo;
        }
            media_tempo = soma_tempo_2[i] / 10;

            printf("Merge Sort - Média de tempo para ordenar %d valores: %f\n", n[i], media_tempo);

        for(int j = 0; j < 10; j++){
                vetor = vetor_aleatorio(n[i]);

                inicio = clock();
                quicksort(vetor, 0, n[i]-1);
                final = clock();

                tempo = ((double) (final-inicio)/CLOCKS_PER_SEC);

                soma_tempo_3[i] += tempo;
        }
            media_tempo = soma_tempo_3[i] / 10;

            printf("Quick Sort - Média de tempo para ordenar %d valores: %f\n\n", n[i], media_tempo);

    }
    free(vetor);
    return 0;
}