#include <iostream>
#include <ctime>
#include <vector>
#include <random>
#include <algorithm>

using namespace std;

void printVect(vector<int> * aVect)
{
    for(int i: *aVect)
        cout << i << endl;
}

int pivot(vector<int> * aVect, int begin, int end)
{
    int small = begin-1;
    for(int i=begin; i < end; ++i)
    {
        if(aVect->at(i) < aVect->at(end))
        {
            ++small;
            swap(aVect->at(i), aVect->at(small));
        }
    }
    swap(aVect->at(end), aVect->at(small+1));
    return small+1;
}

void quickSort(vector<int> * aVect, int begin=0, int end=99)
{
    int p = pivot(aVect, begin, end);
    if(p > begin)
        quickSort(aVect, begin, p-1);
    if(p < end)
        quickSort(aVect, p+1, end);
}

int main()
{
    srand(time(0));
    vector<int> * aVect = new vector<int>;
    for(int i=0; i<10; ++i)
        aVect->push_back(i);
    random_shuffle(aVect->begin(), aVect->end());
    printVect(aVect);

    quickSort(aVect, 0, aVect->size()-1);
    cout << "tri" << endl << endl;
    printVect(aVect);

    delete aVect;
    return 0;
}