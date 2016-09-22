#include "sortingcompetition.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

SortingCompetition::SortingCompetition()
{

}

//set the name of the inputFile name
SortingCompetition::SortingCompetition(const string& inputFileName)
{
    fileName = inputFileName;
}

//set the name of the input file
void SortingCompetition::setFileName(const string& inputFileName)
{
    fileName = inputFileName;
}

//read the data in and store it into an original vector
bool SortingCompetition::readData()
{
    ifstream inputFile(fileName.c_str());
    while(inputFile >> word)
    {
        //add the word into the wordHolder
        wordHolder.push_back(word);
    }
    return true;
}

//store the data into a copy Holder so this one can be sorted and tested and then reset
bool SortingCompetition::prepareData()
{
    for(int i = 0; i < wordHolder.size(); i++)
    {
        //push the words from wordHolder to the temporary holder
        wordHolderTemp.push_back(wordHolder[i]);
    }
    return true;
}

//function to sort data using radix and merge
void SortingCompetition::sortDataRadixMerge()
{
    //first radix sort will be called to sort the vector by string length
    radixsort();
    //at this point, the vector has been sorted by stringlength
    int i = 0;

    //end index to parse to
    int endIndex = 0;
    //beginning index to parse from
    int beginIndex = 0;

    while(i < wordHolderTemp.size() - 1)
    {
        int first = wordHolderTemp[i].length();
        int second = wordHolderTemp[i+1].length();
        if(first == second)
        {
            //increase endIndex and the size
            i++;
        }
        else
        {
            //once we've gotten an endIndex, we merge from the beginIndex till the end
            endIndex = i;
            //call mergesort
            mergeSort(beginIndex, endIndex);
            //set begin to the end so we can parse from there
            beginIndex = i+1;
            endIndex = i+1;
            i++;
        }

    }
}

//RADIX SORT CODE, TAKEN OFF OF GEEKFORGEEKS
//gets the max stringlength from the wordHolder
int SortingCompetition::getMax()
{
    //determine max length of string
    int mx = wordHolderTemp[0].length();
    for (int i = 1; i < wordHolderTemp.size(); i++)
        //if there is a bigger string length, then store that one as the biggest
        if (wordHolderTemp[i].length() > mx)
            mx = wordHolderTemp[i].length();
    //return the max stringlength
    return mx;
}

// A function to do counting sort of vector wordHolder according to the digit represented by exp.
void SortingCompetition::countSort(int exp)
{
       vector<string> output (wordHolderTemp.size()); // output array the size of the vector holder
       int i, count[10] = {0};

       // Store count of occurrences in count[]
       for (i = 0; i < wordHolderTemp.size(); i++)
           count[ (wordHolderTemp[i].length()/exp)%10 ]++;

       // Change count[i] so that count[i] now contains actual position of this digit in output[]
       for (i = 1; i < 10; i++)
           count[i] += count[i - 1];

       // Build the output array
       for (i = wordHolderTemp.size() - 1; i >= 0; i--)
        {
            output[count[ (wordHolderTemp[i].length()/exp)%10 ] - 1] = wordHolderTemp[i];
            count[ (wordHolderTemp[i].length()/exp)%10 ]--;
        }

        // Copy the output array to wordHolder, so that wordHolder now contains sorted strings according to size length
        for (i = 0; i < wordHolderTemp.size(); i++)
        {
            wordHolderTemp[i] = output[i];
        }
}

void SortingCompetition::radixsort()
{
    // Find the maximum number to know number of digits
    int m = getMax();

    // Do counting sort for every digit. Note that instead of passing digit number, exp is passed. exp is 10^i where
    //i is current digit number
    for (int exp = 1; m/exp > 0; exp *= 10)
        countSort(exp);
}


//MERGE SORT CODE
void SortingCompetition::mergeSort(int low, int high)
{
    //low and high are supposed to be the highest and lowest index should be called with wordHolder, 0, wordHolder.size()-1
        int mid = 0;
        if (low < high)
        {
            mid=(low+high)/2;
            mergeSort(low, mid);
            mergeSort(mid+1, high);
            merge(low, high, mid);
        }
        return;
}

