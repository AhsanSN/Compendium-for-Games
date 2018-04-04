#ifndef TWOHITBRICK_H
#define TWOHITBRICK_H
#include "Brick.h"

//Specialized brick, dies in two hits

class TwoHitBrick:public Brick
{
public:
    TwoHitBrick(LTexture*,Board*,Point);
    virtual void render(SDL_Renderer*);
};
#endif // TWOHITBRICK_H
