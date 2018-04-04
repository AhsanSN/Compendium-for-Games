#include "Bullet.h"

Bullet::Bullet(LTexture* texture, Board* gameBoard, Paddle* paddle, int bulletPosition):Smasher(texture, gameBoard, paddle), bulletPosition(bulletPosition)
{
    width = 9;
    height = 21;

    //loading sprites and sound

    for (int i=NORMAL; i<NUM_SMASHER_TYPES; i++)
    {
        spriteClips[i].x = 257 + 17*i;
        spriteClips[i].y = 27;
        spriteClips[i].w = width;
        spriteClips[i].h = height;
    }

    bulletFire = Mix_LoadWAV("Sounds/bullet.wav");
    if (bulletFire == NULL)
    {
        printf( "Failed to load sound! SDL_mixer Error: %s\n", Mix_GetError() );
        exit(10);
    }
    Mix_PlayChannel(-1,bulletFire,0);
    speed = 5;
    type = NORMBULLET;
    bulletPositionOffset = 2;

    initializePosition();
    setBounds();
}

Bullet::~Bullet()
{
    Mix_FreeChunk(bulletFire);          //deallocating sound
    bulletFire = NULL;
}

void Bullet::render(SDL_Renderer* gRenderer)        //Rendering the bullet
{
    if (alive)      //while alive this render
    {
        if(type==NORMBULLET)
            spriteSheetTexture->render(pos.x, pos.y, &spriteClips[NORMAL], 0, NULL, SDL_FLIP_NONE, gRenderer);
        else
            spriteSheetTexture->render(pos.x, pos.y, &spriteClips[RESISTANT], 0, NULL, SDL_FLIP_NONE, gRenderer);

    }

    else            //rendering the explosions
    {
        static int sound = 0;
        delay++;
        if(delay%5==0)
        {
            expFrame++;
        }

        if (expFrame < NUM_EXPLODING_FRAMES)
        {
            if (!sound)         //sound for explosion played once
            {
                Mix_PlayChannel(-1, soundExplode, 0);
                sound++;
            }
            spriteSheetTexture->render(pos.x-offsetX, pos.y-offsetY, &expSpriteClips[expFrame], 0, NULL, SDL_FLIP_NONE, gRenderer);
        }
        else
        {
            sound = 0;
            finished = true;
        }

    }
}


void Bullet::move(List* worldEnt)       //Move the bullet, while within board bounds
{
    if (alive)
    {
        pos.y -= speed;
    }

    if (pos.y <= boardBounds.y)
    {
        alive = false;
    }
    setBounds();
}

void Bullet::initializePosition()       //sets the initial position, with offset being the amount displaced from the centre of the paddle
{
    if (bulletPosition == LEFT)
    {
        pos.x = paddle->getPos().x + bulletPositionOffset;
        pos.y = paddle->getPos().y - height - 10;
    }

    else if (bulletPosition == RIGHT)
    {
        pos.x = paddle->getPos().x + paddle->getWidth() - width - bulletPositionOffset;
        pos.y = paddle->getPos().y - height - 10;
    }
}