void SortingCompetition::merge(int low, int high, int mid)
{
    int i = low;
    int j = mid+1;
    int k = low;
    //create a temporary wordHolder with the size of the original
    vector<string> wordHolderTempRef (wordHolderTemp.size());

    // compares adjacent words and copies whichever goes first alphabetically into wHolderTemp
    while (i <= mid && j <= high)
    {
        //sort the words
        if(wordHolderTemp[i].compare(wordHolderTemp[j]) < 1)
        {
            wordHolderTempRef[k] = wordHolderTemp[i];
            k++;
            i++;
        }
        else
        {
            wordHolderTempRef[k] = wordHolderTemp[j];
            k++;
            j++;
        }
    }

    // from first half, copies words/page numbers from original holder into temp holder
    while (i <= mid)
    {
        wordHolderTempRef[k] = wordHolderTemp[i];
        k++;
        i++;
    }
    // from second half, copies words/page numbers from original holder into temp holder
    while (j <= high)
    {
        wordHolderTempRef[k] = wordHolderTemp[j];
        k++;
        j++;
    }
    // keeps copying words/page numbers (ordered) from temp holder back into the orignal holders until complete
    for (i = low; i < k; i++)
    {
       wordHolderTemp[i] = wordHolderTempRef[i];
    }

}


//sort using radix and quicksort median of three
void SortingCompetition::sortDataRadixQuickThree()
{
    //first radix sort will be called to sort the vector by string length
    radixsort();
    //at this point, the vector has been sorted by stringlength
    int i = 0;

    //end index to parse to
    int endIndex = 0;
    //beginning index to parse from
    int beginIndex = 0;

    while(i < wordHolderTemp.size() - 1)
    {
        int first = wordHolderTemp[i].length();
        int second = wordHolderTemp[i+1].length();
        if(first == second)
        {
            //increase endIndex and the size
            i++;
        }
        else
        {
            //once we've gotten an endIndex, we merge from the beginIndex till the end
            endIndex = i;
            //call quicksort median of three
            quicksortThree(beginIndex, endIndex);
            //set begin to the end so we can parse from there
            beginIndex = i+1;
            endIndex = i+1;
            i++;
        }

    }
}


//EMELY'S QUICK SORT MEDIAN OF THREE CODE
//quick sort to call
void SortingCompetition::quicksortThree(int begin, int end)
{
    //designed to take in the pieces of the array to be sorted
    //these pieces are sorted due to their string length
    recQuickSortThree(begin, end);
}

//recursive quicksort called internally in main quicksort
//again, this functions takes into account the size of the array holder to be sorted
void SortingCompetition::recQuickSortThree(int begin, int end)
{
    //works with the size of the specific string lengths
    //this is the size of the array to be sorted
    int size = end - begin + 1;
    if(size <=3)
    {
        //will just go ahead and manually sort the array if it is too small for quickSort
        manualSortThree(begin, end);
    }
    //assuming that it is bigger than 3 then partition it into sections
    else
    {
        //determines which string is in the middle
        string median = medianOf3(begin, end);
        //partion determines how to split up the array
        int p = partitionThree(begin, end, median);

        //following keeps dividing up the array to sort it
        recQuickSortThree(begin, p-1);
        recQuickSortThree(p+1, end);
    }
}

//gets the median of 3
const string& SortingCompetition::medianOf3(int left, int right)
{
    int center = (left+right)/2;

    //orders left and center
    if(wordHolderTemp[left].compare(wordHolderTemp[center]) > 0)
    swap(wordHolderTemp[left], wordHolderTemp[center]);

    //orders left and right
    if(wordHolderTemp[left].compare(wordHolderTemp[right]) > 0)
        swap(wordHolderTemp[left], wordHolderTemp[right]);

    //orders center and right
    if(wordHolderTemp[center].compare(wordHolderTemp[right]) > 0)
        swap(wordHolderTemp[center], wordHolderTemp[right]);

    swap(wordHolderTemp[center], wordHolderTemp[right-1]); //places pivot on right
    return wordHolderTemp[right-1]; // returns median value
}

