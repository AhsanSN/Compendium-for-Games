#ifndef PauseMenu_H
#define PauseMenu_H

#include <vector>
#include "Point.h"
#include "Button.h"
#include "LTexture.h"
#include "LoadGameScreen.h"
#include "MainMenu.h"

class PauseMenu : public Menu
{
public:
    /** Default constructor */
    PauseMenu(LTexture* image,Point pos = Point());
    /** Default destructor */
    virtual ~PauseMenu() {};
    // buttons
    enum Buttons {RESUME,SAVE,QUIT,BUTTONSMAX};
    // handle the events
    void handleEvents(SDL_Event& e);
    // main menu pointer ofr quitting
    MainMenu* mMenu = NULL;
    //pointer to savegame screen
    LoadGameScreen* saveState = NULL;
    //render the menu on screen
    void render(SDL_Renderer*);
    //reset the game for quitting
    bool resetGame = false;
    // run the game
    bool gameRun;

protected:

private:
    //text objects
    Text* heading;
    //ptr to the main game
    Game* game;
};

#endif // PauseMenu_H
