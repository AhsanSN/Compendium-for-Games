#ifndef POWERUP_H
#define POWERUP_H

#include "Entity.h"
#include "Board.h"
#include "Paddle.h"
#include "Ball.h"
#include <SDL.h>

class PowerUp : public Entity               //Not all powerUps are helpful, :) careful which you are to collect
{
public:

    PowerUp(LTexture*,Board*,Point);            //Constructor

    enum POWERUP_TYPE {RESTORE_PAD,SHORTEN,ELONGATE,RESTORE_BALL,TURTLE,SPEEDBALL,BULLET,FIREBALL,STICKYBALL,MISSILE,EXTRA_LIFE,MULTIBALL,NUM_POWERUPS};

    ~PowerUp();         //Destructor

    void render(SDL_Renderer*);         //Rendering function

    void setWhich(int);                     //Setter for which powerUp this powerUp is

    void move(List* = NULL);            //move function (falling animation of the powerUp

    int getWhich();                         //Getter for which powerUp this powerUp is

    void setPower(Paddle*, Ball*);          //Power setter, sets the power of the ball or the paddle depending on the which of the powerUp

private:

    int which;                  //Stores which powerUp the powerUp is

    Board* gameBoard;           //keeps the gameBoard. Used to keep check of movement

    SDL_Rect spriteClips[NUM_POWERUPS];         //The sprite clip information is stored in this array
};

#endif // POWERUP_H
