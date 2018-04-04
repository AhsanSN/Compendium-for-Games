#include "Board.h"

Board::Board(LTexture* image,Point pos):Entity(image,pos),powerCollect(0)
{
    SCREEN_HEIGHT=1024;         //Initializing the dimensions of the screen
    SCREEN_WIDTH=768;

    r=255;      //Colors for background modulation
    g=255;
    b=255;

    //setting clips of boundary walls (the 4 boxes at the bottom right corner of the sprite sheet)
    spriteClips[0] = {267, 253, 30, 30};

    spriteClips[1] = {297, 253, 30, 30};

    spriteClips[2] = {267, 283, 30, 30};

    spriteClips[3] = {297, 283, 30, 30};

    //width and height of the blocks
    this->width = spriteClips[ 0 ].w;
    this->height = spriteClips[ 0 ].h;

    //Setting the dimensions of the sparkle sprites and the clips used to form the sparkle strip

    int sparkleX = 76;
    int sparkleY = 104;
    sparkleWidth = 16;
    sparkleHeight = 15;

    for (int i=0; i<8; i++)
    {
        sparkleSpriteClips[i]= {sparkleX,sparkleY,sparkleWidth,sparkleHeight};
        sparkleX+=17;
    }

    // Initializing the position of the sparkle strip
    sparklePos = height*3;

    //Loading the background music

    mainDay = Mix_LoadMUS( "Sounds/bgday.wav" );
    mainNight = Mix_LoadMUS("Sounds/bgnight.wav");

    if (mainDay == NULL || mainNight == NULL)       //If loading of music fails
    {
        printf( "Failed to load sound! SDL_mixer Error: %s\n", Mix_GetError() );
        exit(12);
    }


    gSpriteSheetTexture=image;
}

Board::~Board()
{
    //Freeing the bg texture
    bgTexture.free();

    //Freeing the sounds
    Mix_FreeMusic(mainDay);
    mainDay = NULL;
    Mix_FreeMusic(mainNight);
    mainNight = NULL;
}


void Board::render(SDL_Renderer* gRenderer)        //Renders the background (scrolling) and the strips that constitute the bounds of the game
{
    static int loaded=0;    //Flag, as this is to be loaded once per game
    if(!loaded)         //Loaded here instead of game, hence loading in the render function to get gRenderer
    {
        if(!bgTexture.loadFromFile("Images/Background.png",gRenderer,0,255,255))
            cerr << "Failed loading background image.\n";
        else
            loaded=1;
        scrollingOffset=0;
    }
    scrollingOffset-=0.5;       //The scrolling by moving the rendered part of the bg

    if( scrollingOffset < -bgTexture.getWidth() )       //Once whole image is rendered, the initial part is rendered again
    {
        scrollingOffset = 0;
    }

    //BACKGROUND MOVING AND CHANGE FROM DAY TO NIGHT
    bgTexture.render(scrollingOffset,0,&bgRect,0,NULL,SDL_FLIP_NONE,gRenderer);     //The start scroll
    bgTexture.render(scrollingOffset+SCREEN_WIDTH,0,&bgRect,0,NULL,SDL_FLIP_NONE,gRenderer);        //the follow up scroll

    int gameTimer=SDL_GetTicks()/1000;//stores current time in sec
    if(gameTimer%DAYTIME==0 && gameTimer!=0)        // Checks if the time period for background day or night duration is complete or not
    {
        dayChange=1;
    }
    if(dayChange)  //If the time period is complete, then change the setting
    {
        if(day)//change from day to night
        {

            if(r>0 && g>0)  //Shifting from day time to night time by decreasing the r and g of the colors
            {
                r-=1;
                g-=1;
            }
            else//day has been changed
            {
                playNightMusic();       //Plays the night time music
                dayChange=0;
                day=0;
            }

        }
        else
        {
            if(r<255 && g<255)      //Changing the r and g to get day time setting
            {
                r+=1;
                g+=1;
            }
            else//day has been changed
            {
                playDayMusic();     //plays the day music
                dayChange=0;
                day=1;
            }

        }
    }
    bgTexture.setColor(r,g,b);      //Sets every loop

    int sprite=0;
    //Rendering the top strip
    for (int i=width/2; i<SCREEN_WIDTH - width; i+=height)
    {
        spriteSheetTexture->render(i,3*height,&spriteClips[sprite%4],0.0, NULL, SDL_FLIP_NONE, gRenderer);
        sprite++;
    }
    //Rendering the left strip
    for (int i=3*height; i<SCREEN_HEIGHT; i+=height)
    {
        spriteSheetTexture->render(0,i,&spriteClips[sprite%4],0.0, NULL, SDL_FLIP_NONE, gRenderer);
        sprite++;
    }
    //Rendering the right strip
    sprite=1;
    for (int i=3*height; i<SCREEN_HEIGHT; i+=height)
    {
        spriteSheetTexture->render(SCREEN_WIDTH - height,i,&spriteClips[sprite%4],0.0, NULL, SDL_FLIP_NONE, gRenderer);
        sprite++;
    }

    if (powerCollect)       //If a powerUP is collected this will be activated through the game
    {
        int spark = 0;          //To choose the sparkle
        for (int x = 0; x < SCREEN_WIDTH; x += 20)      //renders the whole strip of sparkles
        {
            spriteSheetTexture->render(x,sparklePos,&sparkleSpriteClips[spark],0.0,NULL,SDL_FLIP_NONE,gRenderer);
            if (++spark > 7) spark = 0;
        }
        sparklePos += 5;
        if (sparklePos>SCREEN_HEIGHT)       //resetting after completion of animation
        {
            powerCollect = false;
            sparklePos = height*3;
        }
    }

    SDL_SetRenderDrawColor( gRenderer, 0x00, 0xFF, 0x00, 0xFF );
}
void Board::setDimensions(int SCREEN_WIDTH,int SCREEN_HEIGHT)       //To set the dimensions of the gameBoard along with the rect for back ground
{
    this->SCREEN_WIDTH=SCREEN_WIDTH;
    this->SCREEN_HEIGHT=SCREEN_HEIGHT;
    bgRect= {0,0,SCREEN_WIDTH,SCREEN_HEIGHT};
    bounds.x= width;                                        //Setting the bounding rectangle (collisions as always)
    bounds.y = 4*height;
    bounds.w= SCREEN_WIDTH-2*width;
    bounds.h=SCREEN_HEIGHT-4*height;
}

void Board::playDayMusic()          //To run the background music, day mode
{
    Mix_FadeInMusic(mainDay, -1, 2000);     //Gives a fade in effect.
}

void Board::playNightMusic()        //To run the background music, night mode
{
    Mix_FadeInMusic(mainNight,-1,2000);     //Gives a fade in effect.
}

bool Board::isDay()      //Used so that current bg mode (day or night) may be known
{
    if (r < 255)
    {
        return false;
    }
    return true;
}

void Board::sparkleOn()     //To activate the flag which activates the powerCollection sparkling on the board
{
    powerCollect = true;
}
