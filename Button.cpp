#include "Button.h"

Button::Button(LTexture* image,Point pos):Entity(image,pos)
{
    buttonRects[0] = {457,1089,512,74};
    buttonRects[1] = {457,1174,512,74};
    this->height = buttonRects[0].h;
    this->width = buttonRects[0].w;
    this->bounds = {(int)pos.x,(int)pos.y,width,height};
    this->buttonText = new Text(" ",image,pos);
    buttonText->setPosition(pos.x+width/2,pos.y+height/2);
}

Button::~Button()
{
    //dtor
}
void Button::render(SDL_Renderer* gRenderer)
{
    spriteSheetTexture->render(pos.x,pos.y,&buttonRects[State],0.0,NULL,SDL_FLIP_NONE,gRenderer,buttonSize);
    buttonText->color = State;
    buttonText->render(gRenderer);
}

void Button::setSize(float scale)
{
    this->buttonSize = scale;
    this->width *= scale;
    this->height *= scale;
    buttonText->setSize(scale);
}

void Button::setPosition(int x, int y)
{
    this->pos.x = x;
    this->pos.y = y;
    this->bounds = {x,y,this->width,this->height};
    buttonText->setPosition(x+(this->width/2),y +(this->height/2));
}
