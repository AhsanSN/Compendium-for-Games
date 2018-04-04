#ifndef STEELBRICK_H
#define STEELBRICK_H
#include "Brick.h"
class SteelBrick:public Brick//Special brick, can only be broken through smashers
{
public:
    SteelBrick(LTexture*,Board*,Point);
    void render(SDL_Renderer*);
};

#endif // STEELBRICK_H
