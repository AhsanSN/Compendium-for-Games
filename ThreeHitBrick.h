#ifndef THREEHITBRICK_H
#define THREEHITBRICK_H
#include "Brick.h"
class ThreeHitBrick:public Brick
{
public:
    ThreeHitBrick(LTexture*,Board*,Point);
    void render(SDL_Renderer*);
};

#endif // THREEHITBRICK_H
