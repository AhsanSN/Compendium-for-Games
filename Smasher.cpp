#include "Smasher.h"

Smasher::Smasher(LTexture* image, Board* gameBoard, Paddle* paddle):Entity(image),gameBoard(gameBoard),paddle(paddle)
{
    int xList[] = {25, 61, 97, 137, 179, 219, 258};
    int yList[] = {214, 209, 206, 206, 206, 206, 206};
    int widthList[] = {21, 31, 38, 38, 36, 36, 37};
    int heightList[] = {20, 31, 38, 37, 37, 37, 37};
    for (int i=START; i<=NUM_EXPLODING_FRAMES; i++)
    {
        expSpriteClips[i].x = xList[i];
        expSpriteClips[i].y = yList[i];
        expSpriteClips[i].w = widthList[i];
        expSpriteClips[i].h = heightList[i];
    }

    soundExplode = Mix_LoadWAV("Sounds/explode.wav");
    if (soundExplode == NULL)
    {
        printf( "Failed to load sound! SDL_mixer Error: %s\n", Mix_GetError() );
        exit(-1);
    }

    smashed = false;
    finished = false;
    expFrame = 0;
    offsetX = 13;
    offsetY = 13;
    paddle=paddle;
    delay = 0;
    boardBounds = gameBoard->getBounds();
}

Smasher::~Smasher()
{
    gameBoard = NULL;
    paddle = NULL;
    Mix_FreeChunk(soundExplode);
    soundExplode = NULL;
}
