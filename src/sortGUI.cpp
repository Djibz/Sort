#include "sortGUI.h"

SortGUI::SortGUI(int width, int height)
    : windowWidth(width), windowHeight(height)
{
    SDL_Init(SDL_INIT_VIDEO);
    itsWindow = SDL_CreateWindow("SortGUI",
                                SDL_WINDOWPOS_UNDEFINED,
                                SDL_WINDOWPOS_UNDEFINED,
                                width,
                                height,
                                SDL_WINDOW_SHOWN);

    itsRenderer = SDL_CreateRenderer(itsWindow, -1, SDL_RENDERER_ACCELERATED);
}

SortGUI::~SortGUI()
{
    SDL_DestroyWindow(itsWindow);
    SDL_Quit();
    delete itsVector;
}

void SortGUI::renderAll()
{
    SDL_Rect full;
    full.x = 0;
    full.y = 0;
    full.w = windowWidth;
    full.h = windowHeight;
    SDL_SetRenderDrawColor(itsRenderer, 0, 0, 0, 255);
    SDL_RenderFillRect(itsRenderer, &full);
    SDL_SetRenderDrawColor(itsRenderer, 255, 0, 0, 255);
    double width = (double)windowWidth / itsVector->size();
    for(int i=0; i<itsVector->size(); ++i)
    {
        SDL_Rect aRect;
        aRect.x = i * width;
        aRect.w = width >= 1 ? width : 1;
        aRect.h = (itsVector->at(i) * windowHeight) / itsVector->size();
        aRect.y = windowHeight - aRect.h;
        /*if(index == i || index2 == i)
            SDL_SetRenderDrawColor(r, 0, 255, 0, 255);
        else
            SDL_SetRenderDrawColor(r, 255, 0, 0, 255);*/
        SDL_RenderFillRect(itsRenderer, &aRect);
    }
    //SDL_Delay(50);
    SDL_RenderPresent(itsRenderer);
}

void SortGUI::initVect(int size)
{
    if(itsVector != nullptr)
        delete itsVector;
    itsVector = new vector<int>;
    for(int i=0; i<size; ++i)
        itsVector->push_back(i);
    random_shuffle(itsVector->begin(), itsVector->end());
}

void SortGUI::setAlgo(SortAlgo *algo)
{
    itsAlgo = algo;
    itsAlgo->setSwap(new Swap(itsRenderer, itsWindow));
}

void SortGUI::process()
{
    renderAll();
    itsAlgo->sort(itsVector);
}

bool SortGUI::saveScreenshotBMP(std::string filepath) {
    SDL_Surface* saveSurface = NULL;
    SDL_Surface* infoSurface = NULL;
    infoSurface = SDL_GetWindowSurface(itsWindow);
    if (infoSurface == NULL) {
        std::cerr << "Failed to create info surface from window in saveScreenshotBMP(string), SDL_GetError() - " << SDL_GetError() << "\n";
    } else {
        unsigned char * pixels = new (std::nothrow) unsigned char[infoSurface->w * infoSurface->h * infoSurface->format->BytesPerPixel];
        if (pixels == 0) {
            std::cerr << "Unable to allocate memory for screenshot pixel data buffer!\n";
            return false;
        } else {
            if (SDL_RenderReadPixels(itsRenderer, &infoSurface->clip_rect, infoSurface->format->format, pixels, infoSurface->w * infoSurface->format->BytesPerPixel) != 0) {
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

void SortGUI::setTitle(string aTitle)
{
    SDL_SetWindowTitle(itsWindow, aTitle.c_str());
}