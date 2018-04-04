#include "MobileBrickY.h"

MobileBrickY::MobileBrickY(LTexture* image,Board* gameBoard,Point pos):MobileBrick(image,gameBoard,pos)
{
    dy=UP;//start default direction as UP
    type=MOBILEBRICKY;
}

void MobileBrickY::move(List* worldEnt)//instead of passing the entire list, pass two entities, prev and for bricks
{
    if(!alive) //Don't move the brick if it is not alive
        return;

    SDL_Rect boardBounds=gameBoard->getBounds();//get board bounds
    //switch movement dir of brick if it goes out of he board or collides with any other brick in the list

    if (dy==UP)
    {
        if (boardBounds.y + 2 < this->pos.y )//moves the brick inside the bounds of the board//moves the brick inside the bounds of the board
        {
            int collisionType=checkCollisions(worldEnt);//checking collision type

            //if collision detected, reverse brick movement direction, else move it with its set speed

            if (collisionType==DOWN)
            {
                reverseDir();
            }
            else
            {
                pos.y -= speed;//moving UP
            }
            setBounds();//update bounding rectangle
        }
        else
        {
            reverseDir();
        }
    }
    else
    {
        if (boardBounds.y + boardBounds.h/2 > pos.y)//keeps the brick inside the bounds of the board
        {
            int collisionType=checkCollisions(worldEnt);//checking collision type

            //if collision detected, reverse brick movement direction, else move it with its set speed

            if(collisionType==UP)
            {
                reverseDir();
            }
            else
            {
                pos.y += speed;
            }
            setBounds();//update bounding rectangle
        }
        else
        {
            reverseDir();
        }
    }
}


