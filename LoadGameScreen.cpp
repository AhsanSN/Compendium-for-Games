#include "LoadGameScreen.h"
#include "Game.h"
LoadGameScreen::LoadGameScreen(LTexture* image,Point pos):Menu(image,pos)
{
    heading = new Text("LOAD GAME",image, pos);
    heading->setSize(1.5);
    heading->color = 1;
    mode=1;
    this->MAXBUTTONS = BUTTONSMAX;
    for (int i=0; i<BUTTONSMAX; i++)
    {
        buttons.push_back(Button(image,pos));
        buttons[i].setPosition(SCREEN_WIDTH/2 - width,SCREEN_HEIGHT/2);
    }
    buttons[STATE1].buttonText->setText("State 1");
    buttons[STATE2].buttonText->setText("State 2");
    buttons[STATE3].buttonText->setText("State 3");
    buttons[CANCEL].buttonText->setText("Cancel");
}

void LoadGameScreen::setMode(int Mode)
{
    this->mode = Mode;
    option=-1;
    if(mode==SAVE)
    {
        heading->setText("SAVE GAME");
    }

    else
    {
        heading->setText("LOAD GAME");
    }
    heading->setSize(1.5);
}

void LoadGameScreen::handleEvents(SDL_Event& e)
{
    Menu::handleEvents(e);
    switch (option)
    {
    case STATE1:
    {
        Mix_PlayChannel(-1,selectSound,0);
        if (mode == LOAD)
        {
            game->stateLoader("Saves/State1.txt");
            cout << "Game has been loaded from state 1.\n";
            alive=0;
            parentMenu->startGame();
        }
        else if (mode == SAVE)
        {
            game->stateSaver("Saves/State1.txt");
            cout << "Game has been saved in state 1.\n";
        }
        option = -1;
        break;
    }
    case STATE2:
    {
        Mix_PlayChannel(-1,selectSound,0);
        if (mode == LOAD)
        {
            game->stateLoader("Saves/State2.txt");
            cout << "Game has been loaded from state 2.\n";
            alive=0;
            parentMenu->startGame();

        }
        else if (mode == SAVE)
        {
            game->stateSaver("Saves/State2.txt");
            cout << "Game has been saved in state 2.\n";
        }
        option = -1;
        break;
    }
    case STATE3:
    {
        Mix_PlayChannel(-1,selectSound,0);
        if (mode == LOAD)
        {
            game->stateLoader("Saves/State3.txt");
            cout << "Game has been loaded from state 3.\n";
            alive=0;
            parentMenu->startGame();
        }
        else if (mode == SAVE)
        {
            game->stateSaver("Saves/State3.txt");
            cout << "Game has been saved in state 3.\n";
        }
        option = -1;
        break;
    }
    case CANCEL:
    {
        Mix_PlayChannel(-1,selectSound,0);
        option = -1;
        this->alive = false;
        if (parentMenu) parentMenu->setAlive(true);
    }
    }
}

void LoadGameScreen::render(SDL_Renderer* gRenderer)
{
    Menu::render(gRenderer);
    heading->setPosition(SCREEN_WIDTH/2,SCREEN_HEIGHT/3);
    heading->render(gRenderer);
}

void LoadGameScreen::setGame(Game* game)
{
    this->game=game;
}
