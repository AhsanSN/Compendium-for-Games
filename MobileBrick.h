#ifndef MOBILEBRICK_H
#define MOBILEBRICK_H
#include "OneHitBrick.h"
#include "List.h"

class MobileBrick: public OneHitBrick//Abstract Class, Two direct childs are x and y mobile bricks, can move in x and y directions respectively
{
public:
    MobileBrick(LTexture*,Board*,Point);
    enum DIRECTIONS {NONE,LEFT,RIGHT,UP,DOWN};//enumeration for movement directions
    virtual void move(List* = NULL)=0;//Will be redefined in child classes
    void reverseDir();//will simply reverse the current direction of the brick
    int checkCollisions(List*);//Used for checking brick-brick collisions
};

#endif // MOBILEBRICK_H
