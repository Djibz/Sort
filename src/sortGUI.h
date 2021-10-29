#ifndef SORTGUI_H
#define SORTGUI_H

#include <SDL2/SDL.h>
#include <windows.h>
#include <stdio.h>
#include <iostream>
#include <ctime>
#include <vector>
#include <random>
#include <algorithm>
#include <string>
#include "sortAlgo.h"

using namespace std;


class SortGUI
{
private:
    SDL_Window *itsWindow = nullptr;
    SDL_Renderer  *itsRenderer;
    vector<int> *itsVector = nullptr;
    int windowWidth;
    int windowHeight;
    SortAlgo * itsAlgo;
public:
    SortGUI(int width, int height);
    ~SortGUI();
    void renderAll();
    void initVect(int size);
    void setAlgo(SortAlgo *algo);
    void process();
    bool saveScreenshotBMP(std::string filepath, SDL_Window* SDLWindow, SDL_Renderer* SDLRenderer);
};

#endif