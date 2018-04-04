#include"LTexture.h"

LTexture::LTexture()
{
    texture = NULL;
    width = 0;
    height = 0;
}

LTexture::~LTexture()
{
    free();
}

bool LTexture::loadFromFile( std::string path, SDL_Renderer* gRenderer,int r,int g,int b)
{
    //Get rid of pre-existing texture
    free();

    //The final texture
    SDL_Texture* newTexture = NULL;

    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
    if( loadedSurface == NULL )
    {
        printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
    }
    else
    {
        //Color key image
        SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, r, g, b ) );
        //Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
        if( newTexture == NULL )
        {
            printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
        }
        else
        {
            //Get image dimensions
            width = loadedSurface->w;
            height = loadedSurface->h;
        }

        //Get rid of old loaded surface
        SDL_FreeSurface( loadedSurface );
    }

    //Return success
    texture = newTexture;
    return texture != NULL;
}

void LTexture::free()
{
    //Free texture if it exists
    if( texture != NULL )
    {
        SDL_DestroyTexture( texture );
        texture = NULL;
        width = 0;
        height = 0;
    }
}

void LTexture::setColor( Uint8 red, Uint8 green, Uint8 blue )
{
    //Modulate texture rgb
    SDL_SetTextureColorMod( texture, red, green, blue );
}

void LTexture::setBlendMode( SDL_BlendMode blending )
{
    //Set blending function
    SDL_SetTextureBlendMode( texture, blending );
}

void LTexture::setAlpha( Uint8 alpha )
{
    //Modulate texture alpha
    SDL_SetTextureAlphaMod( texture, alpha );
}

int LTexture::getWidth()
{
    return width;
}

int LTexture::getHeight()
{
    return height;
}

void LTexture::render( int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip, SDL_Renderer* gRenderer,float scale,SDL_Rect* outputRect)
{
    //Set rendering space and render to screen
    SDL_Rect renderQuad = { x, y, int(width*scale), int(height*scale) };
    if (outputRect == NULL)
    {
        //Set clip rendering dimensions
        if( clip != NULL )
        {
            renderQuad.w = clip->w*scale;
            renderQuad.h = clip->h*scale;
        }
    }
    else
    {
        renderQuad = {x,y,outputRect->w,outputRect->h};
    }
    //Render to screen
    SDL_RenderCopyEx( gRenderer, texture, clip, &renderQuad, angle, center, flip );
}


