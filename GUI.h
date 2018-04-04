#ifndef GUI_H
#define GUI_H

#include "Entity.h"
#include "Text.h"
#include <string>
#include <sstream>

class GUI : public Entity
{
public:
    /** Default constructor */
    GUI(LTexture* image,Point pos = Point());
    /** Default destructor */
    virtual ~GUI();
    //set the game time
    void setTime(Uint32& initialTicks);
    // set the game score
    void setScore(int& score);
    //set the game lives
    void setLives(int& lives);
    // set the positions of the GUI elements
    void setDimensions(int x,int y);
    //render on screen
    void render(SDL_Renderer* gRenderer);
    //toggle the color of the text
    void toggleColor();
    // set the powerups on the gui
    void setPowerUp(int ball,int pad,int padSize,bool multiBall);

protected:

private:
    // time
    Uint32 time = 0;
    //current powerups
    int currentPowerup[4]= {0,0,0,0};
    //text objects
    Text* scoreText = NULL;
    Text* timeText = NULL;
    Text* livesText = NULL;
    Text* timeHeading = NULL;
    Text* powerupText = NULL;
    //for the icons of the powerups
    SDL_Rect ballPowerupIcons[4];
    SDL_Rect padPowerupIcons[4];
    SDL_Rect padSizeIcon[2];
    SDL_Rect multiBall;
    //background rect
    SDL_Rect GUIBg;
    int SCREEN_HEIGHT;
    int SCREEN_WIDTH;

};

#endif // GUI_H
