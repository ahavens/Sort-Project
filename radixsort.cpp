#include "radixsort.h"
using namespace std;
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <locale>
#include <utility>
#include <algorithm>

using namespace std;

RadixSort::RadixSort()
{
}
//able to treat a vector like a normal array
// A utility function to get maximum string length in the vector wordHolder
int RadixSort::getMax(vector<string>& wordHolder, int n)
{
    //determine max length of string
    int mx = wordHolder[0].length();
    for (int i = 1; i < n; i++)
        //if there is a bigger string length, then store that one as the biggest
        if (wordHolder[i].length() > mx)
            mx = wordHolder[i].length();
    //return the max stringlength
    return mx;
}

// A function to do counting sort of vector wordHolder according to
// the digit represented by exp.
void RadixSort::countSort(vector<string>& wordHolder, int n, int exp)
{
    vector<string> output (n); // output array the size of the vector holder
    int i, count[10] = {0};

    // Store count of occurrences in count[]
    for (i = 0; i < n; i++)
        count[ (wordHolder[i].length()/exp)%10 ]++;

    // Change count[i] so that count[i] now contains actual position of
    // this digit in output[]
    for (i = 1; i < 10; i++)
        count[i] += count[i - 1];

    // Build the output array
    for (i = n - 1; i >= 0; i--)
    {
        output[count[ (wordHolder[i].length()/exp)%10 ] - 1] = wordHolder[i];
        count[ (wordHolder[i].length()/exp)%10 ]--;
    }

    // Copy the output array to wordHolder, so that wordHolder now
    // contains sorted strings according to size length
    for (i = 0; i < n; i++)
    {
        wordHolder[i] = output[i];
        cout << wordHolder[i] << endl;
    }
}

// The main function to that sorts vector wordHolder of size n using Radix Sort
void RadixSort::radixsort(vector<string>& wordHolder, int n)
{
    // Find the maximum number to know number of digits
    int m = getMax(wordHolder, n);

    // Do counting sort for every digit. Note that instead of passing digit
    // number, exp is passed. exp is 10^i where i is current digit number
    for (int exp = 1; m/exp > 0; exp *= 10)
        countSort(wordHolder, n, exp);
    mergeSort(wordHolder, 0, wordHolder.size()-1);
}

// A utility function to print an array
void RadixSort::print(vector<string>& wordHolder, int n, ofstream& outputFile)
{
    for (int i = 0; i < n; i++)
        outputFile << wordHolder[i] << endl;
}

//need to find a way to get rid of the capital letters
void RadixSort::mergeSort(vector<string>& wordHolder, int low, int high)
{
//low and high are supposed to be the highest and lowest index
//should be called with wordHolder, 0, wordHolder.size()-1
    int mid;
    if (low < high)
    {
        mid=(low+high)/2;
        mergeSort(wordHolder, low, mid);
        mergeSort(wordHolder, mid+1, high);
        merge(wordHolder, low, high, mid);
    }
    return;
}

// combines the parts of the merge sort
void RadixSort::merge(vector<string>& wordHolder, int low, int high, int mid)
{
    int i = low;
    int j = mid+1;
    int k = low;
    //create a temporary wordHolder with the size of the original
    vector<string> wordHolderTemp (wordHolder.size());

    // compares adjacent words and copies whichever goes first alphabetically into wHolderTemp
    while (i <= mid && j <= high)
    {
        //assuming that there might be some words that are capitalized, Emely's code accounts for it but can't
        //workaround it in order to ignore the capital letters, so we are going to ignore case and just focus on
        //it's order
        //assign temporary string variables
        string tempJ = wordHolder[j];
        string tempI = wordHolder[i];
        //transform them into lowercase variables
        transform(tempI.begin(), tempI.end(), tempI.begin(), ::tolower);
        transform(tempJ.begin(), tempJ.end(), tempJ.begin(), ::tolower);
        //this should provide a good enough workaround where it will not matter
        if(tempI.compare(tempJ) < 1)
        {
            wordHolderTemp[k] = wordHolder[i];
            k++;
            i++;
        }
        else
        {
            wordHolderTemp[k] = wordHolder[j];
            k++;
            j++;
        }
    }

    // from first half, copies words/page numbers from original holder into temp holder
    while (i <= mid)
    {
        wordHolderTemp[k] = wordHolder[i];
        k++;
        i++;
    }
    // from second half, copies words/page numbers from original holder into temp holder
    while (j <= high)
    {
        wordHolderTemp[k] = wordHolder[j];
        k++;
        j++;
    }
    // keeps copying words/page numbers (ordered) from temp holder back into the orignal holders until complete
    for (i = low; i < k; i++)
    {
       wordHolder[i] = wordHolderTemp[i];
    }
}

