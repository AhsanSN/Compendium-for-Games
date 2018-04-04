#ifndef GAMEOVER_H
#define GAMEOVER_H

#include "Menu.h"
#include "Button.h"
#include "LTexture.h"
#include "MainMenu.h"


class GameOver : public Menu
{
public:
    /** Default constructor */
    GameOver(LTexture* image,Point pos = Point());
    /** Default destructor */
    virtual ~GameOver() {};
    //buttons
    enum Buttons {CONTINUE,QUIT,BUTTONSMAX};
    //for the events. name is pretty self explanatory
    void handleEvents(SDL_Event& e);
    // main menu pointer for quitting
    MainMenu* mainMenu = NULL;
    // for resetting if quit
    bool resetGame;
    // for the continue button
    bool gameRun;
    //render on screen. nuff said =P
    void render(SDL_Renderer* gRenderer);
    //adjust according to the game resolution
    void setDimensions(int _SCREEN_WIDTH,int _SCREEN_HEIGHT);

protected:

private:
    //Texts that are going to be rendered.
    Text* gameOverText;
};

#endif // GAMEOVER_H
