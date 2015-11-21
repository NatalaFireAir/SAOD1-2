#ifndef INTARRAY
#define INTARRAY

#include <cstring>

class IntArray {
private:
    int m;
    int c;
    int size;
    int controlSum;
    int *originalArray;

    bool isLarger(int a, int b);    //сравнение
    void swap(int &a, int &b);      //поменять местами

    bool seriesNumberCheck(int *array);
    bool controlSumCheck(int *array);
    void printSortResult(int *array, char *name);

    void downHeap (int *array, int k, int n);
    void quickSortFunction(int *array, int first, int last);

public:
    IntArray(int s);

    int* copyArray();

    void initRand();
    void initSerial();
    void printArray(int *array);

    void directSelectionSort();
    void bubbleSort();
    void shakerSort();
    void shellSort();
    void heapSort();
    void quickSort();
};
#endif // INTARRAY

