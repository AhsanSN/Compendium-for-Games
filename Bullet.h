#ifndef BULLET_H_INCLUDED
#define BULLET_H_INCLUDED
#include "Smasher.h"

class Bullet : public Smasher
{

public:

    Bullet(LTexture*, Board*, Paddle*, int);            //Constructor

    ~Bullet();              //Destructor

    void render(SDL_Renderer*);         //rendering function

    enum BULLET_POSITIONS {LEFT, RIGHT, NUM_BULLET_POSITIONS};      //Position nums

    void move(List* = NULL);            //moves the bullet

    void initializePosition();

protected:

    SDL_Rect spriteClips[2];            //1 is normal bullet, 2nd is resistant bullet

    int bulletPosition;

    int bulletPositionOffset;

    Mix_Chunk* bulletFire = NULL;           //firing sound
};

#endif // BULLET_H_INCLUDED
