#include "SteelBrick.h"

SteelBrick::SteelBrick(LTexture* image,Board* gameBoard,Point pos):Brick(image,gameBoard,pos)
{
    brickHealth=10; //unique health, won't be effected by normal ball
    color=GRAY; //assigning unique color
    type=STEELBRICK;
}

void SteelBrick::render(SDL_Renderer* gRenderer)
{

    static int delay=0;//variable for controlling delay between sprite loading
    //If brick is alive, render appropriate frame corresponding to the damage

    if(alive)
    {
        spriteSheetTexture->render(pos.x,pos.y,&spriteClips[color][INTACT],0.0, NULL, SDL_FLIP_NONE, gRenderer);
    }

    //If not alive, after each call the static int delay is incremented, and explosion sprites are rendered every time delay%5==0

    if(!alive)
    {
        if(delay%5==0)
        {
            if(expFrame++ > 2)
            {
                delay=0;
                expFrame=3;
            }
        }
        if(expFrame==0) expFrame++;
        if(expFrame==3) return;
        else
        {
            delay++;
            spriteSheetTexture->render( pos.x, pos.y, &spriteClips[color][expFrame+2], 0.0, NULL, SDL_FLIP_VERTICAL, gRenderer );//+2 for going to the appropriate frame (the explosion of the bricks), expFrame will either be 1 or 2
        }
    }
}

