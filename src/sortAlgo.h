#ifndef SORTALGO_H
#define SORTALGO_H

#include <vector>
#include <list>
#include <SDL2/SDL.h>
#include <string>
#include "binaryTree.h"

using namespace std;

using namespace std;

class Swap
{
    SDL_Renderer *r;
    SDL_Window *w;
    int last1 = 0;
    int last2 = 0;
    bool saveScreenshotBMP(std::string filepath);
    int image = 0;
public:
    Swap(SDL_Renderer *renderer, SDL_Window *window);
    void operator()(vector<int> *aVect, int i1, int i2);
    void assign(vector<int> *aVect, int i, int v);
};

class SortAlgo{
protected:
    Swap *swap;
public:
    virtual void sort(vector<int> *aVect) = 0;
    void setSwap(Swap *s);
    ~SortAlgo();
};

class QuickSort: public SortAlgo
{
public:
    QuickSort();
    void sort(vector<int> *aVect);
private:
    int pivot(vector<int> * aVect, int begin, int end);
    void quickSort(vector<int> *aVect, int begin, int end);
};

class Radix: public SortAlgo
{
public:
    Radix();
    void sort(vector<int> *aVect);
    void countSort(vector<int> *aVect, int exp);
};

class TriFusion: public SortAlgo
{
public:
    TriFusion();
    void sort(vector<int> *aVect);
    void triFusion(vector<int> *aVect, int begin, int end);
    void fusion(vector<int> *aVect, int beg1, int end1, int end2);
};

class Gravity: public SortAlgo
{
public:
    Gravity();
    void sort(vector<int> *aVect);
};

class Heap: public SortAlgo
{
    Node *root = nullptr;
    list<Node*> *nodeList;
public:
    Heap();
    ~Heap();
    void sort(vector<int> *aVect);
    void createTree(vector<int> *aVect);
    Node *findEmpty(Node *n, int a);
    void swapNode(Node *n1, Node *n2, vector<int> *aVect);
    bool notGood();
    Node *findNode(int i);
};

#endif