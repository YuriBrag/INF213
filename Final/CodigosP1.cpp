#include <algorithm>
#include <iostream>
#include <chrono>
#include <iomanip>
#include <cmath>
#include <vector>
#include <string>

//buscaBin
int buscaBin(const int *v, const int beg, const int end, const int key) {
    if (beg > end) {
        return -1;
    }
    int meio = (end - beg)/2 + beg;

    if (v[meio] == key) {
        return meio;
    }
    
    if (v[meio] < key) {
        return buscaBin(v, meio + 1, end, key);
    }
    else {
        return buscaBin(v, beg, meio - 1, key);
    }
}

int buscaBin(const int *v, const int key, const int n) {
    //n eh o tamanho do array
    return buscaBin(v, 0, n - 1, key);
}


//-----Ordenacao-----

//bubbleSort

void bubbleSort(int *v, const int n) {
    int end = n - 1;
    for (int i = 0; i < end; i++) {
        for (int j = 0; j < end - i; i++) {
            if (v[j] > v[j+1]) {
                std::swap(v[j], v[j+1]);
                // int aux = v[j];
                // v[j] = v[j+1];
                // v[j+1] = aux;
            }
        }
    }
}

//selectionSort

void selectionSort(int *v, const int n) {
    for (int i = 0; i < n - 1; i++) {
        int posMenor = i;
        for (int j = 0; j < n - 1; j++) {
            if (v[i] > v[j]) {
                posMenor = j;
            }
        }
        std::swap(v[i], v[posMenor]);
    } 
}

//insertionSort

void insertionSort(int *v, const int n) {
    for (int i = 1; i < n; i++) {
        int elemInserir = v[i];
        int j = i - 1;
        while (j >= 0 && elemInserir < v[j]) {
            v[j + 1] = v[j];
            j--;
        }
        v[j + 1] = elemInserir;
    }
}

//mergeSort

void merge(int *v, int p, int q, int r) {
    int tam = r - p;
    int *aux = new int[tam];
    int i = p;
    int j = q;
    int k = 0;
    while (i < q && j < r) {
        if (v[i] < v[j]) {
            aux[k++] = v[i++];
        }
        else {
            aux[k++] = v[j++];
        }
    }
    while (i < q) {
        aux[k++] = v[i++];
    }
    while (j < r) {
        aux[k++] = v[j++];
    }
    for (k = 0; k < tam; k++) {
        v[p + k] = aux[k];
    }
    delete [] aux;
}

void mergeSort(int *v, const int p, const int r) {
    if (r - 1 > p) {
        int meio = (r - p)/2;
        mergeSort(v, p, meio);
        mergeSort(v, meio, r);
        merge(v, p, meio, r);
    }
}

void mergeSort(int *v, const int n) {
    mergeSort(v, 0, n);
}

//quickSort

int particiona(int *v, int beg, int end, int pivo) {
    int valorPivo = v[pivo];
    std::swap(v[pivo], v[end-1]);
    int pos = beg;
    for (int i = beg; i < end - 1; i++) {
        if (v[i] < v[pivo]) {
            std::swap(v[pos], v[i]);
            pos++;
        }
    }
    std::swap(v[pos], v[end-1]);
    return pos;
}

void quickSort2(int *v, int beg, int end) {
    if (end == beg) {
        return;
    }
    int pos = particiona(v, beg, end, beg);
    quickSort2(v, beg, pos);
    quickSort2(v, pos + 1, end);
}

void quickSort(int *v, const int n) {
    quickSort2(v, 0, n);
}

//shellSort

void shellSort(int *v, int n) {
    int h = 1;
    while (h < n) h = 3 * h + 1;
    do {
        h = h / 3;
        for (int i = h; i < n; i++) {
            int elemInserir = v[i];
            int j = i-h;
            while(j >= 0 && v[j] > elemInserir) {
                v[j+h] = v[j];
                j -= h;
            }
            v[j+h] = elemInserir;
        }       
    } while (h > 1);
}

//countingSort

/* Supomos que todos elementos de v estão no intervalo [0,k)*/
void countingSort(int *v, int n, int k) {
    int *numMenorIg = new int[k];
    int *temp = new int[n];
    for(int i=0;i<k;i++){   
        numMenorIg[i] = 0;
    }
    for(int i=0;i<n;i++){   
        numMenorIg[v[i]]++;
    }
    //Agora, numMenorIg[i] contem a quantidade do elemento i na entrada... 
    //precisamos saber, entao, quantos elementos sao menores ou iguais a i..
    int ct = 0;
    for(int i = 1; i < k; i++){  
        numMenorIg[i] = numMenorIg[i] + numMenorIg[i-1]; 
    }   
    for(int i = n-1; i >= 0; i--) {
        //Para cada elemento A do arranjo,grave o elemento A na posicao
        //numMenores[A] de temp
        temp[numMenorIg[v[i]]-1] = v[i];
        numMenorIg[v[i]]--;
    }   
    for(int i = 0; i < n; i++)
        v[i] = temp[i]; //Copiamos o arranjo temporario de volta para v...
    delete []numMenorIg;
    delete []temp;  
}