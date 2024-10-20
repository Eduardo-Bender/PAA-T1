#include <stdio.h>
#include <iostream>
#include <vector>
#include <chrono>
#include <cstdlib>
#include <numeric>
using namespace std;

#define RED "\033[31m"
#define GREEN "\033[32m"
#define RESET "\033[0m"

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

void merge(vector<int>& v, int low, int mid, int high) {
    int n1 = mid - low + 1;
    int n2 = high - mid;

    vector<int> left(n1), right(n2);

    for (int i = 0; i < n1; i++) {
        left[i] = v[low + i];
    }
    for (int i = 0; i < n2; i++) {
        right[i] = v[mid + 1 + i];
    }

    int i = 0, j = 0, k = low;
    while (i < n1 && j < n2) {
        if (left[i] <= right[j]) {
            v[k] = left[i];
            i++;
        } else {
            v[k] = right[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        v[k] = left[i];
        i++;
        k++;
    }

    while (j < n2) {
        v[k] = right[j];
        j++;
        k++;
    }
}

void mergeSort(vector<int>& v, int low, int high) {
    if (low < high) {
        int mid = low + (high - low) / 2;
        mergeSort(v, low, mid);
        mergeSort(v, mid + 1, high);
        merge(v, low, mid, high);
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