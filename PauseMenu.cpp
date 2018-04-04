#include "PauseMenu.h"


PauseMenu::PauseMenu(LTexture* image,Point pos):Menu(image,pos)
{
    heading = new Text("GAME PAUSED",image, pos);
    heading->setSize(1.5);
    heading->color = 1;

    this->MAXBUTTONS = PauseMenu::BUTTONSMAX;
    for (int i=0; i<BUTTONSMAX; i++)
    {
        buttons.push_back(Button(image,pos));
        buttons[i].setPosition(SCREEN_WIDTH/2 - width,SCREEN_HEIGHT/2);
    }
    buttons[RESUME].buttonText->setText("Resume");
    buttons[SAVE].buttonText->setText("Save");
    buttons[QUIT].buttonText->setText("Quit");
    option = -1;

}

void PauseMenu::handleEvents(SDL_Event& e)
{
    Menu::handleEvents(e);
    if (e.key.keysym.sym == SDLK_p)
    {
        option = RESUME;
    }
    switch(option)
    {
    case RESUME:
    {
        Mix_PlayChannel(-1,selectSound,0);
        Mix_ResumeMusic();
        this->alive = false;
        gameRun = true;
        option = -1;
        break;
    }
    case SAVE:
    {
        Mix_PlayChannel(-1,selectSound,0);
        this->alive = false;
        if (saveState)
        {
            saveState->setMode(LoadGameScreen::SAVE);
            saveState->parentMenu = this;
            saveState->setAlive(true);
        }
        option = -1;
        break;
    }
    case QUIT:
    {
        Mix_PlayChannel(-1,selectSound,0);
        Mix_PlayMusic(menuMus,-1);
        this->alive = false;
        option = -1;
        if (mMenu)
        {
            mMenu->setAlive(true);
        }
        resetGame = true;
        break;
    }
    }
}

void PauseMenu::render(SDL_Renderer* gRenderer)
{
    heading->setPosition(SCREEN_WIDTH/2,SCREEN_HEIGHT/3);
    Menu::render(gRenderer);
    heading->render(gRenderer);
}
