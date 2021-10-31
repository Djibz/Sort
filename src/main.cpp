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
    SortGUI a(1000, 800);

    a.initVect(304);
    a.setTitle("Heap Sort");
    a.setAlgo(new Heap());
    a.process();
    a.renderAll();

    a.initVect(500);
    a.setTitle("Gravity");
    a.setAlgo(new Gravity());
    a.process();
    a.renderAll();

    a.initVect(10000);
    a.setAlgo(new QuickSort());
    a.process();
    a.renderAll();
    
    a.initVect(10000);
    a.renderAll();
    a.setAlgo(new TriFusion());
    a.process();
    a.renderAll();

    SortGUI aGUI(1500, 500);
    aGUI.initVect(500);
    aGUI.renderAll();
    aGUI.setAlgo(new Radix());
    aGUI.process();
    a.renderAll();

    return 0;
}