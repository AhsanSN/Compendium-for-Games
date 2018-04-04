#include "MobileBrickX.h"

MobileBrickX::MobileBrickX(LTexture* image,Board* gameBoard,Point pos):MobileBrick(image,gameBoard,pos)
{
    dx=LEFT;//start default direction as LEFT
    type=MOBILEBRICKX;
}

void MobileBrickX::move(List* worldEnt)//instead of passing the entire list, pass two entities, prev and for bricks
{
    if(!alive) //Don't move the brick if it is not alive
        return;

    SDL_Rect boardBounds=gameBoard->getBounds();//get board bounds
    //switch movement dir of brick if it goes out of he board or collides with any other brick in the list

    if (dx==RIGHT)
    {
        if (boardBounds.x + boardBounds.w > this->pos.x + this->width + 2 )//moves the brick inside the bounds of the board
        {

            int collisionType=checkCollisions(worldEnt);//checking collision type

            //if collision detected, reverse brick movement direction, else move it with its set speed

            if (collisionType!=NONE)
            {
                reverseDir();
            }
            else
            {
                pos.x += speed;//moving right
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
        if (boardBounds.x + 2 < pos.x)//keeps the brick inside the bounds of the board
        {
            //if collision detected, reverse brick movement direction, else move it with its set speed

            int collisionType=checkCollisions(worldEnt);

            if(collisionType!=NONE)
            {
                reverseDir();
            }
            else
            {
                pos.x -= speed; //moving left
            }

            setBounds();//update bounding rectangle
        }
        else
        {
            reverseDir();
        }
    }
}



