#include <iostream>
#include <cstdlib>
#include <ctime>

#include "intarray.h"
using namespace std;

int main() {
    srand(time(NULL));
    IntArray intArray(20);
    intArray.initRand();
    intArray.directSelectionSort();
    intArray.bubbleSort();
    intArray.shakerSort();
    intArray.shellSort();
    intArray.heapSort();
    intArray.quickSort();
    return 0;
}

