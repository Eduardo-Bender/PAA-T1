#include "sorts.hpp"

#define RED "\033[31m"
#define GREEN "\033[32m"
#define RESET "\033[0m"

// g++ main.cpp -o main && ./main < input.txt
// g++ main.cpp -o main && ./main < input.txt
// g++ main.cpp -o main && ./main < input.txt

// cout << GREEN << "+ Merge: " << RESET

void printVector(const vector<int>& v, int comeco, int fim) {
    cout << "[ ";
    for (int i = comeco; i <= fim; i++) {
        cout << v[i] << " ";
    }
    cout << "]" << endl;
}

void printVectorFull(vector<int>& vec)
{
    for (int v : vec)
    {
        cout << v << " ";
    }
    cout << endl;
}

int main() {
    vector<int> numeros;
    string input;

    cout << "Digite os numeros (digite X para parar): " << endl;

    while (true) {
        cin >> input;
        
        if (input == "X" || input == "x") {
            break;
        }

        try {
            int valor = stoi(input); 
            numeros.push_back(valor);
        } catch (invalid_argument& e) {
            cout << "Entrada invalida. Digite um numero ou X para parar." << endl;
        }
    }

    cout << "Original: ";
    printVector(numeros, 0, numeros.size() - 1);

    vector<int> mergeVec = numeros;
    mergeSort(mergeVec, 0, mergeVec.size() - 1);
    cout << "MergeSort: ";
    printVector(mergeVec, 0, mergeVec.size() - 1);

    vector<int> quickVec = numeros;
    quickSort(quickVec, 0, quickVec.size() - 1);
    cout << "QuickSort: ";
    printVector(quickVec, 0, quickVec.size() - 1);

    vector<int> shellVec = numeros;
    shellSort(shellVec, 0, shellVec.size() - 1);
    cout << "ShellSort: ";
    printVector(shellVec, 0, shellVec.size() - 1);

    return 0;
}