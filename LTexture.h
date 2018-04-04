#ifndef LTEXTURE_H
#define LTEXTURE_H
#include <iostream>
#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>

//Texture wrapper class
class LTexture
{
private:

    SDL_Texture* texture;

    int width;

    int height;

public:

    LTexture();

    ~LTexture();

    bool loadFromFile( std::string path, SDL_Renderer* gRenderer,int r,int g,int b );

    void free();    //Deallocates texture

    //Method to set color modulation
    void setColor( Uint8 red, Uint8 green, Uint8 blue );

    //Set blending method
    void setBlendMode( SDL_BlendMode blending );

    //Set alpha modulation method
    void setAlpha( Uint8 alpha );


    //Rendering method
    void render( int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE, SDL_Renderer* gRenderer = NULL,float scale = 1,SDL_Rect* outputRect = NULL);

    int getWidth();         //returns the width of the texture

    int getHeight();        //returns the height of texture
};


#endif // LTEXTURE_H
