#include "Entity.h"

Entity::Entity(LTexture* image,Point pos)           //Constructor to set some generic attributes
{
    spriteSheetTexture = image;
    this->pos.x = pos.x;
    this->pos.y = pos.y;
    alive=true;
    width=0;
    height=0;
    dx=0;
    dy=0;
    expFrame=0;
    speed=0;
}

Entity::~Entity()       //Destructor to set pointers to NULL
{
    spriteSheetTexture=NULL;
}
int Entity::getWidth()
{
    return width;
}
int Entity::getHeight()
{
    return height;
}
void Entity::setPos(Point pos)
{
    this-> pos = pos;
}
bool Entity::insideBounds(int x, int y)
{
    return (x>=bounds.x && x<=(bounds.x + bounds.w) && y>=bounds.y && y<=(bounds.y + bounds.h));
}

void Entity::setAlive(bool alive)
{
    this->alive=alive;
}
bool Entity::getAlive()
{
    return alive;
}

SDL_Rect Entity::getBounds()
{
    return bounds;
}

int Entity::getType()
{
    return type;
}

Point Entity::getPos()
{
    return pos;
}
float Entity::getSpeed()
{
    return speed;
}
void Entity::setBounds()
{
    bounds.x=pos.x;
    bounds.y=pos.y;
    bounds.w=width;
    bounds.h=height;
}

void Entity::setPosX(int x)
{
    pos.x=x;
}
void Entity::setPosY(int y)
{
    pos.y=y;
}

float Entity::getDX()
{
    return dx;
}

float Entity::getDY()
{
    return dy;
}
