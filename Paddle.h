#ifndef PADDLE_H_INCLUDED
#define PADDLE_H_INCLUDED
#include "Entity.h"
#include "Board.h"

class Paddle : public Entity
{
public:

    Paddle(LTexture*, Board*);      //Constructor

    ~Paddle();                              //Destructor

    void render(SDL_Renderer*);             //Rendering function for the paddle

    enum PADDLE_MODES {NORMAL,FIRE,TURTLE,ROCKET,NUM_PADDLE_MODES};     //The modes of the paddles, enum helps in usage

    void setDimensions();           //Sets the dimensions, width and height, according to the size and mode

    void fireUp();                  //Sets the mode of the paddle to bullet/fire mode

    void turtleDown();          //Sets the turtle paddle

    void rocketUp();            //Sets the rocket/missile firing paddle

    void restoreMode();         //Restores to the normal mode of the paddle

    void diminish();            //Shortens the paddle

    void enlarge();             //Elongates the paddle

    void restoreSize();         //restores the size to normal size of paddle

    void move(List* = NULL);            //Moves the paddle according to some set conditions

    void handleEvents(SDL_Event&);          //event handler method for the paddle

    int getPaddleMode();            //returns the mode of the paddle, useful for saving to file

    void setPaddleMode(int);            //sets the mode of paddle

    int getPaddleSize();                    //get the size of paddle which is active

    int getModeTime();                  //gets the time at which mode powerUp was set

    void setModeTime(int);          //sets the time at which mode powerUp was set

    int getSizeTime();                      //gets the time at which the size powerUp was set

    void setSizeTime(int);          //sets the time at which the size powerUp was set

    void setPaddleSize(int);            //sets the paddle size type

    void reset();                   //resets to default

private:

    enum PADDLE_SIZES {SMALL,MEDIUM,LARGE,NUM_PADDLE_SIZES};            //Enumeration to keep paddle size info, enum makes usage easy

    SDL_Rect spriteClips[NUM_PADDLE_SIZES][NUM_PADDLE_MODES];           //2D array to store info regarding the sprite clips for each, mode and size of the paddle

    int mode;           //Stores the mode of the paddle

    int size;           //Stores the size of the paddle

    int widthList[NUM_PADDLE_SIZES];            //Stores the widths of the paddle according to the sizes

    int heightList[NUM_PADDLE_MODES];           //Stores the height of the paddle, according to the modes

    int mouseX;                     //Used to store info about mouse state

    Board* gameBoard;       //used to store the gameBoard

    int padSizeTime;            //Used to store the time at which the size powerUp was set

    int padModeTime;        //Used to store the time at which the mode powerUp was set

    SDL_Rect boardBounds;           //Used to store the bounding rectangle of the gameBoard
};

#endif // PADDLE_H_INCLUDED
