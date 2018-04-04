#include "ResistantBullet.h"

ResistantBullet::ResistantBullet(LTexture* texture, Board* gameBoard, Paddle* paddle, int bulletPosition):Bullet(texture, gameBoard, paddle, bulletPosition)
{
    smashes = NULL;
    numSmashes = 0;
    delays = NULL;
    expFrames = NULL;
    type= RESISTANTBULLET;
}

ResistantBullet::~ResistantBullet()
{
    delete[] smashes;
    delete[] delays;
    delete[] expFrames;

    smashes = NULL;
    delays = NULL;
    expFrames = NULL;
}

void ResistantBullet::render(long int& frame, SDL_Renderer* gRenderer)      //renders the resistant bullet
{
    Bullet::render(gRenderer);          //Renders the movement according to BULLET's render

    for (int i=0; i<numSmashes; i++)        //Explosion rendering
    {
        static int sound = 0;
        delays[i]++;
        if(delays[i]%5==0)
        {
            expFrames[i]++;
        }

        if (expFrames[i] < NUM_EXPLODING_FRAMES)
        {
            if (!sound)         //Explosion sound played once
            {
                Mix_PlayChannel(-1, soundExplode, 0);
            }
            sound++;
            spriteSheetTexture->render(smashes[i].x-offsetX, smashes[i].y-offsetY, &expSpriteClips[expFrames[i]], 0, NULL, SDL_FLIP_NONE, gRenderer);
        }
        else
        {
            sound = 0;
            finished = true;
        }
    }
}

void ResistantBullet::addSmashLocation()            //Adds smash locations and info to the resistant bullet
{
    numSmashes ++;
    Point* tempSmashes = new Point[numSmashes];
    int* tempDelays = new int[numSmashes];
    int* tempExpFrames = new int[numSmashes];
    for (int i=0; i<numSmashes-1; i++)
    {
        tempSmashes[i] = smashes[i];
        tempDelays[i] = delays[i];
        tempExpFrames[i] = expFrames[i];

    }
    delete[] smashes;
    delete[] delays;
    delete[] expFrames;
    tempSmashes[numSmashes-1] = pos;
    tempDelays[numSmashes-1] = 0;
    tempExpFrames[numSmashes-1] = 0;
    smashes = tempSmashes;
    delays = tempDelays;
    expFrames = tempExpFrames;
}

void ResistantBullet::takeCollisionAction(int type)
{
    addSmashLocation();
}