//partitions the sections
int SortingCompetition::partitionThree(int begin, int end, string pivot){
    int leftPtr = begin;         //right of first string
    int rightPtr = end -1;    //left of pivot

    while(true){
        //find bigger
       while(wordHolderTemp[++leftPtr].compare(pivot) < 0)
            ;
        //find smaller
       while(wordHolderTemp[--rightPtr].compare(pivot) > 0)
            ;
        //if pointers cross, partition done
        if(leftPtr >= rightPtr)
            break;
        //otherwise, swap elements
       else
            swap(wordHolderTemp[leftPtr], wordHolderTemp[rightPtr]);
    }
    swap(wordHolderTemp[leftPtr], wordHolderTemp[end-1]);
    return leftPtr;                             // return pivot location
}

//may or may not need this part, since not very likely that there will be <=3 words of any length
void SortingCompetition::manualSortThree(int begin, int end){
    int size = end-begin + 1;

    //no sort is necessarry
    if(size <=1)
        return;
    //2-sort left and right
    if(size ==2)
    {
       if(wordHolderTemp[begin].compare(wordHolderTemp[end]) > 0)
            swap(wordHolderTemp[begin], wordHolderTemp[end]);
        return;
    }
    //size is 3, so 2-sort left, center, and right
    else{
        //left, center swap
       if(wordHolderTemp[begin].compare(wordHolderTemp[end-1]) > 0)
          swap(wordHolderTemp[begin], wordHolderTemp[end-1]);
        //left, right swap
        if(wordHolderTemp[begin].compare(wordHolderTemp[end]) > 0)
            swap(wordHolderTemp[begin], wordHolderTemp[end]);
        //center, right swap
        if(wordHolderTemp[end-1].compare(wordHolderTemp[end]) > 0)
            swap(wordHolderTemp[end-1], wordHolderTemp[end]);
    }
}


//sort using radix and quicksort median of five
void SortingCompetition::sortDataRadixQuickFive()
{
    //first radix sort will be called to sort the vector by string length
    radixsort();
    //at this point, the vector has been sorted by stringlength
    int i = 0;

    //end index to parse to
    int endIndex = 0;
    //beginning index to parse from
    int beginIndex = 0;

    while(i < wordHolderTemp.size() - 1)
    {
        int first = wordHolderTemp[i].length();
        int second = wordHolderTemp[i+1].length();
        if(first == second)
        {
            //increase endIndex and the size
            i++;
        }
        else
        {
            //once we've gotten an endIndex, we merge from the beginIndex till the end
            endIndex = i;
            //call quicksort median of five
            quicksortFive(beginIndex, endIndex);
            //set begin to the end so we can parse from there
            beginIndex = i+1;
            endIndex = i+1;
            i++;
        }

    }
}

//EMELY'S QUICK SORT MEDIAN OF FIVE CODE, NEEDS TO BE ADJUSTED AS SUCH
//quick sort to call
void SortingCompetition::quicksortFive(int begin, int end)
{
    //designed to take in the pieces of the array to be sorted
    //these pieces are sorted due to their string length
    recQuickSortFive(begin, end);
}

//recursive quicksort called internally in main quicksort
//again, this functions takes into account the size of the array holder to be sorted
void SortingCompetition::recQuickSortFive(int begin, int end)
{
    //works with the size of the specific string lengths
    //this is the size of the array to be sorted
    int size = end - begin + 1;
    if(size <=3)
    {
        //will just go ahead and manually sort the array if it is too small for quickSort
        manualSortFive(begin, end);
    }
    //assuming that it is bigger than 3 then partition it into sections
    else
    {
        //determines which string is in the middle
        string median = medianOf5(begin, end);
        //partion determines how to split up the array
        int p = partitionFive(begin, end, median);

        //following keeps dividing up the array to sort it
        recQuickSortFive(begin, p-1);
        recQuickSortFive(p+1, end);
    }
}

