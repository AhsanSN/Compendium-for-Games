#include "MainMenu.h"

MainMenu::MainMenu(LTexture* image,Point pos):Menu(image,pos)
{
    this->MAXBUTTONS = BUTTONSMAX;
    for (int i=0; i<BUTTONSMAX; i++)
    {
        buttons.push_back(Button(image,pos));
        buttons[i].setPosition(SCREEN_WIDTH/2 - width,SCREEN_HEIGHT/2);
    }
    buttons[0].buttonText->setText("New Game");
    buttons[1].buttonText->setText("Load");
    buttons[2].buttonText->setText("Credits");
    buttons[3].buttonText->setText("Quit");
    heading = new Text("BRICRUMBLE",image, pos);
    heading->setSize(1.5);
    heading->color = 1;
    heading->setPosition(512,256);
    creditsSound = Mix_LoadMUS("Sounds/credits.wav");
    if( creditsSound == NULL)
    {
        printf( "Failed to load sound! SDL_mixer Error: %s\n", Mix_GetError() );
        exit(100);
    }
    scrollingOffset=0;
    option=-1;
}

void MainMenu::setDimensions(int w,int h)
{
    Menu::setDimensions(w,h);
    heading->setPosition(w/2,h/3);
    heading->setSize(1.5);
}

MainMenu::~MainMenu()
{
    delete heading;
    credits.free();
    Mix_FreeMusic(creditsSound);
    creditsSound = NULL;
}

void MainMenu::handleEvents(SDL_Event& e)
{
    if (!showCredits)
    {
        Menu::handleEvents(e);
        switch (option)
        {
        case PLAY:
        {
            Mix_PlayChannel(-1,selectSound,0);
            alive = false;
            option = -1;
            gameStart = true;
            break;
        }
        case LOAD:
        {
            Mix_PlayChannel(-1,selectSound,0);
            alive = false;
            option = -1;
            if (loadState)
            {
                loadState->setMode(LoadGameScreen::LOAD);
                loadState->parentMenu = this;
                loadState->setAlive(true);
            }
            break;
        }
        case CREDITS:
        {
            Mix_PlayChannel(-1,selectSound,0);
            Mix_PlayMusic(creditsSound,-1);
            showCredits = true;
            option = -1;
            break;
        }
        }
    }
    else
    {
        if (e.key.keysym.sym == SDLK_ESCAPE)
        {
            Mix_PlayMusic(menuMus,-1);
            showCredits = false;
        }
    }
}

void MainMenu::render(SDL_Renderer* gRenderer)
{
    static int loaded=0;
    if(!loaded)
    {
        if(!credits.loadFromFile("Images/Credits.png",gRenderer,0,255,255))
            cerr << "Failed loading background image.\n";
        else
        {
            loaded=1;
            bgRect= {0,0,credits.getWidth(),credits.getHeight()};
        }

    }
    if (!showCredits)
    {
        static int playOnce = 0;
        if (!playOnce++) Mix_PlayMusic(menuMus,-1);
        Menu::render(gRenderer);
        heading->render(gRenderer);
    }
    else
    {
        scrollingOffset-=0.5;
        if( scrollingOffset < -credits.getHeight() + 175 )
        {
            scrollingOffset = 0;
            showCredits=false;
            Mix_PlayMusic(menuMus,-1);
        }
        credits.render(0,scrollingOffset,&bgRect,0,NULL,SDL_FLIP_NONE,gRenderer);
        credits.render(0,scrollingOffset+credits.getHeight(),&bgRect,0,NULL,SDL_FLIP_NONE,gRenderer);
    }
}

void MainMenu::startGame()
{
    gameStart=true;
    alive=0;
}
