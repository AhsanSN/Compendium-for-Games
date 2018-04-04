#ifndef MAINMENU_H
#define MAINMENU_H
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include "Menu.h"
#include "Button.h"
#include "LoadGameScreen.h"

class MainMenu: public Menu
{
public:
    // Default constructor
    MainMenu(LTexture*,Point pos = Point());
    // Default destructor
    virtual ~MainMenu();
    //buttons
    enum Buttons {PLAY,LOAD,CREDITS,QUIT,BUTTONSMAX};
    //handling events for this menu
    void handleEvents(SDL_Event& e);
    // render on sceen
    void render(SDL_Renderer* gRenderer);
    // adjust according to the game resolution
    void setDimensions(int w,int h);
    //pointer to the load screen
    LoadGameScreen* loadState = NULL;
    // should the game start?
    bool gameStart;
    // start the game
    void startGame();

private:
    // for clocking for the credits render
    Uint32 firstTick = 0;
    // show the credits
    bool showCredits = false;
    //sounds for credits
    Mix_Music* creditsSound = NULL;
    //Text objects
    Text* heading;
    LTexture credits;
    //background rect
    SDL_Rect bgRect;
    // for scrolling the credits texture;
    float scrollingOffset;

};

#endif // MAINMENU_H
