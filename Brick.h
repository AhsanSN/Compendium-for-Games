#ifndef BRICK_H
#define BRICK_H
#include "Entity.h"
#include "Board.h"

class Brick : public Entity //ABSTRACT CLASS
{
public:
    Brick(LTexture*,Board*,Point);

    ~Brick();

    enum BRICK_FRAMES {INTACT,SLIGHTCRACK,HEAVCRACK,EXP1,EXP2,NUM_BRICK_FRAMES};//enumeration for brick frames

    enum COLORS {PURPLE,RED,YELLOW,TURQ,GRAY,GREEN,NUM_BRICK_COLORS};//enumeration for brick colors

    bool getPower(); //for getting powered attribute in save/load

    int getDamage();//for getting brickDamage attribute in save/load

    int getColor();//for getting color for save/load

    void setColor(int);//for setting color for save/load

    void setPowered(bool);//for setting powered attribute in save/load

    void setDamage(int);//for setting brickDamage attribute in save/load

    void setTargeted(bool);//for setting targeted attribute (for missile) in save/load

    bool getTargeted();//for getting targeted attribute in save/load
protected:

    SDL_Rect spriteClips[NUM_BRICK_COLORS][NUM_BRICK_FRAMES];//array for storing all brick sprites, dimensions [6][5]

    int brickHealth;//brickHealth attribute, unique for each type of brick

    int brickDamage;//brickDamage attribute, stores current brick damage

    int color;//stores brick color

    int incrementDmg();//method for incrementing brick Damage

    Board* gameBoard;//pointer to the gameBoard (association), will be used in for mobile bricks

    bool isPowered;//bool for storing if the brick can generate a powerup

    bool targeted;//bool for tracking if a missile has targeted the brick
};

#endif // BRICK_H
