#ifndef SMASHER_H_INCLUDED
#define SMASHER_H_INCLUDED
#include "Entity.h"
#include "Paddle.h"
#include "Board.h"
#include <SDL_mixer.h>
class Smasher : public Entity
{
public:

    Smasher(LTexture*, Board*, Paddle*);        //constructor

    ~Smasher();                     //destructor

    virtual void render(SDL_Renderer*)=0;           //pure virtual render, making class abstract

    virtual void move(List* = NULL)=0;              //pure virtual move

protected:

    enum EXPLODING_FRAMES {START, POWERUP1, POWERUP2, BLOW, POWERDOWN1, POWERDOWN2, FINISH, NUM_EXPLODING_FRAMES};          //Exploding frame nums

    enum SMASHER_TYPES {NORMAL,RESISTANT,NUM_SMASHER_TYPES};        //Smasher type nums

    SDL_Rect expSpriteClips[NUM_EXPLODING_FRAMES];          //Secondary sprite clips

    bool smashed;           //Flag to check if the smasher has been smashed

    bool finished;              //Flag to check if the explosion has finished or not

    Board* gameBoard;       //Gameboard to be stored, to see collision

    int offsetX;

    int offsetY;

    Paddle* paddle;             //Paddle, being the originating point

    int delay;

    SDL_Rect boardBounds;           //bounding rect of the gameBoard

    Mix_Chunk* soundExplode = NULL;         //Chuck to store explosion sound

};


#endif // SMASHER_H_INCLUDED
