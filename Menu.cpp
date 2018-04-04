#include "Menu.h"

Menu::Menu(LTexture* image,Point pos):Entity(image,pos)
{
    menuSprite = {0,0,1024,768};
    this->height = menuSprite.h;
    this->width = menuSprite.w;
    menuMus = Mix_LoadMUS("Sounds/gamemenus.wav");
    selectSound = Mix_LoadWAV("Sounds/select.wav");
    if( menuMus == NULL || selectSound == NULL)
    {
        printf( "Failed to load sound! SDL_mixer Error: %s\n", Mix_GetError() );
        exit(101);
    }
}

Menu::~Menu()
{
    Mix_FreeMusic(menuMus);
    menuMus = NULL;
    Mix_FreeChunk(selectSound);
    selectSound = NULL;
}

void Menu::setDimensions(int _SCREEN_WIDTH,int _SCREEN_HEIGHT)
{
    this->SCREEN_WIDTH = this->width = _SCREEN_WIDTH;
    this->SCREEN_HEIGHT = this->height = _SCREEN_HEIGHT;
    for (int i=0; i<MAXBUTTONS; i++)
    {
        buttons[i].setPosition(SCREEN_WIDTH/2 - buttons[i].getWidth()/2, SCREEN_HEIGHT/2 - buttons[i].getHeight()/2 + i*(buttons[i].getHeight()+20));
    }
    outputRect = {0,0,SCREEN_WIDTH,SCREEN_HEIGHT};
}

void Menu::render(SDL_Renderer* gRenderer)
{
    spriteSheetTexture->render(pos.x,pos.y,&menuSprite,0.0,NULL,SDL_FLIP_NONE,gRenderer,1,&outputRect);
    for (int i=0; i<MAXBUTTONS; i++)
    {
        buttons[i].render(gRenderer);
    }
}

int Menu::getOption()
{
    return option;
}

void Menu::setOption(int opt)
{
    option = opt;
}

void Menu::handleEvents(SDL_Event& e)
{
    if( e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP )
    {
        //Get mouse position
        int x, y;
        SDL_GetMouseState( &x, &y );
        for (int i =0; i<MAXBUTTONS ; i++)
        {
            if (buttons[i].insideBounds(x,y))
            {
                buttons[i].State = 1;
            }
            else
            {
                buttons[i].State = 0;
            }
        }
        if(e.type == SDL_MOUSEBUTTONDOWN) // change the click position of the mouse
        {
            if (e.button.button == SDL_BUTTON_LEFT) // Undo Button
            {
                for (int i=0; i<Menu::MAXBUTTONS; i++)
                {
                    if (buttons[i].insideBounds(x,y))
                    {
                        option = i;
                    }
                }
            }
        }
    }
}
