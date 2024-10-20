#include "sorts.hpp"

using namespace std;

// g++ main.cpp -o main && ./main < input.txt
// g++ main.cpp -o main && ./main < input.txt
// g++ main.cpp -o main && ./main < input.txt

// cout << GREEN << "+ Merge: " << RESET

#define ITERATIONS 100000

void clearScreen()
{
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void printVectorFull(vector<int>& vec)
{
    for (int v : vec)
    {
        cout << v << " ";
    }
    cout << endl;
}

void printExecutionTime(double duration, string sort)
{
    cout << "Tempo de execucao do " << sort << ": " << GREEN << duration << RESET << " ms"  << endl;
}

int main() {
    vector<int> numeros;
    string input;

    cout << "Digite os numeros (digite X para parar): " << endl << endl;

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
    clearScreen();

    vector<double> mergeTimes;
    vector<double> quickTimes;
    vector<double> shellTimes;

    cout << "Original: ";
    printVectorFull(numeros);
    cout << endl;

    for (int i = 0; i < ITERATIONS; i++) {
        vector<int> mergeVec = numeros;
        vector<int> quickVec = numeros;
        vector<int> shellVec = numeros;

        // MergeSort timing
        auto start = chrono::high_resolution_clock::now();
        mergeSort(mergeVec, 0, mergeVec.size() - 1);
        auto end = chrono::high_resolution_clock::now();
        mergeTimes.push_back(chrono::duration<double, milli>(end - start).count());

        // QuickSort timing
        start = chrono::high_resolution_clock::now();
        quickSort(quickVec, 0, quickVec.size() - 1);
        end = chrono::high_resolution_clock::now();
        quickTimes.push_back(chrono::duration<double, milli>(end - start).count());

        // ShellSort timing
        start = chrono::high_resolution_clock::now();
        shellSort(shellVec, 0, shellVec.size() - 1);
        end = chrono::high_resolution_clock::now();
        shellTimes.push_back(chrono::duration<double, milli>(end - start).count());
    }

    double mergeAvg = accumulate(mergeTimes.begin(), mergeTimes.end(), 0.0) / ITERATIONS;
    double quickAvg = accumulate(quickTimes.begin(), quickTimes.end(), 0.0) / ITERATIONS;
    double shellAvg = accumulate(shellTimes.begin(), shellTimes.end(), 0.0) / ITERATIONS;

    printExecutionTime(mergeAvg, "MergeSort");
    printExecutionTime(quickAvg, "QuickSort");
    printExecutionTime(shellAvg, "ShellSort");

    cout << "Sorted: ";
    printVectorFull(numeros);
    cout << endl;

    return 0;
}