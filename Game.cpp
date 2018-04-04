#include "Game.h"

Game::Game()
{
    lives=5;
    score=0;
    levelNum=1;
    gameTimer=0;
    firstTick=0;
    numBalls=0;
    pad=NULL;
    ball=NULL;
    //will initialize the seed only once

    static bool seeded=false;
    if(!seeded)
    {
        srand(time(NULL));
    }
    init();
}

Game::~Game()
{
    //dtor
}

void Game::loadMenus()
{
    //Allocating menus, screens, and the in-game GUI
    pauseMenu = new PauseMenu(&pauseMenuTexture);
    gameOver = new GameOver(&pauseMenuTexture);
    loadState = new LoadGameScreen(&mainMenuTexture);
    loadState->setGame(this);
    mainMenu = new MainMenu(&mainMenuTexture);
    splashScreen = new Screen(&splashTexture);
    levelComplete = new GameCompleteScreen(&pauseMenuTexture);
    controlsScreen = new Screen(&controlsTexture);
    gameGUI = new GUI(&mainMenuTexture);

    //Pushing them into the STL vectors

    Menus.push_back(pauseMenu);
    Menus.push_back(mainMenu);
    Menus.push_back(gameOver);
    Menus.push_back(loadState);
    Screens.push_back(splashScreen);
    Screens.push_back(controlsScreen);

    //Setting dimensions according to the game resolution
    for (unsigned int i=0; i<Menus.size(); i++)
    {
        Menus[i]->setDimensions(SCREEN_WIDTH,SCREEN_HEIGHT);
    }
    for (unsigned int i=0; i<Screens.size(); i++)
    {
        Screens[i]->setDimensions(SCREEN_WIDTH,SCREEN_HEIGHT);
    }

    levelComplete->setDimensions(SCREEN_WIDTH,SCREEN_HEIGHT);
    gameGUI->setDimensions(SCREEN_WIDTH,SCREEN_HEIGHT);

    //Setting appropriate parent menus and next screens
    gameOver->mainMenu = mainMenu;
    pauseMenu->mMenu = mainMenu;
    loadState->parentMenu = mainMenu;
    mainMenu->loadState = loadState;
    pauseMenu->saveState = loadState;
    levelComplete->mainMenu = mainMenu;
    splashScreen->nextScreen = controlsScreen;
    controlsScreen->mainMenu = mainMenu;
    controlsScreen->setDelay(4);

    //Setting the splash to alive only
    splashScreen->setAlive(true);
    pauseMenu->setAlive(false);
    loadState->setAlive(false);
    gameOver->setAlive(false);
    controlsScreen->setAlive(false);
    levelComplete->setAlive(false);
    mainMenu->setAlive(false);
}

bool Game::init()
{
    //Initialization flag
    bool success = true;
    //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
        success = false;
    }
    else
    {
        if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
        {
            printf( "Warning: Linear texture filtering not enabled!" );
        }

        //Create windows
        gWindow = SDL_CreateWindow( "BRICRUMBLE!", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_FULLSCREEN );
        if( gWindow == NULL )
        {
            printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
            success = false;
        }
        else
        {
            //Create renderer for window
            gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
            if( gRenderer == NULL )
            {
                printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
                success = false;
            }
            else
            {
                //Initialize renderer color
                SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
                //Initialize PNG loading
                int imgFlags = IMG_INIT_PNG;
                if( !( IMG_Init( imgFlags ) & imgFlags ) )
                {
                    printf( "SDL_image could not initialize! SDL_mage Error: %s\n", IMG_GetError() );
                    success = false;
                }
                if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
                {
                    printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
                    success = false;
                }
            }
        }
    }
    if(loadMedia())
    {
        loadMenus(); //load Menus, and enter the gameLoop
        gameLoop();
    }

    return success;
}

