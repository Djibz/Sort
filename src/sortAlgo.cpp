#include "sortAlgo.h"
#include <string>
#include <windows.h>
#include <iostream>
#include <cmath>

using namespace std;

Swap::Swap(SDL_Renderer *renderer, SDL_Window *window)
{
    r = renderer;
    w = window;
}

bool Swap::saveScreenshotBMP(std::string filepath) {
    if(image % 150 != 0)
    {
        ++image;
        return false;
    }
        
    string name = to_string(image/100);
    for(int i=name.length(); i<6; ++i)
        name = "0"+name;
    filepath += name + ".bmp";
    SDL_Surface* saveSurface = NULL;
    SDL_Surface* infoSurface = NULL;
    infoSurface = SDL_GetWindowSurface(w);
    if (infoSurface == NULL) {
        std::cerr << "Failed to create info surface from window in saveScreenshotBMP(string), SDL_GetError() - " << SDL_GetError() << "\n";
    } else {
        unsigned char * pixels = new (std::nothrow) unsigned char[infoSurface->w * infoSurface->h * infoSurface->format->BytesPerPixel];
        if (pixels == 0) {
            std::cerr << "Unable to allocate memory for screenshot pixel data buffer!\n";
            return false;
        } else {
            if (SDL_RenderReadPixels(r, &infoSurface->clip_rect, infoSurface->format->format, pixels, infoSurface->w * infoSurface->format->BytesPerPixel) != 0) {
                std::cerr << "Failed to read pixel data from SDL_Renderer object. SDL_GetError() - " << SDL_GetError() << "\n";
                delete[] pixels;
                return false;
            } else {
                saveSurface = SDL_CreateRGBSurfaceFrom(pixels, infoSurface->w, infoSurface->h, infoSurface->format->BitsPerPixel, infoSurface->w * infoSurface->format->BytesPerPixel, infoSurface->format->Rmask, infoSurface->format->Gmask, infoSurface->format->Bmask, infoSurface->format->Amask);
                if (saveSurface == NULL) {
                    std::cerr << "Couldn't create SDL_Surface from renderer pixel data. SDL_GetError() - " << SDL_GetError() << "\n";
                    delete[] pixels;
                    return false;
                }
                SDL_SaveBMP(saveSurface, filepath.c_str());
                SDL_FreeSurface(saveSurface);
                saveSurface = NULL;
            }
            delete[] pixels;
        }
        SDL_FreeSurface(infoSurface);
        infoSurface = NULL;
    }
    ++image;
    return true;
}

void Swap::assign(vector<int> *aVect, int i, int v)
{
    aVect->at(i) = v;

    SDL_Rect full;
    full.x = 0;
    full.y = 0;
    SDL_GetWindowSize(w, &(full.w), &(full.h));
    double width = (double)full.w / aVect->size();

    SDL_Rect myRect;
    myRect.x = last1 * width;
    myRect.y = 0;
    myRect.h = (aVect->at(last1) * full.h) / aVect->size();
    myRect.w = width >= 1 ? width : 1;
    myRect.y = full.h - myRect.h;
    SDL_SetRenderDrawColor(r, 255, 0, 0, 255);
    SDL_RenderFillRect(r, &myRect);
    
    myRect.h = full.h;
    myRect.y = 0;
    SDL_SetRenderDrawColor(r, 0, 0, 0, 255);
    myRect.x = i * width;
    SDL_RenderFillRect(r, &myRect);

    SDL_SetRenderDrawColor(r, 0, 255, 0, 255);
    myRect.x = i * width;
    myRect.h = (aVect->at(i) * full.h) / aVect->size();
    myRect.y = full.h - myRect.h;
    SDL_RenderFillRect(r, &myRect);


    SDL_RenderFillRect(r, &myRect);

    last1 = i;
    //SDL_Delay(delay);
    SDL_RenderPresent(r);
    //saveScreenshotBMP("E:/1.SORT/");
}

