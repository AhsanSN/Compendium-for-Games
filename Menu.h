#ifndef MENU_H
#define MENU_H

#include "Entity.h"
#include "Button.h"
#include <vector>

class Menu : public Entity
{
public:
    /** Default constructor */
    Menu(LTexture* image,Point pos = Point());
    /** Default destructor */
    virtual ~Menu();
    //virtual functions, each described in the child classes
    virtual void render(SDL_Renderer* gRenderer);
    virtual void setDimensions(int,int);
    virtual void handleEvents(SDL_Event& e);
    virtual void startGame() {};
    int getOption();
    void setOption(int opt);
    SDL_Rect outputRect;
    //Menu music
    Mix_Music* menuMus = NULL;

protected:
    //vector of buttons different for each type of menu
    vector <Button> buttons;
    int option;
    int SCREEN_HEIGHT, SCREEN_WIDTH;
    int MAXBUTTONS = 4;
    SDL_Rect menuSprite;
    Mix_Chunk* selectSound = NULL;
};

#endif // MENU_H
