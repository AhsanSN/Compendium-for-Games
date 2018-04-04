#include "Screens.h"

using namespace std;

Screen::Screen(LTexture* texture)
{
    this->screenTexture = texture;
    imageRect = {0,0,screenTexture->getWidth(),screenTexture->getHeight()};
    outputRect = {0,0,SCREEN_WIDTH,SCREEN_HEIGHT};
    show = true;
    hide = false;
    stay = false;
    mainMenu = NULL;
    nextScreen = NULL;
}

Screen::~Screen()
{
    mainMenu = NULL;
    nextScreen = NULL;
}

bool Screen::ScreenIn(long int frames,SDL_Renderer* gRenderer)
{
    if ((frames*2)%256 >= 252)
    {
        return true;
    }
    screenTexture->setAlpha((frames*2)%256);
    screenTexture->render(0,0,&imageRect,0.0,NULL,SDL_FLIP_NONE,gRenderer,1,&outputRect);
    return false;
}

bool Screen::ScreenOut(long int frames,SDL_Renderer* gRenderer)
{
    if (255 - (frames*2)%256 <= 2)
    {
        return true;
    }
    screenTexture->setAlpha(255 -(frames*2)%256);
    screenTexture->render(0,0,&imageRect,0.0,NULL,SDL_FLIP_NONE,gRenderer,1,&outputRect);
    return false;
}

void Screen::ScreenStay(SDL_Renderer* gRenderer)
{
    screenTexture->setAlpha(255);
    screenTexture->render(0,0,&imageRect,0.0,NULL,SDL_FLIP_NONE,gRenderer,1,&outputRect);
}

void Screen::setDimensions(int width,int height)
{
    this->SCREEN_HEIGHT = height;
    this->SCREEN_WIDTH = width;
    outputRect = {0,0,SCREEN_WIDTH,SCREEN_HEIGHT};
}

bool Screen::getAlive()
{
    return alive;
}

void Screen::setAlive(bool isAlive)
{
    show = true;
    hide = false;
    stay = false;
    this->alive = isAlive;
}


void Screen::setDelay(int timeDelay)
{
    this->delay = timeDelay;
}

void Screen::render(SDL_Renderer* gRenderer)
{
    frames++;
    if (show)
    {
        stay = ScreenIn(frames,gRenderer);
        if (stay)
        {
            splTick = SDL_GetTicks();
        }
    }
    if (stay)
    {
        show = false;
        ScreenStay(gRenderer);
        if ((SDL_GetTicks()-splTick)/1000 >= delay && (frames*2)%256 == 0)
        {
            hide = true;
            stay = false;
        }
    }
    if (hide)
    {
        if (ScreenOut(frames,gRenderer))
        {
            alive = false;
            if (mainMenu) mainMenu->setAlive(true);
            else if (nextScreen) nextScreen->setAlive(true);
            frames = 0;
        }
    }
}