bool Game::loadMedia()
{
    //Loading success flag
    bool success = true;
    //Load sprite sheet texture
    if( !gSpriteSheetTexture.loadFromFile( "Images/Spritesheet.png", gRenderer,0,255,255  )
            || !mainMenuTexture.loadFromFile("Images/Menu.png",gRenderer,255,0,0)
            || !pauseMenuTexture.loadFromFile("Images/Menu.png",gRenderer,255,0,0)
            || !splashTexture.loadFromFile("Images/Splash.png",gRenderer,0,0,0)
            || !controlsTexture.loadFromFile("Images/Controls.png",gRenderer,0,0,0))
    {
        printf( "Failed to load sprite sheet texture!\n" );
        success = false;
    }


    //Loading music and sounds
    splashSound = Mix_LoadWAV("Sounds/Splash.wav");
    ballBrick = Mix_LoadWAV("Sounds/ballbrick.wav");
    poweringUP = Mix_LoadWAV("Sounds/PowerUp.wav");
    death = Mix_LoadWAV("Sounds/lifelose.wav");
    levFail = Mix_LoadWAV("Sounds/LevelFail.wav");
    gameOverMus = Mix_LoadMUS("Sounds/gameover.wav");
    steelBall = Mix_LoadWAV("Sounds/ballSteel.wav");
    if( splashSound == NULL || ballBrick == NULL ||
            poweringUP == NULL || death == NULL ||
            levFail == NULL || gameOverMus == NULL || steelBall == NULL)
    {
        printf( "Failed to load sound! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }
    return success;
}

void Game::close()
{
    //Free loaded images
    gSpriteSheetTexture.free();
    mainMenuTexture.free();
    pauseMenuTexture.free();
    splashTexture.free();
    controlsTexture.free();
    //Freeing sounds
    Mix_FreeChunk(splashSound);
    splashSound = NULL;
    Mix_FreeChunk(ballBrick);
    ballBrick = NULL;
    Mix_FreeChunk(poweringUP);
    poweringUP = NULL;
    Mix_FreeChunk(death);
    death = NULL;
    Mix_FreeChunk(levFail);
    levFail = NULL;
    Mix_FreeMusic(gameOverMus);
    gameOverMus = NULL;
    Mix_FreeChunk(steelBall);
    steelBall = NULL;
    //Destroy window
    SDL_DestroyRenderer( gRenderer );
    SDL_DestroyWindow( gWindow );
    gWindow = NULL;
    gRenderer = NULL;
    gameBoard = NULL;

    delete pauseMenu;
    delete gameOver;
    delete loadState;
    delete mainMenu;
    delete splashScreen;
    delete levelComplete;
    delete controlsScreen;
    delete gameGUI;
    mainMenu = NULL;
    gameGUI = NULL;
    pauseMenu = NULL;
    splashScreen = NULL;
    loadState = NULL;
    gameOver = NULL;
    levelComplete = NULL;
    //Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
    Mix_Quit();
}

void Game::gameLoop()
{
    //Creating the board, pad, ball, adding into the list playerEnt
    gameBoard=new Board(&gSpriteSheetTexture);
    gameBoard->setDimensions(SCREEN_WIDTH,SCREEN_HEIGHT);

    pad=new Paddle(&gSpriteSheetTexture,gameBoard);//,NULL);
    ball=new Ball(&gSpriteSheetTexture,gameBoard,pad);

    playerEnt.append(pad);
    playerEnt.append(ball);


    //declaring event
    SDL_Event e;
    bool quit=false;

    //frame will be used to clean lists (whenever frame % 60==0) at the end of the loop
    long long int frame=0;

    //declaring attributes for assisting in game score & time calculations
    int totalScore =0;
    int timeDiff = 0;
    bool timeTaken = false;

    //flags for handling mouse events
    bool mouseLeftUp = false;
    bool mouseLeftDown = false;
    bool mouseRightUp = false;
    bool mouseRightDown = false;

    //flags for handling game states
    bool pause = false;
    bool complete = false;
    bool gamerun = false;

    //initializing attributes
    numBalls = 1;

    levelNum = 1;
    firstTick = SDL_GetTicks();

    static int playOnceGameOver = 0;        //For the gameOverScreen music

    while( !quit )                          //Game loop
    {
        while( SDL_PollEvent( &e ) != 0 )   //Handle events on queue
        {
            int menuAlive = 0;

            for (unsigned int i=0; i<Menus.size(); i++)
            {
                if (Menus[i]->getAlive() && !splashScreen->getAlive() && !controlsScreen->getAlive())//checking if any menu is alive
                {
                    Menus[i]->handleEvents(e);
                    gamerun = false;
                    menuAlive++;
                    break;
                }
            }
            if (menuAlive==0 && !splashScreen->getAlive() && !controlsScreen->getAlive() && mainMenu->gameStart) //if 0 menus are alive, this means the game is starting
            {
                pause = false;
                complete = false;
                if (!worldEnt.size())   //Loading level and resetting stuff if the board is empty
                {
                    playerEnt.resetEntities();
                    while(playerEnt.size()>2)//remove any additional entities(such as bullets) from the list if any remain, keep only ball and pad
                    {
                        playerEnt.removeNodeAtInd(playerEnt.size() - 1);
                    }
                    worldEnt.empty();//force clean all bricks if any before loading next level
                    levelLoader();
                }
                levelComplete->proceed = -1;
                firstTick = SDL_GetTicks();// - tickOffset ;
                mainMenu->gameStart = false;
                gamerun = true;
                if (gameBoard->isDay()) //play appropriate bg music through the Board
                    gameBoard->playDayMusic();
                else
                    gameBoard->playNightMusic();
            }

            //Handling events if the level complete screen is alive

            if (levelComplete->getAlive())
            {
                levelComplete->handleEvents(e);
            }


            if (!splashScreen->getAlive() && !controlsScreen->getAlive())
            {
                if (gameOver->gameRun) //if gameover menu continue has been selected
                {
                    gameBoard->playDayMusic();
                    playOnceGameOver=0;
                    gamerun=true;
                    levelNum=1;
                    gameTimer = 0;
                    totalScore = 0;
                    score = 0;
                    lives=5;
                    levelLoader();
                    gameOver->gameRun = false;
                    playerEnt.resetEntities();
                }
                else if (pauseMenu->resetGame || gameOver->resetGame || levelComplete->resetGame) //if pausemenu quit or gameover quit or level complete quit has been selected
                {
                    worldEnt.empty();
                    pauseMenu->resetGame = gameOver->resetGame = levelComplete->resetGame = false;
                    firstTick = SDL_GetTicks();
                    mainMenu->setAlive(true);
                    levelNum=1;
                    gameTimer = 0;
                    totalScore = 0;
                    score = 0;
                    lives=5;
                }
            }
            //User requests quit
            if( e.type == SDL_QUIT || mainMenu->getOption() == MainMenu::QUIT )
            {
                quit = true;
                Mix_HaltMusic();
            }

            if(gamerun)
            {
                if (e.type==SDL_MOUSEBUTTONDOWN)
                {
                    if (e.button.button == SDL_BUTTON_LEFT && !mainMenu->getAlive())
                    {
                        if(ball->isStuck())
                        {
                            ball->setStick(false);//unstick the ball from the paddle
                        }
                    }

                }
                if (e.type == SDL_KEYDOWN)
                {
                    //Cheat codes, 1-4 Balltypes & b multi ball, 5-0 & r Paddle modes & sizes
                    switch( e.key.keysym.sym )
                    {
                    case SDLK_1:
                        ball->setBallType(1);
                        break;
                    case SDLK_2:
                        ball->setBallType(2);
                        break;
                    case SDLK_3:
                        ball->setBallType(3);
                        break;
                    case SDLK_4:
                        ball->setBallType(0);
                        break;
                    case SDLK_5:
                        pad->fireUp();
                        break;
                    case SDLK_6:
                        pad->turtleDown();
                        break;
                    case SDLK_7:
                        pad->restoreMode();
                        break;
                    case SDLK_8:
                        pad->diminish();
                        break;
                    case SDLK_9:
                        pad->restoreSize();
                        break;
                    case SDLK_0:
                        pad->enlarge();
                        break;
                    case SDLK_r:
                        pad->rocketUp();
                        break;
                    case SDLK_ESCAPE:
                        pauseMenu->setAlive(! pauseMenu->getAlive());
                        Mix_PauseMusic();
                        break;
                    case SDLK_b:
                        Ball* ball2 = new Ball(&gSpriteSheetTexture, gameBoard, pad, false);
                        ball2->setStick(false);
                        playerEnt.append(ball2);
                        numBalls++;
                        break;
                    }
                }
                handleEvents(e, mouseLeftUp, mouseLeftDown, mouseRightUp, mouseRightDown);
                if (mouseLeftUp == true)
                {
                    if (pad->getPaddleMode() == Paddle::FIRE)
                    {
                        Bullet* leftBullet = new Bullet(&gSpriteSheetTexture,gameBoard,pad,Bullet::LEFT);
                        Bullet* rightBullet = new Bullet(&gSpriteSheetTexture,gameBoard,pad,Bullet::RIGHT);
                        playerEnt.append(leftBullet);
                        playerEnt.append(rightBullet);
                    }

                    else if(pad->getPaddleMode() == Paddle::ROCKET)
                    {
                        Missile* missile = new Missile(&gSpriteSheetTexture, gameBoard, pad);
                        playerEnt.append(missile);
                    }
                }
                else if (mouseRightUp == true && pad->getPaddleMode() == Paddle::FIRE)
                {
                    Bullet* leftBullet = new ResistantBullet(&gSpriteSheetTexture,gameBoard,pad,Bullet::LEFT);
                    Bullet* rightBullet = new ResistantBullet(&gSpriteSheetTexture,gameBoard,pad,Bullet::RIGHT);
                    playerEnt.append(leftBullet);
                    playerEnt.append(rightBullet);
                }
                mouseLeftUp = false;
                mouseRightUp = false;
            }

        }

        frame++;
        SDL_SetRenderDrawColor( gRenderer, 0, 0, 0, 0xFF );    //Clear screen
        SDL_RenderClear( gRenderer );

        //Handling screen events

        if (splashScreen->getAlive())
        {
            static int playOnce = 0;
            if (playOnce==100)
            {
                Mix_PlayChannel(-1,splashSound,0);
            }
            splashScreen->render(gRenderer);
            playOnce++;
        }

        if (lives<1)
        {
            levelNum = 1;
            gameOver->setAlive(true);
            lives = 5;
        }

        if (loadState->alive && !mainMenu->getAlive())
        {
            loadState->render(gRenderer);
        }

        else if (gamerun)
        {
            if (pauseMenu->getAlive())
            {
                pauseMenu->render(gRenderer);
            }
            else
            {
                //Collision checking and handling
                collisionHandler(&playerEnt,&worldEnt);
                collisionHandler(&playerEnt);

                //Rendering Game Board (boundaries)
                gameBoard->render(gRenderer);
                worldEnt.render(gRenderer);
                playerEnt.render(gRenderer);
                if (!pause) playerEnt.move(&worldEnt);

                //Calculating gameTime

                if (!timeTaken)
                {
                    timeDiff = (int)SDL_GetTicks()/1000;
                    timeTaken = true;
                }

                if (SDL_GetTicks()/1000 > (unsigned)timeDiff && !pause)
                {
                    timeDiff = SDL_GetTicks()/1000;
                    gameTimer++;
                }

                //Updating GUI

                gameGUI->setLives(lives);
                gameGUI->setTime(gameTimer);
                gameGUI->setScore(score);
                gameGUI->setPowerUp(pad->getPaddleMode(),ball->getBallType(),pad->getPaddleSize(),(numBalls>1));
                gameGUI->render(gRenderer);

                //calling move function on worldEntities, if game is unpaused

                if(worldEnt.size()>0)
                {
                    if (!pause) worldEnt.move();//for moving objects that will move
                }

                //lists will get cleaned every 60 frames
                if(frame%60==0)
                {
                    worldEnt.clean();//entities will get deallocaated after every 60 frames
                    playerEnt.clean();
                    frame=0;
                }

                if (levelComplete->proceed == 0)
                {
                    pause = false;
                    worldEnt.empty();//force clean all bricks if any before loadin next level
                    playerEnt.resetEntities();
                    while(playerEnt.size()>2)//remove any additional entities(such as bullets) from the list if any remain, keep only ball and pad
                    {
                        playerEnt.removeNodeAtInd(playerEnt.size() - 1);
                    }
                    worldEnt.empty();
                    levelLoader();
                    score = totalScore;
                    gameTimer = 0;
                    levelComplete->proceed = -1;
                    complete = false;
                    firstTick=SDL_GetTicks();
                }
                if(worldEnt.getBrickCount()==0 && !complete)
                {
                    //update game bonus score on completion
                    levelComplete->setAlive(true);
                    levelComplete->setBonus(calculateBonus(score,gameTimer));
                    levelComplete->setScore(score);
                    totalScore = score+calculateBonus(score,gameTimer);
                    if(totalScore>99999) totalScore=0;
                    levelComplete->setTotalScore(totalScore);
                    pause = true;
                    complete = true;
                }
            }
        }

        //Again handling screen events

        else if (!splashScreen->getAlive() && !loadState->getAlive() && mainMenu->getAlive())
        {
            mainMenu->render(gRenderer);
        }

        if (pauseMenu->getAlive()) pauseMenu->render(gRenderer);

        if (gameOver->getAlive())
        {
            if (!playOnceGameOver++)
                Mix_PlayMusic(gameOverMus,-1);
            gameOver->render(gRenderer);
        }

        if (levelComplete->getAlive())
        {
            levelComplete->render(gRenderer);
        }
        if (pauseMenu->gameRun)
        {
            gamerun = true;
            pauseMenu->gameRun = false;

        }
        if (controlsScreen->getAlive())
        {
            controlsScreen->render(gRenderer);
        }
        SDL_RenderPresent(gRenderer);
    }
    delete gameBoard;
    close();
}
void Game::handleEvents(SDL_Event& e, bool& mouseLeftUp, bool& mouseLeftDown, bool& mouseRightUp, bool& mouseRightDown)
{

    if (e.type == SDL_MOUSEBUTTONDOWN)
    {
        if (e.button.button == SDL_BUTTON_LEFT)
        {
            mouseLeftDown = true;
        }

        else if (e.button.button == SDL_BUTTON_RIGHT)
        {
            mouseRightDown = true;
        }
    }

    if (e.type == SDL_MOUSEBUTTONUP)
    {
        if (e.button.button == SDL_BUTTON_LEFT  && mouseLeftDown)
        {
            mouseLeftUp = true;
            mouseLeftDown = false;
        }

        else if (e.button.button == SDL_BUTTON_RIGHT && mouseRightDown)
        {
            mouseRightUp = true;
            mouseRightDown = false;
        }
    }
}

void Game::levelLoader(string level)
{
    stringstream stream;
    stream << "Levels/lev" << levelNum << ".txt";
    string filename="";
    if (level=="") filename = stream.str();
    else filename = level;
    FileIO file;//by default uses LOAD_LEVEL mode of FileIO

    //generating generic filenames, of the form "Levels/levX.txt"
    if (file.openFile(filename) && file.checkFile())//if the file is opened successfully & checked for proper format, load it onto the board
    {
        file.handleFile(gameBoard, this);
        levelNum++;
    }//file close handled in FileIO destructor
    else
    {
        //will load default.txt onto the board if a failure occurs in loading the given level

        file.closeFile();
        file.openFile("Levels/default.txt");
        if(file.checkFile())
        {
            file.handleFile(gameBoard, this);
            levelNum++;
        }
        else
        {
            cerr << "Error loading default level file." << endl;
            exit(-1);
        }
    }
}
void Game::stateSaver(string Name)
{
    FileIO file(FileIO::SAVE_STATE);
    static int saveNum = 1;
    stringstream stream;
    stream << "/Saved/toSave" << saveNum << ".txt";
    string fileName="";
    if (Name=="") fileName = stream.str();
    else fileName = Name;
    if (file.openFile(fileName))
    {
        file.handleFile(gameBoard,this);
        saveNum++;
    }//file close handled in FileIO destructor
}

void Game::stateLoader(string Name)
{
    FileIO file(FileIO::LOAD_STATE);
    if (file.openFile(Name) && file.checkFile())//if the file is opened successfully & checked for proper format, load it onto the board
    {
        file.handleFile(gameBoard, this);
    }//file close handled in FileIO destructor
    else
    {
        cerr << "Either file could not be created or something bad happened.\n";
    }
}

void Game::collisionHandler(Entity* ent1,Entity* ent2) //For handling all possible collisions b/w two entities
{
    //BALL BOARD COLLISIONS (DOWNWARDS), since a life needs to be subtracted

    if (ent1->getType() == Entity::BALL && ent2->getType() == Entity::PADDLE)
    {
        SDL_Rect ball=ent1->getBounds();
        SDL_Rect board=gameBoard->getBounds();
        if  (ball.y + ball.h >= board.y + board.h)
        {
            if (ent1->isPrimary())
            {
                ent1->stickToPaddle();
                if (lives > 0)
                {
                    if (--lives == 0)
                    {
                        Mix_PlayChannel(-1, levFail, 0);
                    }
                    else
                    {
                        Mix_PlayChannel(-1, death, 0);
                    }
                }
            }
            else
            {
                numBalls--;
                ent1->setAlive(false);
                ent1->setStick(false);
            }
        }
    }

    //BALL-BRICK COLLISIONS

    if (ent1->getType() == Entity::BALL && ent2->getType() <= Entity::BOSSBRICK  && ent2->getAlive()!=0)
    {
        SDL_Rect ball=ent1->getBounds();
        SDL_Rect brick=ent2->getBounds();
        SDL_Rect intersectRect;
        if (SDL_IntersectRect(&ball,&brick,&intersectRect))//if there's a collision
        {
            if (ent2->type != Entity::STEELBRICK)
                Mix_PlayChannel(-1, ballBrick, 0);

            else
                Mix_PlayChannel(-1,steelBall, 0);

            score+=25;

            //Generating a powerup if the brick had a probability

            int check_life = ent2->incrementDmg();//increase damage on the brick,collision has been detected,also store if brick would yield powerup
            if (check_life == 1)//brick has been killed
            {
                score+=50;
                if (ent2->getPower())
                {
                    Point powPos(ent2->getPos().x+ent2->getWidth()/2,ent2->getPos().y+ent2->getHeight()/2);//generating powerup if brick was powered
                    PowerUp* pow = new PowerUp(&gSpriteSheetTexture,gameBoard,powPos);
                    worldEnt.append(pow);
                }
            }
            if(ent1->getBallType()==Ball::FIRE) //Fire ball can go through bricks, breaking all
                return;
            else
            {
                if (intersectRect.w >= intersectRect.h)//TOP OR BOTTOM COLLISION
                {
                    //if ball collides with brick from top, its dy has to be +ve

                    ent1->setDir(ent1->getDX(),ent1->getDY()*-1);//reverse y dir of ball

                    //IF COLLISION IS TOP, BALL Y HAS TO BE SMALLER THAN BRICK Y

                    if(ent1->getPos().y<ent2->getPos().y)//TOP COLLISION
                    {
                        ent1->setPosY(ent2->getPos().y - ent1->getHeight());
                    }
                    else // DOWN COLLISION
                    {
                        ent1->setPosY(ent2->getPos().y + ent2->getHeight());
                    }
                }

                else//LEFT or RIGHT COLLISION
                {
                    ent1->setDir(ent1->getDX()*-1,ent1->getDY());//reverse x dir of ball

                    //IF COLLISION IS LEFT, BALL X HAS TO BE LESS THAN BRICK X

                    if(ent1->getPos().x < ent2->getPos().x)//LEFT Collision
                    {
                        ent1->setPosX(ent2->getPos().x - ent1->getWidth());
                    }
                    else//RIGHT COLLISION
                    {
                        ent1->setPosX(ent2->getPos().x + ent2->getWidth());
                    }
                }
            }
            ent1->move();
        }
        else
        {
            return;
        }
    }

    //PADDLE POWERUP COLLISIONS

    if (ent1->getType() == Entity::PADDLE && (ent2->getType() == Entity::POWERUP))
    {
        SDL_Rect paddle=ent1->getBounds();
        SDL_Rect pow=ent2->getBounds();
        if(SDL_HasIntersection(&paddle,&pow))
        {
            gameBoard->sparkleOn();
            Mix_PlayChannel(-1, poweringUP, 0);
            ent2->setAlive(0);
            if (ent2->getWhich() == PowerUp::EXTRA_LIFE)
            {
                lives++;
            }
            else if (ent2->getWhich() == PowerUp::MULTIBALL)
            {
                Ball* ball2 = new Ball(&gSpriteSheetTexture, gameBoard, pad, false);
                ball2->setStick(false);
                playerEnt.append(ball2);
                numBalls++;
            }
            else
            {
                ent2->setPower(pad, ball);
            }
            int ind = worldEnt.getEntInd(ent2);
            worldEnt.removeNodeAtInd(ind);
        }
        else
        {
            return;
        }
    }

    //BALL-PADDLE COLLISIONS

    if (ent1->getType() == Entity::BALL && ent2->getType() == Entity::PADDLE)
    {
        //BALL Bounce angle is independent of the direction at which it hits the paddle, the farther the collision point is from the paddle's center, greater will be it's deflection angle
        SDL_Rect ball=ent1->getBounds();
        SDL_Rect paddle=ent2->getBounds();
        SDL_Rect intersectRect;

        if (SDL_IntersectRect(&ball,&paddle,&intersectRect))
        {
            if(intersectRect.w > intersectRect.h)//TOP OR BOTTOM COLLISION, in this case it will always be TOP
            {
                float ballMidX = ball.x +  ball.w/2;
                float padStartX = paddle.x;
                float hitPosX = (ballMidX - padStartX)/paddle.w;
                float relativeDirX = hitPosX*4 - 2;
                float denominator = sqrt(pow(relativeDirX,2) + 1);
                ent1->takeCollisionAction(Entity::PADDLE);
                ent1->setDir(relativeDirX/denominator, -1/denominator);
            }

            else//Sideways collision with pad
            {
                if(ent1->isPrimary())
                {
                    ent1->setStick(true);
                    ent1->stickToPaddle();
                    if (lives > 0)
                    {
                        if (--lives == 0)
                        {
                            Mix_PlayChannel(-1, levFail, 0);
                        }
                        else
                        {
                            Mix_PlayChannel(-1, death, 0);
                        }
                    }
                }
                else
                {
                    numBalls--;
                    ent1->setAlive(false);
                    ent1->setStick(false);
                }

            }
        }
        else
        {
            return;
        }

    }

    //SMASHER BRICK COLLISIONS

    if ( ent1->getType() >= Entity::NORMBULLET && ent2->getType() <= Entity::BOSSBRICK  && ent1->getAlive()!=0 && ent2->getAlive()!=0)
    {
        SDL_Rect smasher=ent1->getBounds();
        SDL_Rect brick=ent2->getBounds();

        if (SDL_HasIntersection(&smasher,&brick))//if there's a collision
        {
            score+=25;
            if (ent2->getPower())
            {
                Point powPos(ent2->getPos().x+ent2->getWidth()/2,ent2->getPos().y+ent2->getHeight()/2);
                PowerUp* pow = new PowerUp(&gSpriteSheetTexture,gameBoard,powPos);
                worldEnt.append(pow);
            }

            if(ent1->getType()==Entity::RESISTANTBULLET)
            {
                ent1->takeCollisionAction(-1);
                //Take collision action
                //RESISTANT BULLET
            }
            else
            {
                ent1->setAlive(0);
                //NORM BULLET AND MISSILE
            }
            ent2->setAlive(0);//smasher brick collision detected , kill brick
        }
        else
        {
            return;
        }
    }
}

void Game::collisionHandler(Entity* ent1,List* worldEnt) //helper for ball-brick collisions
{
    Node* tmp=worldEnt->start;
    while(tmp)
    {
        collisionHandler(ent1,tmp->ent);
        tmp=tmp->next;
    }
}

void Game::collisionHandler(List* playerEnt,List* worldEnt) //helper for playerEntity-worldEntity collisions
{
    Node* tmp = playerEnt->start;
    while(tmp)
    {
        collisionHandler(tmp->ent, worldEnt);
        tmp=tmp->next;
    }
}

void Game::collisionHandler(List* playerEnt) //helper for ball-paddle collisions
{
    Node*  tmp = playerEnt->start;
    while(tmp)
    {
        if (tmp->ent->BALL)
        {
            collisionHandler(tmp->ent,pad);
        }
        tmp = tmp->next;
    }
}

int Game::calculateBonus(int score,int time)//if level is completed under 2 minutes, appropriate bonus score is calculated and returned
{
    if (time<60) return score*0.4;
    else if (time<120 && time >60) return score*0.3;
    else return 0;
}

//Simple getter and setters for FileIO

Ball* Game::getGameBall()
{
    return ball;
}

Paddle* Game::getGamePad()
{
    return pad;
}

List* Game::getWorldEnt()
{
    return &worldEnt;
}

List* Game::getPlayerEnt()
{
    return &playerEnt;
}

GUI* Game::getGameGUI()
{
    return gameGUI;
}

int Game::getLives()
{
    return lives;
}

int Game::getScore()
{
    return score;
}

void Game::setLives(int lives)
{
    this->lives = lives;
}

void Game::setScore(int score)
{
    this->score = score;
}
Uint32 Game::getGameTimer()
{
    return gameTimer;
}

void Game::setGameTime(Uint32 timer)
{
    gameTimer = timer;
}
int Game::getLevelNum()
{
    return levelNum;
}

void Game::setLevelNum(int levelNum)
{
    this->levelNum = levelNum;
}

int Game::getNumBalls()
{
    return numBalls;
}

void Game::setNumBalls(int numBalls)
{
    this->numBalls = numBalls;
}


