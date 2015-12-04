#include <iostream>
#include <cstdlib>
#include <ctime>

#include "intarray.h"
using namespace std;

int main() {
    srand(time(NULL));

    IntArray intArray(10);
    //Лабораторная работа 1
    //инициализация слцчайными числами
    cout << "Lab 1\n";
    intArray.initRand();
    intArray.directSelectionSort();
    intArray.bubbleSort();
    intArray.shakerSort();
    //инициализачия последовательными числами
    intArray.initSerial();
    intArray.directSelectionSort();
    intArray.bubbleSort();
    intArray.shakerSort();

    //Лабораторная работа 2
    //инициализация слцчайными числами
    cout << "Lab 2\n";
    intArray.initRand();
    intArray.shellSort();
    intArray.heapSort();
    intArray.quickSort();
    //инициализачия последовательными числами
    intArray.initSerial();
    intArray.shellSort();
    intArray.heapSort();
    intArray.quickSort();

    return 0;
}