//gets the median of 3
const string& SortingCompetition::medianOf5(int left, int right)
{
    int center = (left+right)/2;
    int midleft = (left+center)/2;
    int midright = (right+center)/2;

    //orders left and mid-left
    if(wordHolderTemp[left].compare(wordHolderTemp[midleft]) > 0)
        swap(wordHolderTemp[left], wordHolderTemp[midleft]);

    //orders left and center
    if(wordHolderTemp[left].compare(wordHolderTemp[center]) > 0)
        swap(wordHolderTemp[left], wordHolderTemp[center]);

    //orders left and mid-right
    if(wordHolderTemp[left].compare(wordHolderTemp[midright]) > 0)
        swap(wordHolderTemp[left], wordHolderTemp[midright]);

    //orders left and right
    if(wordHolderTemp[left].compare(wordHolderTemp[right]) > 0)
        swap(wordHolderTemp[left], wordHolderTemp[right]);

    //orders center and mid-left
    if(wordHolderTemp[center].compare(wordHolderTemp[midleft]) > 0)
        swap(wordHolderTemp[center], wordHolderTemp[midleft]);

    //orders center and mid-right
    if(wordHolderTemp[center].compare(wordHolderTemp[midright]) > 0)
        swap(wordHolderTemp[center], wordHolderTemp[midright]);

    //orders center and right
    if(wordHolderTemp[center].compare(wordHolderTemp[right]) > 0)
        swap(wordHolderTemp[center], wordHolderTemp[right]);

    //orders right and mid-left
    if(wordHolderTemp[right].compare(wordHolderTemp[midleft]) > 0)
        swap(wordHolderTemp[right], wordHolderTemp[midleft]);

    //orders right and mid-right
    if(wordHolderTemp[right].compare(wordHolderTemp[midright]) > 0)
        swap(wordHolderTemp[right], wordHolderTemp[midright]);

    //orders mid-right and mid-left
    if(wordHolderTemp[midleft].compare(wordHolderTemp[midright]) > 0)
        swap(wordHolderTemp[midleft], wordHolderTemp[midright]);

    swap(wordHolderTemp[center], wordHolderTemp[right-1]); //places pivot on right
    return wordHolderTemp[right-1]; // returns median value
}

//partitions the sections
int SortingCompetition::partitionFive(int begin, int end, string pivot){
    int leftPtr = begin;         //right of first string
    int rightPtr = end -1;    //left of pivot

    while(true){
        //find bigger
       while(wordHolderTemp[++leftPtr].compare(pivot) < 0)
            ;
        //find smaller
       while(wordHolderTemp[--rightPtr].compare(pivot) > 0)
            ;
        //if pointers cross, partition done
        if(leftPtr >= rightPtr)
            break;
        //otherwise, swap elements
       else
            swap(wordHolderTemp[leftPtr], wordHolderTemp[rightPtr]);
    }
    swap(wordHolderTemp[leftPtr], wordHolderTemp[end-1]);
    return leftPtr;                             // return pivot location
}

//may or may not need this part, since not very likely that there will be <=3 words of any length
void SortingCompetition::manualSortFive(int begin, int end){
    int size = end-begin + 1;

    //no sort is necessarry
    if(size <=1)
        return;
    //2-sort left and right
    if(size ==2)
    {
       if(wordHolderTemp[begin].compare(wordHolderTemp[end]) > 0)
            swap(wordHolderTemp[begin], wordHolderTemp[end]);
        return;
    }
    //size is 3, so 2-sort left, center, and right
    else{
        //left, center swap
       if(wordHolderTemp[begin].compare(wordHolderTemp[end-1]) > 0)
          swap(wordHolderTemp[begin], wordHolderTemp[end-1]);
        //left, right swap
        if(wordHolderTemp[begin].compare(wordHolderTemp[end]) > 0)
            swap(wordHolderTemp[begin], wordHolderTemp[end]);
        //center, right swap
        if(wordHolderTemp[end-1].compare(wordHolderTemp[end]) > 0)
            swap(wordHolderTemp[end-1], wordHolderTemp[end]);
    }
}

