#ifndef GAMECOMPLETESCREEN_H
#define GAMECOMPLETESCREEN_H

#include "SDL.h"
#include "SDL_image.h"
#include "Menu.h"
#include "Text.h"
#include <sstream>
#include <cstdlib>

class GameCompleteScreen : public Menu
{
public:
    /** Default constructor */
    GameCompleteScreen(LTexture* image,Point pos = Point());
    /** Default destructor */
    virtual ~GameCompleteScreen();
    //Render the LevelComplete Screen o
    void render(SDL_Renderer* gRenderer);
    //Handles the events for this screen
    void handleEvents(SDL_Event& e);
    //Set the screen elements according to the game resolution
    void setDimensions(int SCREEN_WIDTH,int SCREEN_HEIGHT);
    //Buttons for this screen
    enum Buttons {NEXT,QUIT,BUTTONSMAX};
    //Variable for the options. Proceed becomes zero if continue is selected
    int proceed = -1;
    //Pointer to the mainMenu for quitting
    Menu* mainMenu = NULL;
    //SDL_Texture for the black tinted transparent background
    SDL_Texture* auxtexture = NULL;
    //Variable for resettting the game
    bool resetGame;
    //Score Display
    void setScore(int Score);
    //Bonus Score Display
    void setBonus(int Score);
    //Total Score Display
    void setTotalScore(int Score);
    //For converting score int to str within the methods
    string getScoreStr(int Score,string scoretype);

private:
    //Screen Sounds
    Mix_Chunk* levComplete = NULL;
    Mix_Chunk* levStart = NULL;
    //All the Texts that are to be rendered
    Text* heading = NULL;
    Text* scoreHeading = NULL;
    Text* scoreText = NULL;
    Text* bonusScore = NULL;
    Text* totalScore = NULL;
};

#endif // GAMECOMPLETESCREEN_H
