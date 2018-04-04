#ifndef GAME_H
#define GAME_H
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <stdio.h>
#include <string>
#include <sstream>
#include <cstdlib>
#include <time.h>
#include <fstream>
#include <sstream>
#include "LTexture.h"
#include "Board.h"
#include "FileIO.h"
#include "OneHitBrick.h"
#include "TwoHitBrick.h"
#include "ThreeHitBrick.h"
#include "SteelBrick.h"
#include "MobileBrickX.h"
#include "MobileBrickY.h"
#include "InvisibleBrick.h"
#include "BossBrick.h"
#include "Point.h"
#include "List.h"
#include "Paddle.h"
#include "MainMenu.h"
#include "Ball.h"
#include "Bullet.h"
#include "ResistantBullet.h"
#include "Missile.h"
#include "PowerUp.h"
#include "GUI.h"
#include "PauseMenu.h"
#include "LoadGameScreen.h"
#include "Screens.h"
#include "GameOver.h"
#include "GameCompleteScreen.h"

class Game
{
public:
    Game();//ctor

    ~Game();//dtor

    bool init();//called directly by the ctor, initializes SDL subsystems and creates window + renderer

    bool loadMedia();//loads texture images and sound files

    void loadMenus();//loads all menus and screens onto the vectors

    void close();//shuts down SDL_Subsystems, frees textures and frees chunks

    void gameLoop();//handles all the game events and presents the changes to the front buffer renderer

    void handleEvents(SDL_Event&, bool&, bool&, bool&, bool&);//helper for assisting mouse press and release events

    void collisionHandler(Entity*,Entity*);//basic collision Handler, handles all in-Game collisions b/w two entities

    void collisionHandler(List*); //helper for ball-paddle collisions

    void collisionHandler(Entity*,List*);//helper for ball-brick collisions

    void collisionHandler(List*, List*);//helper for playerEntity-worldEntity collisions

    void levelLoader(string = "");//method for loading levels onto the board from the text file, through the FileIO class

    void stateSaver(string = "");//method for saving the game state, through the FileIO class

    void stateLoader(string = "");//method for loading a saved state, through the FileIO Class


    ///Getters and Setters for FILE-IO

    Ball* getGameBall();//returns a Pointer to the game Ball

    Paddle* getGamePad();

    List* getPlayerEnt();

    List* getWorldEnt();

    GUI* getGameGUI();

    int getLives();

    void setLives(int);

    int getScore();

    void setScore(int);

    int getLevelNum();

    void setLevelNum(int);

    int getNumBalls();

    void setNumBalls(int);

    Uint32 getGameTimer();

    void setGameTime(Uint32);

    int calculateBonus(int score,int time);//method for calculating game bonus score, depending on the time taken to complete a level

private:
    //The window we'll be rendering to
    SDL_Window* gWindow = NULL;
    //The window renderer
    SDL_Renderer* gRenderer = NULL;
    //The gameboard, i.e. walls
    Board* gameBoard=NULL;
    //The Main Menu
    MainMenu* mainMenu = NULL;
    //Game GUI
    GUI* gameGUI = NULL;
    //Splash Screen
    Screen* splashScreen = NULL;
    //Pause Menu
    PauseMenu* pauseMenu = NULL;
    //Load States Screen
    LoadGameScreen* loadState = NULL;
    //GameOver Screen
    GameOver* gameOver = NULL;
    //levelComplete Screen
    GameCompleteScreen* levelComplete = NULL;
    //Controls Screen
    Screen* controlsScreen = NULL;
    //Vector of Menus
    vector <Menu*>Menus;
    //Vector of Screens
    vector <Screen*> Screens;


///Screen Dimensions
    const int SCREEN_WIDTH = 1024;
    const int SCREEN_HEIGHT = 768;

    ///Game attributes
    int lives;
    int score;
    int levelNum;
    List playerEnt;//used for storing player entities
    List worldEnt;//used for storing world entities
    Uint32 firstTick;//for assisting in calculating game time
    Uint32 gameTimer;//stores game Timer
    int numBalls;
    Paddle* pad;
    Ball* ball;

    ///All textures
    //The spritesheet
    LTexture gSpriteSheetTexture;
    //Texture for Main Menu
    LTexture mainMenuTexture;
    //Texture for Pause Menu
    LTexture pauseMenuTexture;
    //Texture for Splash Screen
    LTexture splashTexture;
    //Texture for Controls Screen
    LTexture controlsTexture;

    ///Music Chunks
    Mix_Chunk* splashSound = NULL;
    //Chunks for collisions and other sound effects
    //ball brick collision sound
    Mix_Chunk* ballBrick = NULL;
    //powerup collect sound
    Mix_Chunk* poweringUP = NULL;
    //death sound
    Mix_Chunk* death = NULL;
    //lev Fail sound
    Mix_Chunk* levFail = NULL;
    //Gameover music
    Mix_Music* gameOverMus = NULL;
    //Ball-steelbrick sound
    Mix_Chunk* steelBall = NULL;


};

#endif // GAME_H
