#include <iostream>
#include <fstream>
#include <sstream>
//#include <chrono>
//#include <ctime>
#include "sortingcompetition.h"
using namespace std;

//EMELY VILLEADA PRINCIPE AND AURORA HAVENS' SORT PROJECT


int main(int argc, char *argv[])
{

    SortingCompetition* obj = new SortingCompetition();

    obj->setFileName(argv[1]);
    obj->readData();
    obj->prepareData();

    //radix-heap combo
    //declare 2 time points
    //chrono::time_point<chrono::system_clock> startRadixHeap, endRadixHeap;
    //start the clock
    //startRadixHeap = chrono::system_clock::now();
    //sort the data with a radix-heap combo
     obj->sortDataRadixHeap();
    //endRadixHeap = chrono::system_clock::now();
    //subtract end from beginning to get number of seconds elapsed
    //chrono::duration<double> elapsed_secondsRadixHeap = endRadixHeap-startRadixHeap;
    //time_t end_timeRadixHeap = chrono::system_clock::to_time_t(end);
    //output the duration.
    //cout << "finished computation at " <<ctime(&end_timeRadixHeap)<< "elapsed time: " << elapsed_secondsRadixHeap.count() << "s\n";
     obj->outputData(argv[2]);



    delete obj;

    return 0;
}
