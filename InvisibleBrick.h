#ifndef INVISIBLEBRICK_H
#define INVISIBLEBRICK_H
#include "TwoHitBrick.h"


class InvisibleBrick: public TwoHitBrick//Special brick, inherits from the Two hit brick, reveals after 1 hit, destructs after 2nd
{
public:
    InvisibleBrick(LTexture*,Board*,Point);
    void render(SDL_Renderer*);
};

#endif // INVISIBLEBRICK_H
