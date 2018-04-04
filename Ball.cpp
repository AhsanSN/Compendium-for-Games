#include "Ball.h"

Ball::Ball(LTexture* texture, Board* gameBoard,Paddle* paddle,bool primary):Entity(texture),gameBoard(gameBoard),paddle(paddle)     //Setting every starting relevant information
{
    int x=246;
    int y=3;
    this->width=12;
    this->height=12;
    this->primary=primary;

    //Loading sprites
    for (int i=NORMAL; i<NUM_BALL_MODES; i++)
    {
        spriteClips[i]= {x,y,width,height};
        x+=13;
    }
    //Loading the trail sprites onto the array
    int trailingX[] = {58, 170, 228, 110};//{24, 76, 136, 194};
    int trailingY = 104;
    trailingWidth = 14;
    trailingHeight = 14;

    for (int i=NORMAL; i<NUM_BALL_MODES; i++)
    {
        for (int j=INITIAL; j<NUM_TRAILING_SPRITES; j++)
        {
            trailingSpriteClips[i][j] = {trailingX[i]-17*j, trailingY, trailingWidth,trailingHeight};
        }
    }
    //Loading the ballPadBoard collision sound
    ballPadBoard = Mix_LoadWAV("Sounds/ballpaddle.wav");
    if( ballPadBoard == NULL)
    {
        printf( "Failed to load sound! SDL_mixer Error: %s\n", Mix_GetError() );
        exit(11);
    }


    setBounds();
    powerTime=0;
    type=BALL;
    setBallType(NORMAL);
    stick = true;
    paddleCollision = false;
    isSparkling = false;
    numTrailingPoints = 0;
    stickToPaddle();
}

Ball::~Ball()
{
    Mix_FreeChunk(ballPadBoard);            //Freeing the chunk
    ballPadBoard = NULL;
}

void Ball::render(SDL_Renderer* gRenderer)
{
    SDL_SetRenderDrawColor( gRenderer, 0x00, 0xFF, 0x00, 0xFF );
    if (isSparkling)
    {
        static int delay = 0;
        delay++;
        if(delay%5 == 0)
            expFrame++;
        if (expFrame < NUM_TRAILING_SPRITES*2)
            spriteSheetTexture->render(pos.x + width/2 - trailingWidth/2, pos.y + height/2 - trailingHeight/2, &trailingSpriteClips[ballType][expFrame%NUM_TRAILING_SPRITES], 0, NULL, SDL_FLIP_NONE, gRenderer);

        else
        {
            isSparkling = false;
            delay = 0;
            expFrame = 0;
        }
    }
    else
    {
        if (ballType != NORMAL)
        {
            for (int i=0; i<numTrailingPoints; i++)
            {
                if (i%2 == 1)
                    spriteSheetTexture->render(trailingPoints[i].x + width/2 - trailingWidth/2, trailingPoints[i].y + height/2 - trailingHeight/2, &trailingSpriteClips[ballType][i/2], 0, NULL, SDL_FLIP_NONE, gRenderer);
            }
        }
        spriteSheetTexture->render(pos.x,pos.y,&spriteClips[ballType],0.0, NULL, SDL_FLIP_NONE, gRenderer);
    }
}

void Ball::setBallType(int ballType)
{
    if (this->ballType != ballType)
    {
        isSparkling = true;
    }
    this->ballType=ballType;
    if(ballType==FIRE)
    {
        speed=5;
    }
    else if (ballType==STICK)
    {
        speed=5;
    }
    else if(ballType==SPEED)
    {
        speed=7;
    }
    else if (ballType==NORMAL)
    {
        speed=5;
    }
}

int Ball::getBallType()
{
    return ballType;
}

void Ball::stickToPaddle()
{
    numTrailingPoints = 0;
    this->pos.y = paddle->getPos().y-height;
    if (!paddleCollision)
    {
        this->pos.x = paddle->getPos().x+(paddle->getWidth()/2) - width/2;
    }
    else
    {
        this->pos.x = paddle->getPos().x + positionDifference;
    }
    setBounds();
    setDir(0,-1);//setting initial direction, normalized
}

void Ball::move(List* worldEnt)
{
    if (!stick && !isSparkling)
    {
        for (int i=numTrailingPoints-1; i>0; i--)
        {
            trailingPoints[i] = trailingPoints[i-1];
        }
        trailingPoints[0] = pos;
        if (numTrailingPoints < NUM_TRAILING_SPRITES*2)
            numTrailingPoints++;
        pos.y+=dy*speed;
        pos.x+=dx*speed;
        SDL_Rect boardCopy=gameBoard->getBounds();
        //TOP BOARD COLLISION
        if(this->pos.y <= boardCopy.y)
        {
            Mix_PlayChannel(-1,ballPadBoard,0);             //The chunk for ball pad/board collision
            pos.y = boardCopy.y;
            setDir(dx,dy*-1);
        }
        //LEFT BOARD COLLISION
        else if(this->pos.x + this->width >= boardCopy.x + boardCopy.w)
        {
            Mix_PlayChannel(-1,ballPadBoard,0);                 //The chunk for ball pad/board collision
            pos.x= boardCopy.x + boardCopy.w - this->width;
            setDir(dx*-1,dy);
        }
        //RIGHT BOARD COLLISION
        else if(this->pos.x  <= boardCopy.x )
        {
            Mix_PlayChannel(-1,ballPadBoard,0);         //The chunk for ball pad/board collision
            pos.x= boardCopy.x;
            setDir(dx*-1,dy);
        }
        //DOWN COLLISION
        else if(this->pos.y + this->height >= boardCopy.y + boardCopy.h)
        {
            Mix_PlayChannel(-1,ballPadBoard,0);     //The chunk for ball pad/board collision
            stick = true;
            paddleCollision = false;
            numTrailingPoints = 0;
        }
    }

    else
    {
        stickToPaddle();
    }
    //Updating bounding rectangle
    setBounds();
    //Checking for time of powerUp here so as to not make another function call
    if (((time(NULL) - powerTime)>10) && powerTime != 0 )
    {
        setBallType(NORMAL);
    }
}

bool Ball::isStuck()
{
    return stick;
}

void Ball::setStick(bool stick)
{
    this->stick=stick;

}

void Ball::setDir(float dx,float dy)
{
    this->dx=dx;
    this->dy=dy;
}

void Ball::reset()                  //Resets the ball
{
    setDir(1/sqrt(2),-1/sqrt(2));
    setBallType(NORMAL);
    stickToPaddle();
    stick = true;
}

void Ball::setPaddle(Paddle* pad)       //Setting the paddle of the ball
{
    this->paddle = pad;
}

void Ball::takeCollisionAction(int type)
{
    Mix_PlayChannel(-1,ballPadBoard,0);                 //The chunk for ball pad/board collision
    positionDifference = pos.x - paddle->getPos().x;
    paddleCollision = true;

    if (ballType == STICK)      //Sticky ball will stick rest will bounce off
    {
        ballType = NORMAL;
        stick=true;
    }
}

int Ball::getBallPowerTime()        //gets the power up activation
{
    return powerTime;
}

void Ball::setPowerTime(int powerTime)      //Sets the power up activation
{
    this ->powerTime = powerTime;
}

bool Ball::isPrimary()      //To get the information that tells us if the ball is the primary gameBall or not
{
    return primary;
}
