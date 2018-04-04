#include "GUI.h"
#include <SDL.h>

GUI::GUI(LTexture* image,Point pos):Entity(image,pos)
{
    this->height = 0;
    this->width = 0;
    this->alive = true;
    this->scoreText = new Text("0",image);
    scoreText->color = 0;
    this->timeText = new Text("0",image);
    timeText->color = 0;
    this->livesText = new Text("0",image);
    livesText->color = 0;
    timeHeading = new Text("Time",image);
    timeHeading->setSize(0.7);
    powerupText = new Text("PowerUp",image);
    powerupText->setSize(0.7);
    for (int i=0; i<4; i++)
    {
        padPowerupIcons[i] = {908+i*27,963,27,27};
        ballPowerupIcons[i] = {908+i*27,936,27,27};
    }
    for(int i=0; i<2; i++)
    {
        padSizeIcon[i] = {908+i*27,989,27,27};
    }
    multiBall = {908,1015,27,27};
    toggleColor();
}

void GUI::setDimensions(int w, int h)
{
    this->SCREEN_WIDTH = w;
    this->SCREEN_HEIGHT = h;
    scoreText->setPosition(150 - scoreText->getWidth()/2,30);
    timeHeading->setPosition(SCREEN_WIDTH/2,30);
    timeText->setPosition(SCREEN_WIDTH/2,70);
    livesText->setPosition(160 - livesText->getWidth()/2,70);
    powerupText->setPosition(SCREEN_WIDTH-(2*powerupText->getWidth())/3,30);
    GUIBg = {0,0,SCREEN_WIDTH,90};
}

void GUI::setTime(Uint32& time)
{
    stringstream ss;
    if (time/60 < 10) ss << '0';
    ss << time/60 << ':';
    if (time%60 < 10) ss << '0';
    ss << (time%60);
    timeText->setText(ss.str());
    timeText->setSize(0.7);
}
void GUI::setPowerUp(int ball,int pad,int padSize,bool multiBall)
{
    this->currentPowerup[0] = ball;
    this->currentPowerup[1] = pad;
    switch(padSize)
    {
    case 0:
    {
        currentPowerup[2] = padSize;
        break;
    }
    case 1:
    {
        currentPowerup[2] = -1;
        break;
    }
    case 2:
    {
        currentPowerup[2] = padSize-1;
        break;
    }
    }
    if (!multiBall)this->currentPowerup[3] = -1;
}
void GUI::setScore(int& score)
{
    stringstream ss;
    stringstream sp;
    sp<<score;
    ss<< "Score:";
    ss << string(5-sp.str().length(),'0') << score;
    scoreText->setText(ss.str());
    scoreText->setSize(0.7);
    scoreText->setPosition(scoreText->getWidth()/2 + 20,70);
}

void GUI::setLives(int& lives)
{
    stringstream ss;
    ss<<"Lives:"<< lives;
    livesText->setText(ss.str());
    livesText->setSize(0.7);
    livesText->setPosition(livesText->getWidth()/2 + 20,30);
}


GUI::~GUI()
{
    //dtor
    delete scoreText;
    delete timeText;
    delete livesText;
    delete timeHeading;
    delete powerupText;
}

void GUI::render(SDL_Renderer* gRenderer)
{

    timeText->render(gRenderer);
    timeHeading->render(gRenderer);
    livesText->render(gRenderer);
    scoreText->render(gRenderer);
    powerupText->render(gRenderer);
    spriteSheetTexture->render(powerupText->getPos().x,50,&ballPowerupIcons[currentPowerup[0]],0.0,NULL,SDL_FLIP_NONE,gRenderer);
    spriteSheetTexture->render(powerupText->getPos().x + 27,50,&padPowerupIcons[currentPowerup[1]],0.0,NULL,SDL_FLIP_NONE,gRenderer);
    if (currentPowerup[2]!=-1)
    {
        spriteSheetTexture->render(powerupText->getPos().x + 2*27,50,&padSizeIcon[currentPowerup[2]],0.0,NULL,SDL_FLIP_NONE,gRenderer);
    }
    if (currentPowerup[3]!=-1)spriteSheetTexture->render(powerupText->getPos().x - 27,50,&multiBall,0.0,NULL,SDL_FLIP_NONE,gRenderer);
}
void GUI::toggleColor()
{
    timeText->color=!(timeText->color);
    livesText->color=!(livesText->color);
    scoreText->color=!(scoreText->color);
    timeHeading->color=!(timeHeading->color);
    powerupText->color=!(powerupText->color);
}


