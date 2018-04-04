#ifndef BOSSBRICK_H
#define BOSSBRICK_H
#include "MobileBrickX.h"
#include "MobileBrickY.h"

//Specialized Brick. Multiply inheriting from the MobileBricks X and Y. Can move in all directions.
//The reason for virtual inheritance in the two parent classes was the diamond inheritance problem.
//Since both the parents have a common ancestor, normal inheritance gets ambiguous as it keeps two copies.
//Hence virtual inheritance is used to tackle this issue.

class BossBrick:public MobileBrickX,public MobileBrickY
{
public:
    BossBrick(LTexture*,Board*,Point);
    void move(List*);
    void render(SDL_Renderer*);


};

#endif // BOSSBRICK_H
