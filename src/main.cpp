#include <SDL2/SDL.h>
#include <windows.h>
#include <stdio.h>
#include <iostream>
#include <ctime>
#include <vector>
#include <random>
#include <algorithm>
#include <string>

using namespace std;

CONST unsigned int WIDTH = 1000;
CONST unsigned int HEIGHT = 500;
int image = 0;
SDL_Window* pWindow = NULL;

bool saveScreenshotBMP(std::string filepath, SDL_Window* SDLWindow, SDL_Renderer* SDLRenderer) {
    SDL_Surface* saveSurface = NULL;
    SDL_Surface* infoSurface = NULL;
    infoSurface = SDL_GetWindowSurface(SDLWindow);
    if (infoSurface == NULL) {
        std::cerr << "Failed to create info surface from window in saveScreenshotBMP(string), SDL_GetError() - " << SDL_GetError() << "\n";
    } else {
        unsigned char * pixels = new (std::nothrow) unsigned char[infoSurface->w * infoSurface->h * infoSurface->format->BytesPerPixel];
        if (pixels == 0) {
            std::cerr << "Unable to allocate memory for screenshot pixel data buffer!\n";
            return false;
        } else {
            if (SDL_RenderReadPixels(SDLRenderer, &infoSurface->clip_rect, infoSurface->format->format, pixels, infoSurface->w * infoSurface->format->BytesPerPixel) != 0) {
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
    return true;
}

void renderAll(vector<int> * aVect, SDL_Renderer * r)
{
    SDL_Rect full;
    full.x = 0;
    full.y = 0;
    full.w = WIDTH;
    full.h = HEIGHT;
    SDL_SetRenderDrawColor(r, 0, 0, 0, 255);
    SDL_RenderFillRect(r, &full);
    SDL_SetRenderDrawColor(r, 255, 0, 0, 255);
    int width = WIDTH / aVect->size();
    for(int i=0; i<aVect->size(); ++i)
    {
        SDL_Rect aRect;
        aRect.x = i * width;
        aRect.y = 0;
        aRect.w = width;
        aRect.h = (aVect->at(i) * HEIGHT) / aVect->size();
        SDL_RenderFillRect(r, &aRect);
    }
    //SDL_Delay(50);
    SDL_RenderPresent(r);

    string iName = "images/" + to_string(image) + ".bmp";
    //saveScreenshotBMP(iName, pWindow, r);
    ++image;

}

int pivot(vector<int> * aVect, int begin, int end, SDL_Renderer * r)
{
    int small = begin-1;
    for(int i=begin; i < end; ++i)
    {
        if(aVect->at(i) < aVect->at(end))
        {
            ++small;
            if(i != small)
            {
                swap(aVect->at(i), aVect->at(small));
                renderAll(aVect, r);
            }
        }
    }
    if(end != small+1)
    {
        swap(aVect->at(end), aVect->at(small+1));
        renderAll(aVect, r);
    }
    return small+1;
}

void quickSort(vector<int> * aVect, SDL_Renderer * r, int begin=0, int end=99)
{
    int p = pivot(aVect, begin, end, r);
    if(p > begin)
        quickSort(aVect, r, begin, p-1);
    if(p < end)
        quickSort(aVect, r, p+1, end);
}

int main(int argc, char** argv)
{
    srand(time(0));
    vector<int> * aVect = new vector<int>;
    for(int i=0; i<1000; ++i)
        aVect->push_back(i);
    random_shuffle(aVect->begin(), aVect->end());

    /* Initialisation simple */
    if (SDL_Init(SDL_INIT_VIDEO) != 0 )
    {
        fprintf(stdout,"Échec de l'initialisation de la SDL (%s)\n",SDL_GetError());
        return -1;
    }

    {
        /* Création de la fenêtre */
        
        pWindow = SDL_CreateWindow("Ma première application SDL2",SDL_WINDOWPOS_UNDEFINED,
                                                                  SDL_WINDOWPOS_UNDEFINED,
                                                                  WIDTH,
                                                                  HEIGHT,
                                                                  SDL_WINDOW_SHOWN);

        SDL_Renderer * renderer =  SDL_CreateRenderer(pWindow, -1, SDL_RENDERER_ACCELERATED);

        SDL_Rect aRect;
        aRect.x = 0;
        aRect.y = 0;
        aRect.w = 32;
        aRect.h = 32;
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        //SDL_RenderFillRect(renderer, &aRect);
        
        quickSort(aVect, renderer, 0, aVect->size()-1);

        if( pWindow )
        {
            //SDL_Delay(3000); /* Attendre trois secondes, que l'utilisateur voit la fenêtre */

            SDL_DestroyWindow(pWindow);
        }
        else
        {
            fprintf(stderr,"Erreur de création de la fenêtre: %s\n",SDL_GetError());
        }
    }

    SDL_Quit();

    delete aVect;
    return 0;
}