void Swap::operator()(vector<int> *aVect, int i1, int i2)
{
    int a = aVect->at(i1);
    aVect->at(i1) = aVect->at(i2);
    aVect->at(i2) = a;

    SDL_Rect full;
    full.x = 0;
    full.y = 0;
    SDL_GetWindowSize(w, &(full.w), &(full.h));
    double width = (double)full.w / aVect->size();

    SDL_Rect myRect;
    myRect.x = last1 * width;
    myRect.y = 0;
    myRect.h = (aVect->at(last1) * full.h) / aVect->size();
    myRect.w = width >= 1 ? width : 1;
    myRect.y = full.h - myRect.h;

    SDL_SetRenderDrawColor(r, 255, 0, 0, 255);
    SDL_RenderFillRect(r, &myRect);
    myRect.x = last2 * width;
    myRect.h = (aVect->at(last2) * full.h) / aVect->size();
    myRect.y = full.h - myRect.h;
    SDL_RenderFillRect(r, &myRect);

    
    myRect.h = full.h;
    myRect.y = 0;
    SDL_SetRenderDrawColor(r, 0, 0, 0, 255);
    myRect.x = i1 * width;
    SDL_RenderFillRect(r, &myRect);
    myRect.x = i2 * width;
    SDL_RenderFillRect(r, &myRect);

    SDL_SetRenderDrawColor(r, 0, 255, 0, 255);
    myRect.x = i1 * width;
    myRect.h = (aVect->at(i1) * full.h) / aVect->size();
    myRect.y = full.h - myRect.h;
    SDL_RenderFillRect(r, &myRect);
    myRect.x = i2 * width;
    myRect.h = (aVect->at(i2) * full.h) / aVect->size();
    myRect.y = full.h - myRect.h;
    SDL_RenderFillRect(r, &myRect);

    last1 = i1;
    last2 = i2;

    //SDL_Delay(delay);
    //SDL_RenderPresent(r);
    saveScreenshotBMP("E:/1.SORT/quick/");
}

void SortAlgo::setSwap(Swap *s)
{
    swap = s;
}

SortAlgo::~SortAlgo()
{
    delete swap;
}

QuickSort::QuickSort()
{

}

void QuickSort::sort(vector<int> *aVect)
{
    quickSort(aVect, 0, aVect->size()-1);
}

int QuickSort::pivot(vector<int> * aVect, int begin, int end)
{
    int hSmall = begin-1;
    for(int i=begin; i < end; ++i)
    {
        if(aVect->at(i) < aVect->at(end))
        {
            ++hSmall;
            if(i != hSmall)
            {
                (*swap)(aVect, i, hSmall);
            }
        }
    }
    if(end != hSmall+1)
    {
        (*swap)(aVect, end, hSmall+1);
    }
    return hSmall+1;
}

void QuickSort::quickSort(vector<int> *aVect, int begin, int end)
{
    int p = pivot(aVect, begin, end);
    if(p > begin)
        quickSort(aVect, begin, p-1);
    if(p < end)
        quickSort(aVect, p+1, end);
}

Radix::Radix()
{

}

void Radix::sort(vector<int> *aVect)
{
    for (int exp = 1; aVect->size() / exp > 0; exp *= 10) 
        countSort(aVect, exp);
}

void Radix::countSort(vector<int> *aVect, int exp)
{
    for(int index=0; index<aVect->size(); ++index)
    {
        bool mooved = false;
        int i = index;
        while(i != 0 && aVect->at(i) % (exp*10) < aVect->at(i-1) % (exp*10))
        {
            (*swap)(aVect, i, i-1);
            mooved = true;
            --i;
        }
        if(mooved)
            --index;
    }
}

TriFusion::TriFusion()
{

}

void TriFusion::sort(vector<int> *aVect)
{
    triFusion(aVect, 0, aVect->size()-1);
}

void TriFusion::triFusion(vector<int> *aVect, int begin, int end)
{
    if(begin != end)
    {
        int middle = (end + begin)/2;
        triFusion(aVect, begin, middle);
        triFusion(aVect, middle+1, end);
        fusion(aVect, begin, middle, end);
    }
}

