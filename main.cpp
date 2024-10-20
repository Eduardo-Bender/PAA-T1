#include <stdio.h>
#include <iostream>
#include <vector>

using namespace std;

// g++ main.cpp -o main && ./main < input.txt
// g++ main.cpp -o main && ./main < input.txt
// g++ main.cpp -o main && ./main < input.txt

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

void mergeSort(vector<int>& v, int comeco, int fim){
    if (comeco < fim) {
        int meio = (fim+comeco)/2;

        mergeSort(v, comeco, meio);
        mergeSort(v, meio+1, fim);
        merge(v, comeco, meio, fim);
    }
}

void printVector(vector<int>& vec)
{
    for (int v : vec)
    {
        cout << v << " ";
    }
    cout << endl;
}

int main()
{
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
    printVector(numeros);
    cout << endl;

    mergeSort(numeros, 0, numeros.size()-1);

    cout << "Output: " << endl;
    printVector(numeros);
    cout << endl;

    return 0;
}