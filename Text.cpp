#include "Text.h"

Text::Text(string text,LTexture* image,Point pos):Entity(image,pos)
{
    SCREEN_HEIGHT = 0;
    SCREEN_WIDTH = 0;
    for (int i = 0; i < 13; i++ )
    {
        SDL_Rect charRect = {377+(40*i),800,40,40};
        Characters.insert ( pair<char,SDL_Rect>((char)(i+97),charRect) );
        charRect.y+=40;
        Characters.insert ( pair<char,SDL_Rect>((char)(i+13+97),charRect) );
        if (i<11)
        {
            charRect.y+=40;
            Characters.insert ( pair<char,SDL_Rect>((char)(i+26+22),charRect) );
        }
    }
    this->text = text;
    this->height = Characters['a'].h;
    this->width = text.length()*Characters['a'].w;
    color = 0;
}

Text::~Text()
{
    //dtor
}

void Text::setText(string str)
{
    this->text = str;
    this->width = str.length()*40;
}

void Text::setPosition(float x, float y)
{
    this->pos.x = x;
    this->pos.y = y;
}

void Text::setSize(float tSize)
{
    this->textSize = tSize;
    this->width = this->text.length()*40*tSize;
    this->height = 40*tSize;
}

void Text::render(SDL_Renderer* gRenderer)
{

    for (unsigned int i = 0; i<text.length(); i++)
    {
        char Char = text[i] ;
        if ((int)text[i] >= 65 && (int)text[i] < 97)
        {
            Char = (char)((int)text[i] + 32);
        }
        else if ((int)text[i] >= 48 && (int)text[i] < 58)
        {
            Char = (char)((int)text[i]);
        }
        SDL_Rect renderQuad = {Characters[Char].x,Characters[Char].y,Characters[Char].w,Characters[Char].h};

        if (color == 1 )
        {
            renderQuad.y += 139;
        }

        spriteSheetTexture->render(pos.x-width/2+(i*textSize*40),pos.y-height/2,&renderQuad,0.0,NULL,SDL_FLIP_NONE,gRenderer,textSize);
    }
}
