#include <SDL2/SDL.h>
#include <windows.h>
#include <stdio.h>
#include <iostream>
#include <ctime>
#include <vector>
#include <random>
#include <algorithm>
#include <string>
#include "sortGUI.h"

using namespace std;


int main(int argc, char** argv)
{
    srand(time(0));
    ::ShowWindow(::GetConsoleWindow(), SW_HIDE);
    SortGUI a(1000, 500);

    /*a.initVect(500);
    a.setTitle("Heap Sort - 500");
    a.setAlgo(new Heap());
    a.process();
    a.renderAll();

    a.initVect(500);
    a.setTitle("Gravity Sort - 500");
    a.setAlgo(new Gravity());
    a.process();
    a.renderAll();*/

    a.initVect(10000);
    a.setTitle("Quick Sort - 10.000");
    a.setAlgo(new QuickSort());
    a.process();
    a.renderAll();
    
    /*a.initVect(10000);
    a.setTitle("Merge Sort - 10.000");
    a.setAlgo(new TriFusion());
    a.process();
    a.renderAll();

    a.initVect(500);
    a.setTitle("Radix Sort (LSD)(10) - 500");
    a.setAlgo(new Radix());
    a.process();
    a.renderAll();*/

    /*SortGUI aGUI(1500, 500);
    aGUI.initVect(500);
    aGUI.renderAll();
    aGUI.setAlgo(new Radix());
    aGUI.process();
    a.renderAll();*/

    return 0;
}