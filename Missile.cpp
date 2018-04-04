#include "Missile.h"

Missile::Missile(LTexture* texture, Board* gameBoard, Paddle* paddle):Smasher(texture, gameBoard, paddle)
{
    width = 10;
    height = 34;

    /* Loading Sprite Clips */
    for (int i=INITIAL; i<NUM_MISSILE_TYPES; i++)
    {
        spriteClips[i].x = 304 - 13*i;
        spriteClips[i].y = 23;
        spriteClips[i].w = width;
        spriteClips[i].h = height;
    }

    //Playing sound on launch
    missileFire = Mix_LoadWAV("Sounds/missileFire.wav");
    if (missileFire == NULL)
    {
        printf( "Failed to load sound! SDL_mixer Error: %s\n", Mix_GetError() );
        exit(12);
    }

    Mix_PlayChannel(-1,missileFire,0);

    /* Initializing attributes */
    speed = 0;
    count = 1;
    brick = NULL;
    brickIdentified = false;
    goneAstray = false;
    type = MISSILE;
    lastPos = paddle->getPos().y;

    initializePosition();
    setBounds();
}

Missile::~Missile()
{
    brick = NULL;
}

void Missile::render(SDL_Renderer* gRenderer)
{
    if (brickIdentified)
    {
        float angle;
        int spriteType;
        if (alive)
        {
            /* Loading relevant sprites*/
            if (count < LOADING)
                spriteType = INITIAL;

            else
                spriteType = FINAL;

            /* Calculating the angle of the missile based on its direction */
            if (count <= PREPARINGTOMOVE || goneAstray)
                angle = 0;

            else
            {
                if (orientation == LEFT)
                    angle = -atan(dx/-fabs(dy))*180/M_PI;

                else
                    angle = -atan(dx/fabs(dy))*180/M_PI;
            }
            spriteSheetTexture->render(pos.x, pos.y, &spriteClips[spriteType], angle, NULL, SDL_FLIP_NONE, gRenderer);
        }

        else
        {
            /* Smashing */
            delay++;
            if(delay%5==0)
                expFrame++;

            if (expFrame < NUM_EXPLODING_FRAMES)
                spriteSheetTexture->render(pos.x-offsetX, pos.y-offsetY, &expSpriteClips[expFrame], 0, NULL, SDL_FLIP_NONE, gRenderer);
        }
    }
}

void Missile::move(List* worldEnt)
{
    if (brickIdentified && alive)
    {
        speed = log(count);
        if (!brick->getAlive() || !brickTracked)
        {
            pos.y -= speed;
            if (brick->getAlive() && !goneAstray)
                brick->setTargeted(false); // Brick targeting set to false in case of missile going astray without the brick being destroyed
            goneAstray = true;
        }
        else if (count < INITIALIZING)
            pos.y -= 1;
        else if (count > PREPARINGTOMOVE)
        {
            float angle = tan((brick->getPos().x + brick->getWidth()/2 - pos.x - width/2) / -(brick->getPos().y + brick->getHeight() - pos.y)); // Angle calculation to generate Sin wave
            dy = sin(angle);
            dx = cos(angle);
            lastPos = pos.y;
            /* Determining movement based on orientation */
            if (orientation == LEFT)
            {
                pos.y += dy*speed;
                pos.x += dx*speed;
            }
            else
            {
                pos.y -= dy*speed;
                pos.x -= dx*speed;
            }
            checkBrickTracking(lastPos);
        }
        count ++;

        //Checking board collision
        if(this->pos.y <= boardBounds.y
                || this->pos.x + this->width >= boardBounds.x + boardBounds.w
                || this->pos.x  <= boardBounds.x
                || this->pos.y + this->height >= boardBounds.y + boardBounds.h)
        {
            alive = 0;
        }
    }

    /* Identify brick if not identified */
    else if(!brickIdentified)
    {
        brickIdentified = getBrick(worldEnt);
        brickTracked = brickIdentified;
        if (brickIdentified)
        {
            if (brick->getPos().x <= boardBounds.x + boardBounds.w/2)
                orientation = LEFT;
            else
                orientation = RIGHT;
        }
    }
    setBounds();
}

bool Missile::getBrick(List* worldEnt)
{
    Node* tmp = worldEnt->getNodeAtInd(0);
    float minDist;
    if (tmp)
    {
        while (tmp && (tmp->ent->getType() == POWERUP || tmp->ent->getTargeted()))
        {
            tmp = tmp->next;
        }

        if (!tmp)
        {
            return false;
        }

        brick = tmp->ent;
        minDist = sqrt(pow(pos.x - brick->getPos().x + width/2 - brick->getWidth()/2, 2) + pow(pos.y - brick->getPos().y - brick->getHeight(), 2)); // Calculating minimum distance between the top of missile and the bottom of the brick

        while(tmp)
        {
            if (tmp->ent->getType() != POWERUP && tmp->ent->getAlive() && !tmp->ent->getTargeted())
            {
                Entity* currentBrick = tmp->ent;
                float curDist = sqrt(pow(pos.x - currentBrick->getPos().x + width/2 - currentBrick->getWidth()/2, 2) + pow(pos.y - currentBrick->getPos().y - currentBrick->getHeight(), 2));
                if (curDist < minDist)
                {
                    brick = currentBrick;
                    minDist = curDist;
                }
            }
            tmp = tmp->next;
        }
        brick->setTargeted(true);
        return true;
    }
    return false;
}

void Missile::initializePosition()
{
    pos.x = paddle->getPos().x + paddle->getWidth()/2 - width/2;
    pos.y = paddle->getPos().y - height;
}

void Missile::checkBrickTracking(int last)
{
    if (lastPos < pos.y && count > ONITSPATH) // Checking whether the missile has stuck once it has loaded
    {
        brickTracked = false;
    }
}
