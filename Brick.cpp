#include "Brick.h"

Brick::Brick(LTexture* image, Board* gameBoard, Point pos):Entity(image,pos),gameBoard(gameBoard)
{
    int probability = rand() % 100;
    //each brick has a 20% chance of being powered
    if (probability < 20)
    {
        isPowered = true;
    }
    else
        isPowered = false;

    //Loading sprites

    int x=0;
    int y=0;
    width=48;
    height=18;
    for(int i=PURPLE; i<NUM_BRICK_COLORS - 1; i++)
    {
        y=0;
        for(int j=INTACT; j<NUM_BRICK_FRAMES; j++)
        {
            spriteClips[i][j]= {x,y,width,height};
            y+=height;
        }
        x+=width;
    }
    x=317;
    y=0;
    for(int i=INTACT; i<NUM_BRICK_FRAMES; i++)
    {
        spriteClips[GREEN][i]= {x,y,width,height};
        y+=height;
    }
    //setting attributes and updating bounds
    brickHealth=0;
    brickDamage=0;
    setBounds();
    color=rand()%(NUM_BRICK_COLORS-2);// Subtracting 2 since last two bricks are steel and boss one, their color will be set separately
}

Brick::~Brick()
{
    //dtor
}

int Brick::incrementDmg() //increments brick damage, returns 1 if brick is dead, 0 otherwise
{
    if(brickHealth==10)
    {
        return 0;//condition for steel brick, should die only if hit by bullet or missile
    }
    if(++brickDamage>=brickHealth)
    {
        setAlive(0);
        return 1;
    }
    else
    {
        return 0;
    }
}


bool Brick::getPower()
{
    return isPowered;
}

int Brick::getDamage()
{
    return brickDamage;
}

int Brick::getColor()
{
    return color;
}

void Brick::setDamage(int dmg)
{
    brickDamage = dmg;
}

void Brick::setColor(int color)
{
    this->color = color;
}

void Brick::setPowered(bool isPowered)
{
    this->isPowered = isPowered;
}

bool Brick::getTargeted()
{
    return targeted;
}

void Brick::setTargeted(bool targeted)
{
    this->targeted = targeted;
}
