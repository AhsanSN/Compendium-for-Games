#include "MobileBrick.h"

MobileBrick::MobileBrick(LTexture* image,Board* gameBoard, Point pos):OneHitBrick(image,gameBoard,pos)
{
    speed=this->width/25.0f;//setting brick movement speed
}

void MobileBrick::reverseDir() //will simply reverse the current direction of the brick
{
    if (dx==LEFT)
    {
        dx=RIGHT;
    }
    else if (dx==RIGHT)
    {
        dx=LEFT;
    }
    if (dy==UP)
    {
        dy=DOWN;
    }
    else if (dy==DOWN)
    {
        dy = UP;
    }
}
int MobileBrick::checkCollisions(List* worldEnt)
{

    int ind = worldEnt->getEntInd(this);// ind has address of the current mobile brick in the list

    Node* tmp = worldEnt->getNodeAtInd(0);//tmp starts from the start of the list

    if (ind == -1) return -1; //if current brick is not found in the list, return -1

    while(tmp)
    {
        if(tmp->ent != this)//To skip checking for collision with itself
        {
            SDL_Rect prevBrick=tmp->ent->getBounds();
            if(dx==LEFT) //if the mobile brick is moving to the left and collides, RIGHT collision detected
            {
                prevBrick.x += 2;//for correcting offset for better surrounded collisions

                if(SDL_HasIntersection(&(bounds),&(prevBrick)))
                {
                    return RIGHT;
                }
            }

            if(dx==RIGHT) //if the mobile brick is moving to the right and collides, LEFT collision detected
            {
                prevBrick.x -=2;//for correcting offset for better surrounded collisions

                if(SDL_HasIntersection(&(bounds),&(prevBrick)))
                {
                    return LEFT;
                }
            }
            if(dy==UP) //if the mobile brick is moving up and collides, DOWN collision detected
            {
                prevBrick.y+=2;//for correcting offset for better surrounded collisions

                if(SDL_HasIntersection(&(bounds),&(prevBrick)))
                {
                    return DOWN;
                }
            }
            if (dy==DOWN) //if the mobile brick is moving down and collides, UP collision detected
            {
                prevBrick.y-=2;//for correcting offset for better surrounded collisions

                if(SDL_HasIntersection(&(bounds),&(prevBrick)))
                {
                    return UP;
                }
            }

        }
        tmp=tmp->next;
    }
    return NONE;
}
