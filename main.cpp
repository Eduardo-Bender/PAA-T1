#include <stdio.h>
#include <iostream>
#include <vector>
#include <chrono>

using namespace std;

#define RED "\033[31m"
#define GREEN "\033[32m"
#define RESET "\033[0m"

// g++ main.cpp -o main && ./main < input.txt
// g++ main.cpp -o main && ./main < input.txt
// g++ main.cpp -o main && ./main < input.txt

// cout << GREEN << "+ Merge: " << RESET

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

void printVectorFull(vector<int>& vec)
{
    for (int v : vec)
    {
        cout << v << " ";
    }
    cout << endl;
}

void merge(vector<int>& v, int comeco, int meio, int fim) {
    int com1 = comeco, com2 = meio+1, comAux = 0, tam = fim-comeco+1;
    vector<int> vAux(tam);

    while(com1 <= meio && com2 <= fim){
        if(v[com1] < v[com2]) {
            vAux[comAux] = v[com1];
            com1++;
        } else {
            vAux[comAux] = v[com2];
            com2++;
        }
        comAux++;
    }

    while(com1 <= meio){ 
        vAux[comAux] = v[com1];
        comAux++;
        com1++;
    }

    while(com2 <= fim) {  
        vAux[comAux] = v[com2];
        comAux++;
        com2++;
    }

    for(comAux = comeco; comAux <= fim; comAux++){   
        v[comAux] = vAux[comAux-comeco];
    }
}

void mergeSort(vector<int>& v, int comeco, int fim, int depth = 0){
    string indent = string(depth * 4, ' ');
    cout << indent;
    printVectorDivide(v, comeco, fim);

    if (comeco < fim) {
        int meio = (fim+comeco)/2;

        mergeSort(v, comeco, meio, depth + 1);
        mergeSort(v, meio+1, fim, depth + 1);
        merge(v, comeco, meio, fim);

        printVectorMerge(v, comeco, fim);
    }
}

int main()
{
    auto start = chrono::high_resolution_clock::now();

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

    cout << "Input: " << endl;
    printVectorFull(numeros);
    cout << endl;

    mergeSort(numeros, 0, numeros.size()-1);

    cout << "Output: " << endl;
    printVectorFull(numeros);
    cout << endl;

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> duration = end - start;
    cout << "Tempo de execucao: " << duration.count() << " ms" << endl;

    return 0;
}