#ifndef BALL_H
#define BALL_H
#include "Entity.h"
#include <math.h>
#include "Board.h"
#include <SDL_mixer.h>
#include "Paddle.h"

class Ball: public Entity
{
public:

    Ball(LTexture*,Board*,Paddle*, bool = true);      //constructor

    ~Ball();                            //destructor

    enum BALL_MODE {NORMAL,STICK,SPEED,FIRE,NUM_BALL_MODES};        //The different modes of the ball, enum helps in selection in the code

    enum TRAILING_MODES {INITIAL, MIDDLE, FINAL, NUM_TRAILING_SPRITES};

    void render(SDL_Renderer*);          //Rendering function

    void setBallType(int);              // Setting the mode of the ball, useful in loading from file and powerUp setting

    int getBallType();              //Getting the type of the ball, useful in saving to a file

    void move(List* = NULL);        //Moves the ball according to some set conditions

    void stickToPaddle();           //set the ball to stick on the paddle

    bool isStuck();                 //returns if the ball is stuck or not

    void setStick(bool);            //sets if the ball is supposed to be stuck or not

    void setDir(float,float);       //sets the direction of movement of the ball

    void reset();                   //sets the ball to its initial condition

    void setPaddle(Paddle* pad);        //Sets the paddle that is related to the ball

    void takeCollisionAction(int);          //Gets the ball to take action according to the collision subject

    void setPaddleCollision(bool);      //Sets if collision with paddle is true or not

    void setPowerTime(int);         //Sets the time the powerUp was activated

    int getBallPowerTime();         //gets the time the powerUp was activated

    bool isPrimary();               //Returns if the ball under study is the gameBall or not

private:

    SDL_Rect spriteClips[NUM_BALL_MODES];             // To store the ball sprites

    SDL_Rect trailingSpriteClips[NUM_BALL_MODES][NUM_TRAILING_SPRITES];

    int ballType;       //Flag to keep track of what type of ball it is

    Board* gameBoard;       //The gameBoard is related to the ball, collisions being one of the usages

    Paddle* paddle;             //Paddle is kept associated to the ball, to set sticking and collision action

    bool stick;                 //Flag to keep track if the ball is supposed to stick or not

    bool primary;               //Flag to keep check if a ball is the gameBall or multiBall

    bool paddleCollision;       //Flag to keep track if the paddleball collision has occurred

    float positionDifference;           //To see the position difference between the colliding point of the ball with the paddle and the pad's .x

    int powerTime;                  //Attribute to see when a powerUp is activated.

    Mix_Chunk* ballPadBoard = NULL;     //Chunk for the ball sound on collision with the paddle and the board

    bool isSparkling;               //to check if the ball is supposed to leave a trail, or not

    Point trailingPoints[NUM_TRAILING_SPRITES*2];       //array of points relating to the sparkles

    int numTrailingPoints;              //Number of trailing sparkles

    int trailingWidth;               //Trail width

    int trailingHeight;                 //Trail Height

};

#endif // BALL_H
