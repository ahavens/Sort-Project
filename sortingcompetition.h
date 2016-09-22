#ifndef SORTINGCOMPETITION_H
#define SORTINGCOMPETITION_H
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

class SortingCompetition
{
private:
    vector<string> wordHolder;
    vector<string> wordHolderTemp;
    string word;
    string fileName;
public:
    SortingCompetition();
    SortingCompetition(const string& inputFileName);
    void setFileName(const string& inputFileName);
    bool readData();
    bool prepareData();
    void clearTemp();

    //five sort functions to guage the speed of all the combos
    void sortDataRadixMerge();
    void sortDataRadixQuickThree();
    void sortDataRadixQuickFive();
    void sortDataRadixHeap();
    void sortDataRadixExchange();

    void outputData(const string& outputFileName);

    //Sort functions
    int getMax();
    void countSort(int exp);
    void radixsort();
    void mergeSort(int low, int high);
    void merge(int low, int high, int mid);

    //median of three quick sort
    void quicksortThree(int begin, int end);
    void recQuickSortThree(int begin, int end);
    const string& medianOf3(int begin, int end);
    int partitionThree(int begin, int end, string pivot);
    void manualSortThree(int begin, int end);

    //median of five quick sort
    void quicksortFive(int begin, int end);
    void recQuickSortFive(int begin, int end);
    const string& medianOf5(int begin, int end);
    int partitionFive(int begin, int end, string pivot);
    void manualSortFive(int begin, int end);

    void heapsort(int begin, int end);
    int leftChild(int i);
    void percDown(int begin, int end);
    void exchangeSort(int being, int end);


};

#endif // SORTINGCOMPETITION_H
