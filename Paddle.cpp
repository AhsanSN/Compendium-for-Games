#include "Paddle.h"

Paddle::Paddle(LTexture* image, Board* gameBoard):Entity(image),gameBoard(gameBoard)
{
    padModeTime = 0;
    padSizeTime = 0;

    //Setting position of paddle a/c to the board
    this->pos.x = gameBoard->getBounds().x + gameBoard->getBounds().w/2.0f;
    this->pos.y=(gameBoard->getBounds().y + gameBoard->getBounds().h)/1.1f;

    /*Setting the widths and heights arrays*/
    widthList[SMALL] = 32;
    widthList[MEDIUM] = 54;
    widthList[LARGE] = 82;
    heightList[NORMAL] = 14;
    heightList[FIRE] = 15;
    heightList[TURTLE] = 14;
    heightList[ROCKET] = 16;

    /* Loading the sprites */
    for(int i=SMALL; i<NUM_PADDLE_SIZES; i++)
    {
        for(int j=NORMAL; j<NUM_PADDLE_MODES; j++)
        {
            spriteClips[i][j].x = 16 + 104*j;
            spriteClips[i][j].y = 147 - heightList[j] + 26*i;
            spriteClips[i][j].w = widthList[i];
            spriteClips[i][j].h = heightList[j];
        }
    }


    //Starting with default
    mode = NORMAL;
    size = MEDIUM;
    restoreMode();
    type=PADDLE;
    speed = 10;
    boardBounds = gameBoard->getBounds();

}

Paddle::~Paddle()       //Freeing pointers
{
    gameBoard=NULL;
}

void Paddle::render(SDL_Renderer* gRenderer)        //renders the paddle according to the mode and size
{
    SDL_SetRenderDrawColor( gRenderer, 0x00, 0xFF, 0x00, 0xFF );
    spriteSheetTexture->render(pos.x,pos.y,&spriteClips[size][mode],0.0, NULL, SDL_FLIP_NONE, gRenderer);
}

void Paddle::setDimensions()            //Sets width and height according to the size and mode
{
    width = widthList[size];
    height = heightList[mode];
}

void Paddle::fireUp()
{
    mode = FIRE;
    speed=15;
    setDimensions();
    setBounds();
}

void Paddle::turtleDown()
{
    mode = TURTLE;
    speed = 3;
    setDimensions();
    setBounds();
}

void Paddle::restoreMode()
{
    mode = NORMAL;
    speed=10;
    setDimensions();
    setBounds();
}

void Paddle::diminish()
{
    pos.x = pos.x + widthList[size]/2 - widthList[SMALL]/2;
    size = SMALL;
    setDimensions();
    setBounds();
}

void Paddle::enlarge()
{
    pos.x = pos.x + widthList[size]/2 - widthList[LARGE]/2;
    if (pos.x + widthList[LARGE] > boardBounds.x + boardBounds.w)
    {
        pos.x = boardBounds.x + boardBounds.w - widthList[LARGE];
    }
    else if (pos.x < boardBounds.x)
    {
        pos.x = boardBounds.x;
    }
    size = LARGE;
    setDimensions();
    setBounds();
}

void Paddle::restoreSize()
{
    pos.x = pos.x + widthList[size]/2 - widthList[MEDIUM]/2;
    if (pos.x + widthList[MEDIUM] > boardBounds.x + boardBounds.w)
    {
        pos.x = boardBounds.x + boardBounds.w - widthList[MEDIUM];
    }
    else if (pos.x < boardBounds.x)
    {
        pos.x = boardBounds.x;
    }
    size = MEDIUM;
    setDimensions();
    setBounds();
}


void Paddle::rocketUp()
{
    mode = ROCKET;
    speed = 10;
    setDimensions();
    setBounds();
}

void Paddle::handleEvents(SDL_Event& e)
{
    if(e.type == SDL_MOUSEMOTION)//if the event is moving mouse
    {
        //Get mouse position
        SDL_GetMouseState(&mouseX,NULL);
    }
}
void Paddle::move(List*)        //Moves according to the mouse position on screen, rather follows it
{
    //Move part
    SDL_GetMouseState(&mouseX,NULL);
    if (pos.x + bounds.w <= boardBounds.x + boardBounds.w && pos.x >= boardBounds.x)
    {
        int expectedPos=0;
        if (mouseX > pos.x + width/2)
        {
            expectedPos = pos.x + speed;
            if (expectedPos + width/2 < mouseX && expectedPos + width <= boardBounds.x + boardBounds.w)
            {
                pos.x = expectedPos;
            }
            else if (mouseX <= boardBounds.x + boardBounds.w - width/2)
            {
                pos.x = mouseX - width/2;
            }
            else
            {
                pos.x = boardBounds.x + boardBounds.w - width;
            }
        }

        else if (mouseX < pos.x + width/2)
        {
            expectedPos = pos.x - speed;
            if (expectedPos + width/2 > mouseX && expectedPos >= boardBounds.x)
            {
                pos.x = expectedPos;
            }
            else if (mouseX >= boardBounds.x + width/2)
            {
                pos.x = mouseX - width/2;
            }
            else
            {
                pos.x = boardBounds.x;
            }
        }
    }
    setDimensions();
    setBounds();


    /* Restoring pad or ball after time being elapsed, done here as this function is continuously being called, hence saving work
    to be done in game and that of making getters and setters*/
    if (((time(NULL) - padModeTime)>10) && padModeTime != 0)
    {
        restoreMode();
        padModeTime = 0;
    }
    if (((time(NULL) - padSizeTime)>10) && padSizeTime != 0)
    {
        restoreSize();
        padSizeTime = 0;
    }
}

int Paddle::getPaddleMode()         //Returns the mode of the paddle
{
    return mode;
}

void Paddle::reset()            //resets to default, the mode, the size and the position
{
    restoreMode();
    restoreSize();
    this->pos.x = 70;
    this->pos.y=(gameBoard->getBounds().y + gameBoard->getBounds().h)/1.1f;
}

int Paddle::getPaddleSize()     //returns the size
{
    return size;
}

void Paddle::setPaddleSize(int Size)            //Sets the size of the paddle
{
    this -> size = Size;
}


int Paddle::getSizeTime()
{
    return padSizeTime;
}

void Paddle::setSizeTime(int time)
{
    padSizeTime = time;
}

int Paddle::getModeTime()
{
    return padModeTime;
}

void Paddle::setModeTime(int time)
{
    padModeTime = time;
}

void Paddle::setPaddleMode(int mode)
{
    this->mode = mode;
}

