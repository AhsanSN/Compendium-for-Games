#include "BossBrick.h"

BossBrick::BossBrick(LTexture* image,Board* gameBoard,Point pos):MobileBrick(image,gameBoard,pos),MobileBrickX(image,gameBoard,pos),MobileBrickY(image,gameBoard,pos)
{
    type=BOSSBRICK;
    brickHealth=3;//setting brick Health
    color=GREEN;//setting unique color
}

void BossBrick::move(List* worldEnt)//The brick follows different movement patterns depending on its current damage
{
    static Uint32 start=SDL_GetTicks();

    if(brickDamage==0)//If 0 hit, brick traces out a square pattern (either UP/DOWN or LEFT/RIGHT), switches each 3 seconds
    {
        if(SDL_GetTicks()-start < 3000)
        {
            MobileBrickX::move(worldEnt);
        }
        else
        {
            MobileBrickY::move(worldEnt);
            if(SDL_GetTicks() - start > 6000)
                start=SDL_GetTicks();
        }
    }
    else if(brickDamage==1)//if 1 hit, follows a zig zag Y pattern, switches each 2 seconds
    {
        if(SDL_GetTicks()-start < 2000)
        {
            MobileBrickX::move(worldEnt);
            MobileBrickY::move(worldEnt);
        }
        else
        {
            MobileBrickY::move(worldEnt);
            if(SDL_GetTicks() - start > 4000)
                start=SDL_GetTicks();
        }
    }
    else if(brickDamage==2)//if 2 hit, follows a zig zag X pattern, switches every 1.5 seconds
    {
        if(SDL_GetTicks()-start < 1500)
        {
            MobileBrickX::move(worldEnt);
            MobileBrickY::move(worldEnt);
        }
        else
        {
            MobileBrickX::move(worldEnt);
            if(SDL_GetTicks() - start > 3000)
                start=SDL_GetTicks();
        }
    }
}

void BossBrick::render(SDL_Renderer* gRenderer)
{
    static int delay=0;//variable for controlling delay between sprite loading
    //If brick is alive, render appropriate frame corresponding to the damage
    if(alive)
    {
        if(brickDamage==0)
        {
            spriteSheetTexture->render(pos.x,pos.y,&spriteClips[color][INTACT],0.0, NULL, SDL_FLIP_NONE, gRenderer);
        }
        else if(brickDamage==1)
        {
            spriteSheetTexture->render(pos.x,pos.y,&spriteClips[color][SLIGHTCRACK],0.0, NULL, SDL_FLIP_NONE, gRenderer);
        }
        else if(brickDamage==2)
        {
            spriteSheetTexture->render(pos.x,pos.y,&spriteClips[color][HEAVCRACK],0.0, NULL, SDL_FLIP_NONE, gRenderer);
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
        if(expFrame==3) return;
        else
        {
            delay++;
            spriteSheetTexture->render( pos.x, pos.y, &spriteClips[color][expFrame+2], 0.0, NULL, SDL_FLIP_NONE, gRenderer );//+2 for going to the appropriate frame (the explosion of the bricks), expFrame will either be 1 or 2
        }
    }
}