void TriFusion::fusion(vector<int> *aVect, int beg1, int end1, int end2)
{
    int *table1 = new int[end1-beg1+1];
    int beg2 = end1+1;
    int compt1 = beg1;
    int compt2 = beg2;
    int i;
    for(i = beg1; i<=end1; i++)
    {
        table1[i-beg1] = aVect->at(i);
    }
    for(i = beg1; i<=end2; i++)
    {
        if(compt1 == beg2)
        {
            break;
        }
        else if(compt2 == (end2+1))
        {
            swap->assign(aVect, i, table1[compt1-beg1]);
            ++compt1;
        }
        else if (table1[compt1-beg1]< aVect->at(compt2))
        {
            swap->assign(aVect, i, table1[compt1-beg1]);
            ++compt1;
        }
        else
        {
            swap->assign(aVect, i, aVect->at(compt2));
            ++compt2;
        }
    }
    delete[] table1;
}

Gravity::Gravity()
{

}

void Gravity::sort(vector<int> *aVect)
{
    for(int j=0; j<aVect->size(); ++j)
        for(int i=aVect->size()-1; i>0; --i)
        {
            if(aVect->at(i) < aVect->at(i-1))
                (*swap)(aVect, i, i-1);
        }
}

Heap::Heap()
{

}

Heap::~Heap()
{
    for(Node *n: *nodeList)
        delete n;
    delete nodeList;
}

Node * Heap::findNode(int i)
{
    for(Node *n: *nodeList)
        if(n->index == i)
            return n;
    return nullptr;
}

void Heap::sort(vector<int> *aVect)
{
    int count = aVect->size()-1;
    createTree(aVect);
    while(root->child1 != nullptr)
    {
        while(notGood())
            for(Node *n: *nodeList)
            {
                if(n->parent != nullptr && n->parent->value < n->value)
                swapNode(n, n->parent, aVect);
            }
        Node * aSmall = findNode(count);
        swapNode(aSmall, root, aVect);
        aSmall->parent->child1 == aSmall ? aSmall->parent->child1 = nullptr : aSmall->parent->child2 = nullptr;
        aSmall->parent = nullptr;
        --count;
    }

}

void Heap::createTree(vector<int> *aVect)
{
    nodeList = new list<Node*>;
    root = new Node;
    root->index = 0;
    root->value = aVect->at(0);
    nodeList->push_back(root);

    for(int i=1; i<aVect->size(); ++i)
    {
        Node *aNode = findEmpty(root, aVect->size());
        Node *newNode = new Node;
        newNode->value = aVect->at(i);
        newNode->index = i;
        nodeList->push_back(newNode);
        newNode->parent = aNode;

        if(aNode->child1 == nullptr)
        {
            aNode->child1 = newNode;
        }
        else
        {
            aNode->child2 = newNode;
        }
    }

    for(Node *n: *nodeList)
    {
        if(n->child1 != nullptr)
            n->child1->parent = n;
        if(n->child2 != nullptr)
            n->child2->parent = n;
    }
}

Node* Heap::findEmpty(Node *n, int a)
{
    for(int i=0; i<a; ++i)
    {
        if(n->child1 == nullptr || n->child2 == nullptr)
            return n;
        Node *a = findEmpty(n->child1, i);
        Node *b = findEmpty(n->child2, i);
        if(a != nullptr)
            return a;
        if(b != nullptr)
            return b;     
    }
    return nullptr;
}

void Heap::swapNode(Node *n1, Node *n2, vector<int> *aVect)
{
    (*swap)(aVect, n1->index, n2->index);
    int v = n1->value;
    n1->value = n2->value;
    n2->value = v;
}

bool Heap::notGood()
{
    bool pSmaller = false;
    for(Node *n: *nodeList)
        if(n->parent != nullptr && n->value > n->parent->value)
            pSmaller = true;
    return pSmaller;
}