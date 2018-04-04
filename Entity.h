#ifndef ENTITY_H
#define ENTITY_H
#include "Point.h"
#include "LTexture.h"
#include "time.h"
#include <SDL_mixer.h>
class List;
class Ball;
class Paddle;


/*THE base abstract class. All the objects that are to be rendered onto the game and the menus are derived from this.
An instance of this class cannot be created, however pointers of this type may be kept to store the derived class objects.
Useful in storing all the renderable objects in one place, namely a list. This class has general attributes and method common
to many child classes. However some methods are unique, meant for just specific classes, e.g. getPaddleSize().
These also happen to be virtual as the child class overwrites it and when called directs to the child class's method.
Used in saving to file, iterating for collisions etc. A pure virtual method is render()*/

class Entity
{
public:

    Entity(LTexture*,Point=Point());        //Constructor

    virtual  ~Entity();                 //Virtual destructor for abstract class

    int getWidth();             //Get the width of an entity

    int getHeight();            //Get the height of an entity

    SDL_Rect getBounds();           //returns the bounding rectangle of the entity

    virtual void render(SDL_Renderer*)=0;           //pure virtual render method, has to be re-written in every child class

    void setAlive(bool);                //sets the alive of an entity

    void setPos(Point);                     //Sets the position of the entity, position on the gameBoard

    void setPosX(int);                      //Sets x of the pos

    void setPosY(int);                      //Sets y of the pos

    bool getAlive();                //get whether an entity is alive or not

    float getSpeed();               //returns the speed of an entity

    virtual void move(List* = NULL) {} //will be redefined in object classes that move,, the argumment is to be used only for moving objects

    bool insideBounds(int,int);             //Checks if the given co-ordinates are inside the bounds of the entity

    friend class Game;

    virtual int incrementDmg()
    {
        return -1;   //Here to support polymorphic call for bricks
    }

    virtual void setDir(float,float)
    {
        return;   //Here to support polymorphic call for ball
    }

    virtual void stickToPaddle()
    {
        return;   //Here to support polymorphic call for ball
    }

    virtual bool getPower()
    {
        return 0;   //Here to support polymorphic call for brick
    }

    virtual int getWhich()
    {
        return -1;   //Here to support polymorphic call for powerUp
    }

    virtual int getDamage()
    {
        return -1;   //Here to support polymorphic call for brick
    }

    virtual int getColor()
    {
        return -1;   //Here to support polymorphic call for brick
    }

    virtual int getPaddleMode()
    {
        return -1;   //Here to support polymorphic call for paddle
    }

    virtual int getPaddleSize()
    {
        return -1;   //Here to support polymorphic call for paddle
    }

    virtual int getModeTime()
    {
        return -1;   //Here to support polymorphic call for paddle
    }

    virtual int getSizeTime()
    {
        return -1;   //Here to support polymorphic call for paddle
    }

    virtual int getBallPowerTime()
    {
        return -1;   //Here to support polymorphic call for ball
    }

    virtual int getBallType()
    {
        return -1;   //Here to support polymorphic call for ball
    }

    virtual void setPower(Paddle*, Ball*)
    {
        return;   //Here to support polymorphic call for powerUp
    }

    virtual bool isPrimary()
    {
        return 0;   //Here to support polymorphic call for ball
    }

    int getType();                  //returns the type of the entity

    Point getPos();             //returns pos

    virtual void setStick(bool)
    {
        return;   //Here to support polymorphic call for ball
    }

    void setBounds();           //Set the bounding rect of an entity, according to pos

    virtual bool getTargeted()
    {
        return 0;   //Here to support polymorphic call for brick
    }

    virtual void setTargeted(bool)
    {
        return;   //Here to support polymorphic call for
    }

    virtual void reset()
    {
        return;
    }; //will be redefined in ball,paddle, basically resets state (position & mode)

    virtual void takeCollisionAction(int)
    {
        return;   //Here to support polymorphic call for bullet and ball
    }

    float getDX();      //returns dx

    float getDY();      //returns dy

    //enumeration to keep track of the type of entity the current entity is
    enum ENTITIES {ONEHITBRICK,TWOHITBRICK,THREEHITBRICK,STEELBRICK,MOBILEBRICKX,MOBILEBRICKY,INVBRICK,BOSSBRICK,PADDLE,BALL,POWERUP,NORMBULLET,RESISTANTBULLET,MISSILE};
protected:

    Point pos;              //Co-ordinates of the top left corner of the rect of the entity on the screen

    SDL_Rect bounds;            //bounding rectangle of the entity

    bool alive;                         //flag to check if the entity is alive or not

    int width;                      //width of the entity's rect and on screen

    int height;                     //height of the entity's rect and on screen

    float dx;//used for storing direction of movement, dx&dy both behave as 2d direction vectors for the ball

    float dy;

    float speed;            //used for storing the speed of the movable entities

    int expFrame;           //used to keep track of which explosion frame or dying frame is to be rendered

    int type;               //used to keep check which of the child classes is the current entity

    LTexture* spriteSheetTexture;           //Texture to keep the spritesheet from which the sprites are clipped
};
#endif // ENTITY_H
