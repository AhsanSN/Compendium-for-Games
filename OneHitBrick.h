#ifndef ONEHITBRICK_H
#define ONEHITBRICK_H
#include "Brick.h"

class OneHitBrick:public Brick//Specialized class
{
public:
    OneHitBrick(LTexture*,Board*,Point);
    void render(SDL_Renderer*);
};

#endif // ONEHITBRICK_H
