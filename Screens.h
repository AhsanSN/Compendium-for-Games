#ifndef SCREENS_H
#define SCREENS_H

#include "LTexture.h"
#include "MainMenu.h"

class Screen
{
public:
    /** Default constructor */
    Screen(LTexture* texture);
    //fade in
    bool ScreenIn(long int frame,SDL_Renderer* gRenderer);
    //fade out
    bool ScreenOut(long int frame,SDL_Renderer* gRenderer);
    //stay on the screen
    void ScreenStay(SDL_Renderer* gRenderer);
    //render on screen
    void render(SDL_Renderer* gRenderer);
    //gives the alive var
    bool getAlive();
    //set the alive variable
    void setAlive(bool isAlive);
    //posiition the screen elements according to the resolution
    void setDimensions(int width,int height);
    /** Default destructor */
    virtual ~Screen();
    //set the time for which the splash will stay on screen
    void setDelay(int timeDelay);
    //pointers to menu and the next screen
    MainMenu* mainMenu = NULL;
    Screen* nextScreen = NULL;
    //for clocking the fade in and fade out
    long int frames = 0;


protected:
    //for rendering the picture
    LTexture* screenTexture;
    //local dimensions
    int SCREEN_WIDTH = 1024;
    int SCREEN_HEIGHT = 768;
    //for rendering
    bool show;
    bool hide;
    bool stay;
    bool alive;
    //for fade in and fade out
    Uint32 splTick = 0;

private:
    //input Rect
    SDL_Rect imageRect;
    //output Rect
    SDL_Rect outputRect;
    // the delay for the splash
    unsigned int delay = 1;
};

#endif // SCREENS_H
