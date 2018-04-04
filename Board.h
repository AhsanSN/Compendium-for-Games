#ifndef BOARD_H
#define BOARD_H

#include "Entity.h"


class Board : public Entity
{
public:
    Board(LTexture*,Point=Point());

    ~Board();

    void render(SDL_Renderer*);

    void setDimensions(int,int);

    void playDayMusic();

    void playNightMusic();

    void sparkleOn();

    friend class FileIO;

    bool isDay();
private:
    SDL_Rect spriteClips[4];    //Used to store the sprite clips for the board

    int SCREEN_WIDTH;

    int SCREEN_HEIGHT;

    const int DAYTIME = 45;         //time in seconds after which day/night will switch

    LTexture* gSpriteSheetTexture;

    SDL_Rect sparkleSpriteClips[8];          //To store the sparkle sprites

    int sparkleWidth;       //Dimensions for each sparkle

    int sparkleHeight;

    int sparklePos;         //The position of the sparkle strip

    bool powerCollect;      //Flag used to activate the sparkle strip when a powerUp is collected

    //Texture for background and the colour modulation related attributes
    LTexture bgTexture;     //The background image texture

    int r,g,b;                  //Ints to store color modulation info

    SDL_Rect bgRect;

    bool dayChange=0;           //Flag to check if the day change process should be initialized

    bool day=1;                 //Flag to check if it is day or night

    float scrollingOffset = 0;      // The float amount used to scroll the background


    //Game Music, day
    Mix_Music* mainDay = NULL;
    //Game Music, night
    Mix_Music* mainNight = NULL;
};

#endif // BOARD_H
