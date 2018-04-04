#include "GameCompleteScreen.h"

GameCompleteScreen::GameCompleteScreen(LTexture* image,Point pos):Menu(image,pos)
{
    this->MAXBUTTONS = BUTTONSMAX;
    for (int i=0; i<BUTTONSMAX; i++)
    {
        buttons.push_back(Button(image,pos));
        buttons[i].setPosition(SCREEN_WIDTH/2 - width,SCREEN_HEIGHT/2);
    }
    buttons[QUIT].buttonText->setText("QUIT");
    buttons[NEXT].buttonText->setText("Next");
    heading = new Text("LEVEL COMPLETE",image);
    scoreHeading = new Text("Score",image);
    scoreText = new Text("Score",image);
    bonusScore = new Text("Bonus",image);
    totalScore = new Text("Score",image);

    scoreText->color = bonusScore->color = scoreHeading->color = heading->color = totalScore->color= 1;
    heading->setSize(1.5);
    option = -1;
    levStart = Mix_LoadWAV("Sounds/levelstart.wav");
    levComplete = Mix_LoadWAV("Sounds/levelcomplete.wav");
    if( levStart == NULL || levComplete == NULL)
    {
        printf( "Failed to load sound! SDL_mixer Error: %s\n", Mix_GetError() );
        exit(100);
    }
}

string GameCompleteScreen::getScoreStr(int Score,string scoretype)
{
    stringstream ss;
    stringstream sp;
    sp << Score;
    ss << scoretype<<" : " << string(5-sp.str().length(),'0') << Score;
    return ss.str();
}

void GameCompleteScreen::setScore(int Score)
{
    scoreText->setText(getScoreStr(Score,"Score"));
    scoreText->setPosition(SCREEN_WIDTH/2,SCREEN_HEIGHT/3);
}

void GameCompleteScreen::setBonus(int Score)
{
    bonusScore->setText(getScoreStr(Score,"Bonus"));
    bonusScore->setPosition(SCREEN_WIDTH/2,SCREEN_HEIGHT/3+40);
}

void GameCompleteScreen::setTotalScore(int Score)
{
    totalScore->setText(getScoreStr(Score,"Total Score"));
    totalScore->setPosition(SCREEN_WIDTH/2,SCREEN_HEIGHT/3+80);
}

GameCompleteScreen::~GameCompleteScreen()
{
    //dtor
    mainMenu = NULL;
    SDL_DestroyTexture(auxtexture);
    levComplete = NULL;
    levStart = NULL;
    delete heading;
}

void GameCompleteScreen::setDimensions(int _SCREEN_WIDTH,int _SCREEN_HEIGHT)
{
    Menu::setDimensions(_SCREEN_WIDTH,_SCREEN_HEIGHT);
    heading->setPosition(_SCREEN_WIDTH/2,_SCREEN_HEIGHT/5);
    scoreHeading->setPosition(SCREEN_WIDTH/2,SCREEN_HEIGHT/5+60);

    for (int i=0; i<MAXBUTTONS; i++)
    {
        buttons[i].setSize(0.6);
        buttons[i].setPosition(_SCREEN_WIDTH/2 - buttons[i].getWidth()/2, 3*(_SCREEN_HEIGHT/5)+ i*(buttons[i].getHeight() + 10));
    }
}

void GameCompleteScreen::render(SDL_Renderer* gRenderer)
{
    auxtexture = SDL_CreateTexture(gRenderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, SCREEN_WIDTH, SCREEN_HEIGHT);

    SDL_SetTextureBlendMode(auxtexture, SDL_BLENDMODE_BLEND);
    SDL_SetRenderTarget(gRenderer, auxtexture);
    //render what we want
    SDL_SetRenderDrawColor(gRenderer,0,0,0,150);
    SDL_RenderFillRect(gRenderer,&outputRect);

    //change the target back to the default and then render the aux

    SDL_SetRenderTarget(gRenderer, NULL); //NULL SETS TO DEFAULT
    SDL_RenderCopy(gRenderer, auxtexture, NULL, &outputRect);
    this->bounds = {width/4,height/4,menuSprite.w,menuSprite.h};
    for (int i=0; i<MAXBUTTONS; i++)
    {
        buttons[i].render(gRenderer);
    }
    SDL_DestroyTexture(auxtexture);
    heading->render(gRenderer);
    bonusScore->render(gRenderer);
    totalScore->render(gRenderer);
    scoreText->render(gRenderer);
    scoreHeading->render(gRenderer);
}

void GameCompleteScreen::handleEvents(SDL_Event& e)
{
    static int playOnce = 0;
    if (!playOnce++)
        Mix_PlayChannel(-1,levComplete,0);
    Menu::handleEvents(e);
    switch (option)
    {
    case NEXT:
    {
        Mix_PlayChannel(-1,selectSound,0);
        Mix_PlayChannel(-1,levStart,0);
        alive = false;
        option = -1;
        proceed = 0;
        playOnce = 0;
        break;
    }
    case QUIT:
    {
        Mix_PlayChannel(-1,selectSound,0);
        playOnce = 0;
        alive = false;
        resetGame = true;
        mainMenu->setAlive(true);
        option = -1;
        Mix_PlayMusic(menuMus,-1);
        break;
    }
    }
}


