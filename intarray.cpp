#include <iostream>
#include <cstdlib>
#include <cstring>
#include "intarray.h"

using namespace std;

IntArray::IntArray(int s) {
    c = 0;
    m = 0;
    controlSum = 0;
    if (s > 0) {
        size = s;
    } else {
        size = 0;
    }
    originalArray = new int[size];
}

int* IntArray::copyArray() {
    int* newArray = new int[size];
    for (int i = 0; i < size; i++) {
        newArray[i] = originalArray[i];
    }
    return newArray;
}
//инициализация случайными числами
void IntArray::initRand() {
    int *p;
    p = originalArray;
    for (int i = 0; i < size; i++) {
        *p = rand()%100;
        p++;
    }
    controlSum = 0;
    for (int i = 0; i < size; i++) controlSum += originalArray[i];
}
//инициализация последовательными числами
void IntArray::initSerial() {
    int *p;
    p = originalArray;
    for (int i = 0; i < size; i++) {
        *p = i;
        p++;
    }
    controlSum = 0;
    for (int i = 0; i < size; i++) controlSum += originalArray[i];
}
//вывод массива в консоль
void IntArray::printArray(int *array) {
    int *p = array;
    for (int i = 0; i < size; i++) {
        cout << *p <<"  ";
        p++;
    }
    cout << "\n";
}
//возвращает true, если а больше, чем b
bool IntArray::isLarger(int a, int b){
    c++;
    if(a > b) return true;
    else return false;
}
//меняет местами а и b
void IntArray::swap(int &a, int &b){
    m++;
    int temp;
    temp = a;
    a = b;
    b = temp;
}
//проверка числа серий. Отсортированный массив состоит из 1 серии
bool IntArray::seriesNumberCheck(int *array) {
    int seriesNumber = 1;
    bool thisSeries = true;
    for (int i = 0; i < size-1; i++) {
        if ((array[i] <= array[i+1]) != thisSeries) {
            seriesNumber ++;
            thisSeries = !thisSeries;
        }
    }
    if (seriesNumber == 1) return true;
    else return false;
}
//проверка контрольной суммы(сумма всех элементов массива)
bool IntArray::controlSumCheck(int *array) {
    int sum = 0;
    for (int i = 0; i < size; i++) sum += array[i];
    if (sum == controlSum) return true;
    else return false;
}
//вывод в консоль результатов сортировки
void IntArray::printSortResult(int *array, char *name) {
    cout << "\n";
    printArray(originalArray);
    cout << name<<":      C = " << c << "     M = " << m << "\n";
    printArray(array);
    if (seriesNumberCheck(array) == true && controlSumCheck(array) == true) {
        cout << "Correct sorting result \n\n";
    }
    c = 0;
    m = 0;
}


/////////////////// Методы сортировки массива целых чисел ///////////////////
//Сортировка прямым выбором
void IntArray:: directSelectionSort() {
    int *array = copyArray();
    int min;
    for (int i = 0; i < size-1; i++) {
        min = i;
        for (int j = i+1; j < size; j++) {
            if(isLarger(array[min], array[j]) == true) {
                min = j;
            }
        }
        //перемещает наименьший элемент в позицию i
        swap(array[i], array[min]);
    }
    printSortResult(array, "directSelectionSort");
    delete array;
}

//Сортировка пузырьком
void IntArray::bubbleSort() {
    int *array = copyArray();
    for (int i = 1; i < size; i++) {
        for (int j = size-1; j >= i; j--) {
            if(isLarger(array[j], array[j-1]) == false) {
                swap(array[j], array[j-1]);
            }
        }
    }
    printSortResult(array, "bubbleSort");
    delete array;
}
//Шейкерная сортировка
void IntArray::shakerSort() {
    int *array = copyArray();
    int left = 0;
    int right = size-1;
    int k = size;
    do {
        //поочередная реализация пузырьковой сортировки в обоих направлениях
        for(int i = right; i > left; i--) {
            if (isLarger(array[i-1], array[i]) == true) {
                swap(array[i-1], array[i]);

            }
        k = i;
        }
        left = k;
        for(int i = left; i < right; i++) {
            if (isLarger(array[i], array[i+1]) == true) {
                swap(array[i], array[i+1]);
            }
            k = i;
        }
        right = k;
    } while (left < right);
    printSortResult(array, "shakerSort");
    delete array;
}
//Сортировка Шелла
void IntArray::shellSort() {
    int *array = copyArray();
    int j;
    //размер шага
    int step = size/2;
    while (step > 0) {
        for (int i = 0; i < size - step; i++) {
            j = i;
            while(j >= 0 && isLarger(array[j],array[j + step])) {
                swap(array[j],array[j + step]);
                j -= step;
            }
        }
        step = step/2;
    }
    printSortResult(array, "shellSort");
    delete array;
}
//Пирамидальная сортировка
void IntArray::heapSort() {
    int *array = copyArray();
    //построение пирамиды
    for (int i = (size/2)-1; i >= 0; i--) {
        //(size/2)-1 -условно: номер последнего элемента имеющего потомка
        downHeap(array, i, size);
    }
    int n = size;
    // просеивание элементов массива через пирамиду(сортировка)
    while (n > 1) {
        --n;
        swap (array[n], array[0]);
        downHeap(array, 0, n);
    }
    printSortResult(array, "heapSort");
    delete array;
}
//процедура построения пирамиды для сортировки массива пирамидальным методом
void IntArray::downHeap (int *array, int k, int n) {
    int nMax=k;
    int currentElem = array[k];
    int childNumber;
    while (true) {
        //сравниваем элемент с его левым и правым потомками
        //наименьшего потомка меняем местами с текущим элементом
        childNumber = k*2 +1; //индекс левого потомка
        if (childNumber < n && isLarger(array[childNumber], currentElem)) {
            nMax = childNumber;
        }
        childNumber++; //индекс правого потомка
        if (childNumber < n && isLarger(array[childNumber], array[nMax])) {
            nMax = childNumber;
        }
        //если замены не произошло, цикл прерывается принудительно
        if (nMax == k) break;
        //продолжаем работать с потомком, занявшим место предыдущего элемента
        array[k] = array[nMax];
        array[nMax] = currentElem;
        m++;
        k=nMax;

    }
    array[k] = currentElem;
}

//Сортировка Хоара (быстрая сортировка)
void IntArray::quickSort() {
    int *array = copyArray();
    quickSortFunction(array, 0, size-1);
    printSortResult(array, "QuickSort");
    delete array;
}


void IntArray::quickSortFunction(int *array, int left, int right) {
    int mid;
    int i=left;
    int j=right;
    mid = array[(left + right) / 2]; //вычисление опорного элемента
    while (i <= j) {
        //перемещение элементов: в левуя часть, если меньше опорного
        //в правую часть - если больше
        while (isLarger(mid, array[i]) == true) i++;
        while (isLarger(array[j], mid) == true) j--;
        if (i <= j) {
            swap (array[i], array[j]);
            i++;
            j--;
        }
    }
    //разделение массива на две части и сортировка каждой
    //рекурсивные вызовы метода
    if (left < j) {
        quickSortFunction(array, left, j);
    }
    if (i < right) {
        quickSortFunction(array, i, right);
    }
}


