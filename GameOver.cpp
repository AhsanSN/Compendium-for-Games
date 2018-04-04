#include "GameOver.h"

GameOver::GameOver(LTexture* image,Point pos):Menu(image,pos)
{
    gameOverText = new Text("Game Over",image,pos);
    gameOverText->setSize(2);
    gameOverText->color = 1;
    this->MAXBUTTONS = BUTTONSMAX;
    for (int i=0; i<BUTTONSMAX; i++)
    {
        buttons.push_back(Button(image,pos));
        buttons[i].setPosition(SCREEN_WIDTH/2 - width,SCREEN_HEIGHT/2);
    }
    buttons[CONTINUE].buttonText->setText("Restart");
    buttons[QUIT].buttonText->setText("Quit");
    option = -1;
}

void GameOver::setDimensions(int _SCREEN_WIDTH,int _SCREEN_HEIGHT)
{
    Menu::setDimensions(_SCREEN_WIDTH,_SCREEN_HEIGHT);
    for (int i=0; i<MAXBUTTONS; i++)
    {
        buttons[i].setPosition(SCREEN_WIDTH/2 - buttons[i].getWidth()/2, SCREEN_HEIGHT/2 + i*(buttons[i].getHeight()+20));
    }
    gameOverText->setPosition(SCREEN_WIDTH/2,SCREEN_HEIGHT/3);
}

void GameOver::handleEvents(SDL_Event& e)
{
    Menu::handleEvents(e);
    switch (option)
    {
    case CONTINUE:
    {
        Mix_PlayChannel(-1,selectSound,0);
        option = -1;
        gameRun = true;
        alive = false;
        break;
    }
    case QUIT:
    {
        Mix_PlayChannel(-1,selectSound,0);
        option = -1;
        Mix_PlayMusic(menuMus,-1);
        resetGame = true;
        if (mainMenu)
        {
            mainMenu->setAlive(true);
        }
        this->alive = false;
        break;
    }
    }
}

void GameOver::render(SDL_Renderer* gRenderer)
{
    Menu::render(gRenderer);
    gameOverText->render(gRenderer);

}

