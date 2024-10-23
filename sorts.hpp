#include <stdio.h>
#include <iostream>
#include <vector>
#include <chrono>
#include <cstdlib>
#include <numeric>
#include <random>
#include <algorithm>
#include <mutex>
#include <thread>
using namespace std;

#define RED "\033[31m"
#define GREEN "\033[32m"
#define RESET "\033[0m"

mutex mtx;

void printVectorDivide(const vector<int>& v, int comeco, int fim) {
    cout << "[ ";
    for (int i = comeco; i <= fim; i++) {
        if(i == (fim+comeco)/2+1) cout << RED << "/ " << RESET;
        cout << v[i] << " ";
    }
    cout << "]" << endl;
}

void printVectorMerge(const vector<int>& v, int comeco, int fim) {
    cout << GREEN << "+ Merge: " << RESET;
    cout << "[ ";
    for (int i = comeco; i <= fim; i++) {
        cout << v[i] << " ";
    }
    cout << "]" << endl;
}


void swap(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

int partition(vector<int>& v, int low, int high) {
    int mid = low + (high - low) / 2;
    swap(v[mid], v[high]);

    int pivot = v[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (v[j] <= pivot) {
            i++;
            swap(v[i], v[j]);
        }
    }
    
    swap(v[i + 1], v[high]);
    return i + 1;
}

void quickSort(vector<int>& v, int low, int high) {
    if (low < high) {
        int p = partition(v, low, high);
        quickSort(v, low, p - 1);
        quickSort(v, p + 1, high);
    }
}

void merge(vector<int>& v, int low, int mid, int high, vector<int>& left, vector<int>& right) { // Conquista
    
    int n1 = mid - low + 1; // n de elementos no subarray esquerdo 

    int n2 = high - mid; // n de elementos no subarray direito

    for (int i = 0; i < n1; i++) {
        left[i] = v[low + i]; // Copia os elementos do subarray esquerdo para o array auxiliar
    }
    
    
    for (int i = 0; i < n2; i++) {
        right[i] = v[mid + 1 + i]; // Copia os elementos do subarray direito para o array auxiliar
    }

    int i = 0, j = 0, k = low;

    // Compara os elementos de left e right, e os coloca de volta em v em ordem
    while (i < n1 && j < n2) {
        if (left[i] <= right[j]) {
            v[k] = left[i]; // Se o elemento do lado esquerdo for menor ou igual
            i++;
        } else {
            v[k] = right[j]; // Caso contrário, o elemento do lado direito é inserido
            j++;
        }
        k++;
    }

    // Se ainda restarem elementos no subarray left
    while (i < n1) {
        v[k] = left[i];
        i++;
        k++;
    }

    // Se ainda restarem elementos no subarray right
    while (j < n2) {
        v[k] = right[j];
        j++;
        k++;
    }
}

void mergeSortIdk(vector<int>& v, int low, int high, vector<int>& left, vector<int>& right) { // Divisao
    if (low < high) {
        
        int mid = low + (high - low) / 2; // Encontra o meio do array
        
        mergeSortIdk(v, low, mid, left, right); // Recursivamente ordena o subarray esquerdo (de low a mid)

        mergeSortIdk(v, mid + 1, high, left, right); // Recursivamente ordena o subarray direito (da posição mid + 1 a high)
        
        merge(v, low, mid, high, left, right);  // Junta os dois subarrays ordenados
    }
}

void mergeSort(vector<int>& v, int low, int high) {
    int n = v.size();
    
    // Arrays auxiliares para armazenar temporariamente os subarrays e diminuir o tempo gasto com alocação de espaço
    vector<int> left(n / 2 + 1), right(n / 2 + 1);
    
    mergeSortIdk(v, low, high, left, right); // Chama a função recursiva de ordenação
}

void parallelMergeSort(vector<int>& v, int low, int high, int numThreads) {
    if (numThreads <= 1) {
        mergeSort(v, low, high);
        return;
    }
    
    int n = v.size();
    vector<int> left(n / 2 + 1), right(n / 2 + 1);
    int mid = low + (high - low) / 2;

    thread leftThread(mergeSortIdk, ref(v), low, mid, ref(left), ref(right));
    thread rightThread(mergeSortIdk, ref(v), mid + 1, high, ref(left), ref(right));

    leftThread.join();
    rightThread.join();

    merge(v, low, mid, high, left, right);
}

void iterativeMergeSort(vector<int>& v) {
    int n = v.size();
    
    for (int curr_size = 1; curr_size <= n - 1; curr_size *= 2) {
        for (int low = 0; low < n - 1; low += 2 * curr_size) {
            
            int mid = min(low + curr_size - 1, n - 1);
            int high = min(low + 2 * curr_size - 1, n - 1);

            vector<int> left(mid - low + 1);
            vector<int> right(high - mid);


            merge(v, low, mid, high, left, right);
        }
    }
}

void shellSort(vector<int>& v, int low, int high) {
    int n = high - low + 1;

    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = low + gap; i <= high; i++) {
            int temp = v[i];
            int j;
            for (j = i; j >= low + gap && v[j - gap] > temp; j -= gap) {
                v[j] = v[j - gap];
            }
            v[j] = temp;
        }
    }
}

void beadSort(int *a, int len)
{
	int i, j, max, sum;
	unsigned char *beads;
       #define BEAD(i, j) beads[i * max + j]
 
	for (i = 1, max = a[0]; i < len; i++)
		if (a[i] > max) max = a[i];
 
	beads = (unsigned char*)calloc(1, max * len);
 
	for (i = 0; i < len; i++)
		for (j = 0; j < a[i]; j++)
			BEAD(i, j) = 1;
 
	for (j = 0; j < max; j++) {
		for (sum = i = 0; i < len; i++) {
			sum += BEAD(i, j);
			BEAD(i, j) = 0;
		}
		for (i = len - sum; i < len; i++) BEAD(i, j) = 1;
	}
 
	for (i = 0; i < len; i++) {
		for (j = 0; j < max && BEAD(i, j); j++);
		a[i] = j;
	}
	free(beads);
}