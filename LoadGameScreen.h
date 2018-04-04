#ifndef LoadGameSCREEN_H
#define LoadGameSCREEN_H

#include "Menu.h"
#include <vector>
#include "Button.h"

class Game;

class LoadGameScreen : public Menu
{
public:
    /** Default constructor */
    LoadGameScreen(LTexture* image,Point pos = Point());
    /** Default destructor */
    virtual ~LoadGameScreen()
    {
        parentMenu = NULL;
        delete heading;
        game = NULL;
    };
    //buttons
    enum Buttons {STATE1,STATE2,STATE3,CANCEL,BUTTONSMAX};
    // modes for saving loading
    enum modes {SAVE,LOAD};
    //handle the events for this menu
    void handleEvents(SDL_Event& e);
    //set the mode for saving loading
    void setMode(int Mode);
    //render on screen
    void render(SDL_Renderer*);
    //pointer to parent menu
    Menu* parentMenu;
    //text for the heading
    Text* heading;
    //pointer to main game
    void setGame(Game*);

protected:

private:
    Game* game;
    int mode = -1;
};

#endif // LoadGameSCREEN_H
