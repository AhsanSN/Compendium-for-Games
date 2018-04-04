#include "PowerUp.h"

PowerUp::PowerUp(LTexture* texture, Board* gameBoard,Point pos):Entity(texture,pos),gameBoard(gameBoard)
{
    //Setting attributes
    alive = true;
    int x = 1;
    int y = 249;
    width = 25;
    height = 26;

    type = POWERUP;         //Entity type

    which = (rand() % 12);      //Selecting randomly which powerUp is this powerUp

    //movement info
    dx = 0;
    dy = 1;
    speed = 3;

    //loading sprites
    int i = 0;
    for (; i < RESTORE_BALL; i++)
    {
        spriteClips[i] = {x, y, width, height};
        y += height;
    }
    y = 249;
    x += width + 1;
    for (; i < BULLET; i++)
    {
        spriteClips[i] = {x, y, width, height};
        y += height;
    }
    y = 249;
    x += width + 1;
    for (; i < MISSILE; i++)
    {
        spriteClips[i] = {x, y, width, height};
        y += height;
    }
    y = 249;
    x += width + 1;
    for (; i < NUM_POWERUPS; i++)
    {
        spriteClips[i] = {x, y, width, height};
        y += height;
    }


    setBounds();            //Setting the bounding rectangle (for collision detection)
}

void PowerUp::render(SDL_Renderer* gRenderer)           //Rendering function
{
    //Setting the rendering target's fill color and opacity
    SDL_SetRenderDrawColor( gRenderer, 0x00, 0xFF, 0x00, 0xFF );

    //rendering the sprite
    spriteSheetTexture->render(pos.x, pos.y, &spriteClips[which], 0.0, NULL, SDL_FLIP_NONE, gRenderer);
}

void PowerUp::move(List*)       //Dropping the powerUp
{
    if (!(pos.y > (gameBoard->getBounds().y + gameBoard->getBounds().h)/1.1f + 80))
    {
        pos.y += speed;
        setBounds();
    }
    else    //Once out of bounds, set alive false, and the list handles the deallocation
    {
        alive = false;
    }
}

int PowerUp::getWhich()     //Returns the type of powerUp, useful for file Loading
{
    return which;
}

void PowerUp::setWhich(int which)   //Force sets the type of PowerUp, useful for file loading
{
    this->which = which;
}

PowerUp::~PowerUp()             //Destructor, sets pointer attribute to NULL
{
    gameBoard = NULL;
}

void PowerUp::setPower(Paddle* pad, Ball* ball)             //Power Setter function, sets the power of the ball/pad depending on the type of powerUp
{
    switch (which)
    {
    case RESTORE_PAD:
        pad->restoreMode();
        pad->restoreSize();
        pad->setModeTime(0);
        pad->setSizeTime(0);
        break;
    case ELONGATE:
        pad->enlarge();
        pad->setSizeTime(time(NULL));
        break;
    case SHORTEN:
        pad->diminish();
        pad->setSizeTime(time(NULL));
        break;
    case TURTLE:
        pad->turtleDown();
        pad->setModeTime(time(NULL));
        break;
    case BULLET:
        pad->fireUp();
        pad->setModeTime(time(NULL));
        break;
    case MISSILE:
        pad->rocketUp();
        pad->setModeTime(time(NULL));
        break;
    case RESTORE_BALL:
        ball->setBallType(Ball::NORMAL);
        ball->setPowerTime(0);
        break;
    case FIREBALL:
        ball->setBallType(Ball::FIRE);
        ball->setPowerTime(time(NULL));
        break;
    case SPEEDBALL:
        ball->setBallType(Ball::SPEED);
        ball->setPowerTime(time(NULL));
        break;
    case STICKYBALL:
        ball->setBallType(Ball::STICK);
        ball->setPowerTime(time(NULL));
        break;
    default:
        break;
    }
}

