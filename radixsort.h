#ifndef RADIXSORT_H
#define RADIXSORT_H
#include <vector>
#include <iostream>
#include <string>
using namespace std;
class RadixSort
{
public:
    RadixSort();
    //all of these functions have to take in the vector and the size of the vector
    int getMax(vector<string>& wordHolder, int n);
    void countSort(vector<string>& wordHolder, int n, int exp);
    void radixsort(vector<string>& wordHolder, int n);
    void print(vector<string>& wordHolder, int n, ofstream& outputFile);
    void mergeSort(vector<string>& wordHolder, int low, int high);
    void merge(vector<string>& wordHolder, int low, int high, int mid);
};

#endif // RADIXSORT_H
