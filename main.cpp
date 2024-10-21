#include "sorts.hpp"

using namespace std;

// g++ main.cpp -o main && ./main < input.txt
// g++ main.cpp -o main && ./main < input.txt
// g++ main.cpp -o main && ./main < input.txt

#define ITERATIONS 10

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
    int n;
    vector<int> numeros;

    while (cin >> n) {
        numeros.push_back(n);
    }

    clearScreen();

    vector<double> mergeTimes;
    vector<double> iMergeTimes;
    vector<double> quickTimes;
    vector<double> shellTimes;

    vector<int> mergeVec = numeros;
    vector<int> iMergeVec = numeros;
    vector<int> quickVec = numeros;
    vector<int> shellVec = numeros;

    /*cout << "Original: ";
    printVectorFull(numeros);
    cout << endl;*/

    for (int i = 0; i < ITERATIONS; i++) {
        mergeVec = numeros;
        iMergeVec = numeros;
        quickVec = numeros;
        shellVec = numeros;

        // MergeSort timing
        auto start = chrono::high_resolution_clock::now();
        mergeSort(mergeVec, 0, mergeVec.size() - 1);
        auto end = chrono::high_resolution_clock::now();
        mergeTimes.push_back(chrono::duration<double, milli>(end - start).count());

        // Iterative MergeSort timing
        start = chrono::high_resolution_clock::now();
        iterativeMergeSort(iMergeVec);
        end = chrono::high_resolution_clock::now();
        iMergeTimes.push_back(chrono::duration<double, milli>(end - start).count());
        
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
    double iMergeAvg = accumulate(iMergeTimes.begin(), iMergeTimes.end(), 0.0) / ITERATIONS;
    double quickAvg = accumulate(quickTimes.begin(), quickTimes.end(), 0.0) / ITERATIONS;
    double shellAvg = accumulate(shellTimes.begin(), shellTimes.end(), 0.0) / ITERATIONS;

    /*cout << "Sorted: ";
    printVectorFull(shellVec);
    cout << endl;*/

    printExecutionTime(mergeAvg, "MergeSort");
    printExecutionTime(iMergeAvg, "ItMergeSort");
    printExecutionTime(quickAvg, "QuickSort");
    printExecutionTime(shellAvg, "ShellSort");


    return 0;
}