#include "OneHitBrick.h"

OneHitBrick::OneHitBrick(LTexture* image,Board* gameBoard,Point pos):Brick(image,gameBoard,pos)
{
    brickHealth=1;
    type=ONEHITBRICK;
}

void OneHitBrick::render(SDL_Renderer* gRenderer)
{
    static int delay=0;//variable for controlling delay between sprite loading
    //If brick is alive, render intact frame
    if(alive)
    {
        if(brickDamage==0)
        {
            spriteSheetTexture->render(pos.x,pos.y,&spriteClips[color][INTACT],0.0, NULL, SDL_FLIP_NONE, gRenderer);
        }
        else
        {
            alive=0;
        }
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
        if(expFrame==3) return;//brick explosion has been rendered, no need to render again
        else
        {
            delay++;
            spriteSheetTexture->render( pos.x, pos.y, &spriteClips[color][expFrame+2], 0.0, NULL, SDL_FLIP_NONE, gRenderer );//+2 for going to the appropriate frame (the explosion of the bricks), expFrame will either be 1 or 2
        }
    }
}