//sort using radix and heap
void SortingCompetition::sortDataRadixHeap()
{
    //first radix sort will be called to sort the vector by string length
    radixsort();
    cout << "end of Radix" << endl;
    //at this point, the vector has been sorted by stringlength
    int i = 0;

    //end index to parse to
    int endIndex = 0;
    //beginning index to parse from
    int beginIndex = 0;

    while(i < wordHolderTemp.size() - 1)
    {
        int first = wordHolderTemp[i].length();
        int second = wordHolderTemp[i+1].length();
        if(first == second)
        {
            //increase endIndex and the size
            i++;
        }
        else
        {
            //once we've gotten an endIndex, we merge from the beginIndex till the end
            endIndex = i;
            //call heap sort
            heapsort(beginIndex, endIndex);
            //set begin to the end so we can parse from there
            beginIndex = i+1;
            endIndex = i+1;
            i++;
        }

    }
}

//Emely's heap sort
//  Heapsort code found in "Data Structures and Algorithms Analysis in Java" by Mark Allen Weiss (2nd Edition)
//  Also doubled checked with code in www.cs.fsu.edu/~breno/COP-4530/slides/21-anim.pdf

//standard heapsort that takes in vector of strings
//heapSort is supposed to take in int begin and int end
void SortingCompetition::heapsort(int begin, int end){
    //build the heap
    for(int i=int(wordHolderTemp.size()/2); i>=0; i--)
        //need to change from beginning to end
        percDown(i, int(wordHolderTemp.size()));
    //deleteMax
    for(int j=int(wordHolderTemp.size()-1); j>0; j--)
    {
        swap(wordHolderTemp[0], wordHolderTemp[j]);
        percDown(begin, j);
    }
}

//to be used internally in the heapsort
//returns the index of the left child
int SortingCompetition::leftChild(int i){
    return 2 * i + 1;
}

//to be used internally in the heapsort
//used to delete the maximum and build the heap
void SortingCompetition::percDown(int begin, int end){
    int child;
    string temp;

    for(temp = wordHolderTemp[begin]; leftChild(begin) < end; begin=child)
    {
        child = leftChild(begin);
        if(child != end-1 && wordHolderTemp[child].compare(wordHolderTemp[child+1]) < 0)
            child++;
        if(temp.compare(wordHolderTemp[child]) < 0)
            wordHolderTemp[begin] = wordHolderTemp[child];
        else
            break;
    }
    wordHolderTemp[begin] = temp;
}


//sort using radix and exchange
void SortingCompetition::sortDataRadixExchange()
{
    //This will call the radix sort and merge sort
    //first radix sort will be called to sort the vector by string length
    radixsort();
    //at this point, the vector has been sorted by stringlength
    int i = 0;

    //end index to parse to
    int endIndex = 0;
    //beginning index to parse from
    int beginIndex = 0;

    while(i < wordHolderTemp.size() - 1)
    {
        int first = wordHolderTemp[i].length();
        int second = wordHolderTemp[i+1].length();
        if(first == second)
        {
            //increase endIndex and the size
            i++;
        }
        else
        {
            //once we've gotten an endIndex, we merge from the beginIndex till the end
            endIndex = i;
            //call exchange sort
            exchangeSort(beginIndex, endIndex);
            //set begin to the end so we can parse from there
            beginIndex = i+1;
            endIndex = i+1;
            i++;
        }

    }
}

void SortingCompetition::exchangeSort(int begin, int end)
{
    for(int i = begin; i < end; i++)
    {
        for(int j = begin+1; j < end; i++)
        {
            if(wordHolderTemp[i] > wordHolderTemp[j])
            {
                //swap the two values, secures an O(n) function
                string temp = wordHolderTemp[i];
                wordHolderTemp[i] = wordHolderTemp[j];
                wordHolderTemp[j] = temp;
            }
        }
    }
}

void SortingCompetition::outputData(const string& outputFileName)
{
    ofstream output(outputFileName.c_str());
    for(int i = 0; i < wordHolderTemp.size(); i++)
    {
        output << wordHolderTemp[i] << endl;
    }
}

void SortingCompetition::clearTemp()
{
    wordHolderTemp.clear();
}
