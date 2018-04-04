#include "FileIO.h"

FileIO::FileIO(int mode):mode(mode)         //by default goes to level loading mode
{}

FileIO::~FileIO()
{
    closeFile();
}

int FileIO::openFile(string filename)       //Opens a file for processing, returns 1 if file opens successfully, 0 if there's an error opening the file, and -1 if unspecified mode is passed
{
    if(mode==LOAD_LEVEL || mode==LOAD_STATE)
    {
        inFile.open(filename);
        return !inFile.fail();
    }
    else if(mode==SAVE_STATE)
    {
        outFile.open(filename);
        return !outFile.fail();
    }
    else        //if mode is unspecified
    {
        return -1;
    }

}

bool FileIO::checkFile()        //checks if the loaded file is according to the specified format, For format details, view Levels\ReadMe.txt
{
    bool valid=true;
    unsigned int line=1;
    if (mode==LOAD_LEVEL)   //file is valid if characters on each line are less than 20, since this is our set dimension for the board
    {
        while(!inFile.eof())
        {
            if (line ==1 && inFile.peek() == EOF)  // peek the character without reading it, just in case the file is not empty, so that cursor doesn't need to be reset
            {
                valid=false;        //doesn't  load if empty
                break;
            }
            else
            {
                string outputText;
                getline(inFile, outputText);
                line++;
                if (outputText.length() <=COL && line <= ROW+1)     //Checks if the dimensions of the file are satisfying the set conditions
                    continue;
                else         //doesn't load if not
                {
                    valid=false;
                    break;
                }
            }
        }
    }
    else if(mode==LOAD_STATE)
    {
        int emptyLine = 0;
        while(!inFile.eof())
        {
            if (line ==1 && inFile.peek() == EOF)  // peek the character without reading it, just in case the file is not empty, so that cursor doesn't need to be reset
            {
                valid=false;        //doesn't load if empty
                break;
            }
            else
            {
                string outputText;
                getline(inFile, outputText);
                line++;
                if (outputText.length() >= 5)       //Checks if at least the position and type of an entity are given in the file
                    continue;
                else if (++emptyLine > 1)        //If more than one empty line, file will not load
                {
                    valid=false;
                    break;
                }
            }
        }
        if (line <= 2)      // if just paddle and ball on the saved file, or less, file will not load
        {
            valid = false;
        }
    }
    //Resetting file cursors to beginning, by def if we arrive here this means that the file is valid
    inFile.clear();
    inFile.seekg(0, inFile.beg);
    outFile.clear();
    return valid;
}

void FileIO::closeFile()        //needed if file is not loaded and one needs to move on to the default file
{
    inFile.close();
    outFile.close();
}

void FileIO::handleFile(Board* gameBoard, Game* game)       //does the processing of the loaded file
{
    List* playerEnt = game->getPlayerEnt();     //Getting the list for loading or saving paddle, ball(s), bullet(s), missile(s), powerUP(s) and resistant bullet(s)
    List* worldEnt = game->getWorldEnt();       //getting the list for loading or saving the bricks



    if (mode==LOAD_LEVEL)
    {
        /*the board boxes are 30 px width, two of them in a board row total 60px,
        each brick is 48 px, 20 can be accommodated on the board so 60 + (48*20) = 1020
        screen resolution was 1024 so offset of 2 on each side and top and bottom for maintaining symmetry*/
        const int offsetX=2;
        const int offsetY=2;

        Point spawnPoint(gameBoard->bounds.x + offsetX,gameBoard->bounds.y + offsetY);      //setting the first spawn point
        Point startPoint=spawnPoint;        //for the first brick

        Brick* b = NULL;            //The brick declared once, will be used again and again for each brick being loaded
        char outputChar;            //The char to store the read char
        worldEnt->empty();          //Force cleaning to be sure no entity remains in the list before level loading
        while(inFile.get(outputChar))       //file reading and loading start
        {
            if(outputChar=='1')
            {
                b=new OneHitBrick(gameBoard->gSpriteSheetTexture,gameBoard,spawnPoint);
                spawnPoint++;
            }
            else if (outputChar=='2')
            {
                b=new TwoHitBrick(gameBoard->gSpriteSheetTexture,gameBoard,spawnPoint);
                spawnPoint++;
            }
            else if (outputChar=='3')
            {
                b=new ThreeHitBrick(gameBoard->gSpriteSheetTexture,gameBoard,spawnPoint);
                spawnPoint++;
            }
            else if (outputChar=='s')
            {
                b=new SteelBrick(gameBoard->gSpriteSheetTexture,gameBoard,spawnPoint);
                spawnPoint++;
            }
            else if (outputChar=='x')
            {
                b=new MobileBrickX(gameBoard->gSpriteSheetTexture,gameBoard,spawnPoint);
                spawnPoint++;
            }
            else if (outputChar=='y')
            {
                b=new MobileBrickY(gameBoard->gSpriteSheetTexture,gameBoard,spawnPoint);
                spawnPoint++;
            }
            else if (outputChar=='i')
            {
                b=new InvisibleBrick(gameBoard->gSpriteSheetTexture,gameBoard,spawnPoint);
                spawnPoint++;
            }
            else if (outputChar=='b')
            {
                b=new BossBrick(gameBoard->gSpriteSheetTexture,gameBoard,spawnPoint);
                spawnPoint++;
            }
            else if (outputChar=='\n')      //Shifting row
            {
                ++startPoint;
                spawnPoint=startPoint;
                b=NULL;
            }
            else //case for spaces and all unspecified characters
            {
                b=NULL;
                spawnPoint++;
            }
            if(b)       //if a brick is loaded, then appending it to the list
            {
                worldEnt->append(b);
            }
        }
        return;
    }
    else if (mode==SAVE_STATE) // Works when game is exited with save, and will save the relevant info separated by spaces for each entity and the GUI info as well
    {
        outFile << "Lives ";
        outFile << game->getLives() << endl;

        outFile << "Score ";
        outFile << game->getScore() << endl;

        outFile << "Time ";
        outFile << game->getGameTimer() << endl;

        outFile << "Level ";
        outFile << game->getLevelNum() <<endl;

        outFile << "NumBalls ";
        outFile << game->getNumBalls() << endl;

        Node* tmp= worldEnt->getStart();    //Takes the starting node of the list containing all the entities except for paddle, ball and smashers
        //Starting the saving of the worldEnt entities
        while(tmp)
        {
            Entity* entSave = tmp->ent;         //Will be the same for all entities
            if (entSave->getAlive())                //If the entity is alive then only save it
            {
                int type = entSave->getType();          //Gets the type of the entity and then will accordingly save the information
                outFile << type;        //Stores the type on the first position
                outFile << ' ';
                outFile << entSave->getPos() << ' ';
                if (type == Entity::ONEHITBRICK)
                {
                    outFile << entSave->getColor() << ' ' ;
                    outFile << entSave->getPower() << endl ;
                }
                else if (type == Entity::TWOHITBRICK)
                {
                    outFile << entSave->getColor() << ' ' ;
                    outFile << entSave->getPower() << ' ' ;
                    outFile << entSave->getDamage() << endl;
                }
                else if (type == Entity::THREEHITBRICK)
                {
                    outFile << entSave->getColor() << ' ' ;
                    outFile << entSave->getPower() << ' ' ;
                    outFile << entSave->getDamage() << endl;
                }
                else if (type == Entity::STEELBRICK)
                {
                    outFile << entSave->getPower() << endl ;
                }
                else if (type == Entity::MOBILEBRICKX)
                {
                    outFile << entSave->getColor() << ' ' ;
                    outFile << entSave->getPower() << ' ' ;
                    outFile << entSave->getSpeed() << endl;
                }
                else if (type == Entity::MOBILEBRICKY)
                {
                    outFile << entSave->getColor() << ' ' ;
                    outFile << entSave->getPower() << endl;
                }
                else if (type == Entity::BOSSBRICK)
                {
                    outFile << entSave->getColor() << ' ' ;
                    outFile << entSave->getPower() << ' ';
                    outFile << entSave->getDamage()<< endl;
                }
                else if (type == Entity::INVBRICK)
                {
                    outFile << entSave->getColor() << ' ' ;
                    outFile << entSave->getPower() << ' ' ;
                    outFile << entSave->getDamage() << endl;
                }
                else if (type == Entity::POWERUP)
                {
                    outFile << entSave->getWhich() << endl;
                }
            }
            tmp=tmp->next;
        }
        Node* tmp2 = playerEnt->getStart();
        while(tmp2)
        {
            Entity* entSave2 = tmp2->ent;       //Same for all entities
            if (entSave2->getAlive())
            {
                int type = entSave2->getType();         //Gets the type of the entity and then accordingly stores the info
                outFile << type;
                outFile << ' ';
                outFile << entSave2->getPos() << ' ';
                if (type == Entity::PADDLE)
                {
                    outFile << entSave2->getPaddleMode()<< ' ';
                    outFile << entSave2->getPaddleSize()<<' ';
                    outFile << entSave2->getModeTime()<<' ';
                    outFile << entSave2->getSizeTime()<<endl;
                }
                else if (type == Entity::BALL)
                {
                    outFile << entSave2->getBallType()<<' ';
                    outFile << entSave2->getDX()<<' ';
                    outFile << entSave2->getDY()<<' ';
                    outFile << entSave2->getBallPowerTime()<<' ';
                    outFile << entSave2->isPrimary()<<endl;
                }
                else if (type == Entity::NORMBULLET || type == Entity::RESISTANTBULLET || type == Entity::MISSILE)      //Smashers just need position
                {
                    outFile << endl;
                }
            }
            tmp2 = tmp2->next;
        }
        return;
    }
    else if(mode==LOAD_STATE)
    {
        string outputLine;          //String to store a whole line of the file being read

        //Keeping some global variables, which are used for all/most entities. Extras are within each's condition
        int toLoad1;
        bool toLoad2;
        int toLoad3;

        //Gets the ball and pad from the game
        Ball* ball = game->getGameBall();
        Paddle* pad = game->getGamePad();

        Brick* b = NULL;        //As many entities are of type brick

        //To get the type of entity
        string typeStr;
        int loadType = -1;

        Point spawnPoint(0,0);

        worldEnt->empty();
        while(!inFile.eof())
        {
            //Some strings that will be used everytime to act as primary stage, from load, to converting to bool or int using stringstream
            string x = "";
            string y = "";
            string tl1 = "";
            string tl2 = "";
            string tl3 = "";

            /*The int c used in all for loops, is a counter for spaces,  which will tell us when to move
            on to the next attribute which is to be loaded. Accordingly the loaded strings will be respectively
            converted to the corresponding type of variable that is to be loaded, and then set to the entity
            accordingly. Information regarding the stored items should be known to understand, hence look up saving first.*/

            getline(inFile,outputLine);     //reads the lines
            for (auto i : outputLine)       //to get the type of the entity
            {
                if(i == ' ') break;
                else typeStr += i;
            }
            if (typeStr == "Lives")
            {
                int c = 0;
                for(auto i:outputLine)
                {
                    if (i == ' ') c++;
                    if (c == 1) tl1 += i;
                }
                stringstream for_tl1(tl1);
                for_tl1 >> toLoad1;
                game->setLives(toLoad1);
            }
            else if(typeStr == "Score")
            {
                int c = 0;
                for(auto i:outputLine)
                {
                    if (i == ' ') c++;
                    if (c == 1) tl1 += i;
                }
                stringstream for_tl1(tl1);
                for_tl1 >> toLoad1;
                game->setScore(toLoad1);
            }
            else if(typeStr == "Time")
            {
                Uint32 loadTicks;
                int c = 0;
                for(auto i:outputLine)
                {
                    if (i == ' ') c++;
                    if (c == 1) tl1 += i;
                }
                stringstream for_tl1(tl1);
                for_tl1 >> loadTicks;
                game->setGameTime(loadTicks);
            }
            else if(typeStr == "Level")
            {
                int c = 0;
                for(auto i:outputLine)
                {
                    if (i == ' ') c++;
                    if (c == 1) tl1 += i;
                }
                stringstream for_tl1(tl1);
                for_tl1 >> toLoad1;
                game->setLevelNum(toLoad1);
            }
            else if (typeStr == "NumBalls")
            {
                int c = 0;
                for(auto i:outputLine)
                {
                    if (i == ' ') c++;
                    if (c == 1) tl1 += i;
                }
                stringstream for_tl1(tl1);
                for_tl1 >> toLoad1;
                game->setNumBalls(toLoad1);
            }
            else            //For entity type
            {
                stringstream for_type(typeStr);     //middle ground between the conversion (all stringstreams are so)
                for_type >> loadType;                   //The integer according to which entity to be loaded will be selected


                if( loadType == Entity::ONEHITBRICK )
                {
                    int c = 0;
                    for(auto i:outputLine)
                    {
                        if (i == ' ') c++;
                        if (c == 1) x += i;
                        else if (c == 2) y += i;
                        else if (c == 3) tl1 = i;
                        else if (c == 4) tl2 = i;
                    }
                    stringstream for_x(x);
                    stringstream for_y(y);
                    stringstream for_tl1(tl1);
                    stringstream for_tl2(tl2);
                    for_x >> spawnPoint.x;
                    for_y >> spawnPoint.y;
                    for_tl1 >> toLoad1;
                    for_tl2 >> toLoad2;
                    b = new OneHitBrick(gameBoard->gSpriteSheetTexture,gameBoard,spawnPoint);
                    b->setPowered(toLoad2);
                    b->setColor(toLoad1);
                    worldEnt->append(b);
                }
                else if( loadType == Entity::TWOHITBRICK)
                {
                    int c = 0;
                    for(auto i:outputLine)
                    {
                        if (i == ' ') c++;
                        if (c == 1) x += i;
                        else if (c == 2) y += i;
                        else if (c == 3) tl1 = i;
                        else if (c == 4) tl2 = i;
                        else if (c == 5) tl3 += i;
                    }
                    stringstream for_x(x);
                    stringstream for_y(y);
                    stringstream for_tl1(tl1);
                    stringstream for_tl2(tl2);
                    stringstream for_tl3(tl3);
                    for_x >> spawnPoint.x;
                    for_y >> spawnPoint.y;
                    for_tl1 >> toLoad1;
                    for_tl2 >> toLoad2;
                    for_tl3 >> toLoad3;
                    b = new TwoHitBrick(gameBoard->gSpriteSheetTexture,gameBoard,spawnPoint);
                    b->setPowered(toLoad2);
                    b->setColor(toLoad1);
                    b->setDamage(toLoad3);
                    worldEnt->append(b);
                }
                else if( loadType == Entity::THREEHITBRICK )
                {
                    int c = 0;
                    for(auto i:outputLine)
                    {
                        if (i == ' ') c++;
                        if (c == 1) x += i;
                        else if (c == 2) y += i;
                        else if (c == 3) tl1 = i;
                        else if (c == 4) tl2 = i;
                        else if (c == 5) tl3 += i;
                    }
                    stringstream for_x(x);
                    stringstream for_y(y);
                    stringstream for_tl1(tl1);
                    stringstream for_tl2(tl2);
                    stringstream for_tl3(tl3);
                    for_x >> spawnPoint.x;
                    for_y >> spawnPoint.y;
                    for_tl1 >> toLoad1;
                    for_tl2 >> toLoad2;
                    for_tl3 >> toLoad3;
                    b = new ThreeHitBrick(gameBoard->gSpriteSheetTexture,gameBoard,spawnPoint);
                    b->setPowered(toLoad2);
                    b->setColor(toLoad1);
                    b->setDamage(toLoad3);
                    worldEnt->append(b);
                }
                else if( loadType == Entity::STEELBRICK )
                {
                    int c = 0;
                    for(auto i:outputLine)
                    {
                        if (i == ' ') c++;
                        if (c == 1) x += i;
                        else if (c == 2) y += i;
                        else if (c == 3) tl2 = i;
                    }
                    stringstream for_x(x);
                    stringstream for_y(y);
                    stringstream for_tl2(tl2);
                    for_x >> spawnPoint.x;
                    for_y >> spawnPoint.y;
                    for_tl2 >> toLoad2;
                    b = new SteelBrick(gameBoard->gSpriteSheetTexture,gameBoard,spawnPoint);
                    b->setPowered(toLoad2);
                    worldEnt->append(b);
                }
                else if( loadType == Entity::MOBILEBRICKX )
                {
                    int c = 0;
                    for(auto i:outputLine)
                    {
                        if (i == ' ') c++;
                        if (c == 1) x += i;
                        else if (c == 2) y += i;
                        else if (c == 3) tl1 = i;
                        else if (c == 4) tl2 = i;
                    }
                    stringstream for_x(x);
                    stringstream for_y(y);
                    stringstream for_tl1(tl1);
                    stringstream for_tl2(tl2);
                    for_x >> spawnPoint.x;
                    for_y >> spawnPoint.y;
                    for_tl2 >> toLoad2;
                    for_tl1 >> toLoad1;
                    b = new MobileBrickX(gameBoard->gSpriteSheetTexture,gameBoard,spawnPoint);
                    b->setPowered(toLoad2);
                    b->setColor(toLoad1);
                    worldEnt->append(b);
                }
                else if( loadType == Entity::MOBILEBRICKY )
                {
                    int c = 0;
                    for(auto i:outputLine)
                    {
                        if (i == ' ') c++;
                        if (c == 1) x += i;
                        else if (c == 2) y += i;
                        else if (c == 3) tl1 = i;
                        else if (c == 4) tl2 = i;
                    }
                    stringstream for_x(x);
                    stringstream for_y(y);
                    stringstream for_tl1(tl1);
                    stringstream for_tl2(tl2);
                    for_x >> spawnPoint.x;
                    for_y >> spawnPoint.y;
                    for_tl2 >> toLoad2;
                    for_tl1 >> toLoad1;
                    b = new MobileBrickY(gameBoard->gSpriteSheetTexture,gameBoard,spawnPoint);
                    b->setPowered(toLoad2);
                    b->setColor(toLoad1);
                    worldEnt->append(b);
                }
                else if( loadType == Entity::INVBRICK )
                {
                    int c = 0;
                    for(auto i:outputLine)
                    {
                        if (i == ' ') c++;
                        if (c == 1) x += i;
                        else if (c == 2) y += i;
                        else if (c == 3) tl1 = i;
                        else if (c == 4) tl2 = i;
                        else if (c == 5) tl3 += i;
                    }
                    stringstream for_x(x);
                    stringstream for_y(y);
                    stringstream for_tl1(tl1);
                    stringstream for_tl2(tl2);
                    stringstream for_tl3(tl3);
                    for_x >> spawnPoint.x;
                    for_y >> spawnPoint.y;
                    for_tl1 >> toLoad1;
                    for_tl2 >> toLoad2;
                    for_tl3 >> toLoad3;
                    b = new InvisibleBrick(gameBoard->gSpriteSheetTexture,gameBoard,spawnPoint);
                    b->setPowered(toLoad2);
                    b->setColor(toLoad1);
                    b->setDamage(toLoad3);
                    worldEnt->append(b);
                }
                else if( loadType == Entity::BOSSBRICK )
                {
                    int c = 0;
                    for(auto i:outputLine)
                    {
                        if (i == ' ') c++;
                        if (c == 1) x += i;
                        else if (c == 2) y += i;
                        else if (c == 3) tl1 = i;
                        else if (c == 4) tl2 = i;
                        else if (c == 5) tl3 += i;
                    }
                    stringstream for_x(x);
                    stringstream for_y(y);
                    stringstream for_tl1(tl1);
                    stringstream for_tl2(tl2);
                    stringstream for_tl3(tl3);
                    for_x >> spawnPoint.x;
                    for_y >> spawnPoint.y;
                    for_tl1 >> toLoad1;
                    for_tl2 >> toLoad2;
                    for_tl3 >> toLoad3;
                    b = new BossBrick(gameBoard->gSpriteSheetTexture,gameBoard,spawnPoint);
                    b->setPowered(toLoad2);
                    b->setColor(toLoad1);
                    b->setDamage(toLoad3);
                    worldEnt->append(b);                //Bricks have damage, color, powered, position, type mostly to be stored
                }
                else if (loadType == Entity::PADDLE)
                {
                    string tlModeTime = "";
                    string tlSizeTime = "";
                    int toLoadModeTime = 0;
                    int toLoadSizeTime = 0;
                    int c = 0;
                    for (auto i:outputLine)
                    {
                        if (i == ' ') c++;
                        if (c == 1) x += i;
                        else if (c == 2) y += i;
                        else if (c == 3) tl1 += i;
                        else if (c == 4) tl3 += i;
                        else if (c == 5) tlModeTime += i;
                        else if (c == 6) tlSizeTime += i;
                    }
                    stringstream for_x(x);
                    stringstream for_y(y);
                    stringstream for_tl1(tl1);
                    stringstream for_tl3(tl3);
                    stringstream for_tlModeTime(tlModeTime);
                    stringstream for_tlSizeTime(tlSizeTime);
                    for_x >> spawnPoint.x;
                    for_y >> spawnPoint.y;
                    for_tl3 >> toLoad3;
                    for_tl1 >> toLoad1;
                    for_tlModeTime >> toLoadModeTime;
                    for_tlSizeTime >> toLoadSizeTime;
                    pad->setPos(spawnPoint);
                    pad->setPaddleMode(toLoad1);
                    pad->setPaddleSize(toLoad3);
                    pad->setModeTime(toLoadModeTime);
                    pad->setSizeTime(toLoadSizeTime);
                }
                else if (loadType == Entity::BALL)
                {
                    int c = 0;
                    int toLoadBallPowerTime = 0;
                    string tlBallPowerTime = "";
                    string tlPrim = "";
                    bool primary = 0;
                    for (auto i:outputLine)
                    {
                        if (i == ' ') c++;
                        if (c == 1) x += i;
                        else if (c == 2) y += i;
                        else if (c == 3) tl1 += i;
                        else if (c == 4) tl2 += i;
                        else if (c == 5) tl3 += i;
                        else if (c == 6) tlBallPowerTime += i;
                        else if (c == 7) tlPrim = i;
                    }
                    stringstream for_x(x);
                    stringstream for_y(y);
                    stringstream for_tl1(tl1);
                    stringstream for_tl2(tl2);
                    stringstream for_tl3(tl3);
                    stringstream for_tlBallPowerTime(tlBallPowerTime);
                    stringstream for_tlPrim(tlPrim);
                    float dy;
                    float dx;
                    for_x >> spawnPoint.x;
                    for_y >> spawnPoint.y;
                    for_tl2 >> dx;
                    for_tl3 >> dy;
                    for_tl1 >> toLoad1;
                    for_tlBallPowerTime >> toLoadBallPowerTime;
                    for_tlPrim >> primary;
                    if (primary)        //Only the primary ball will update the gameBall
                    {
                        ball->setStick(false);
                        ball->setPos(spawnPoint);
                        ball->setBallType(toLoad1);
                        ball->setDir(dx,dy);
                        ball->setPowerTime(toLoadBallPowerTime);
                    }
                    else            //others will just append into the game
                    {
                        Ball* ball2 = new Ball(gameBoard->gSpriteSheetTexture, gameBoard, pad, false);
                        ball2->setStick(false);
                        ball2->setPos(spawnPoint);
                        ball2->setBallType(toLoad1);
                        ball2->setDir(dx,dy);
                        playerEnt->append(ball2);
                    }
                }
                else if( loadType == Entity::POWERUP )
                {
                    PowerUp* p;
                    int c = 0;
                    for(auto i:outputLine)
                    {
                        if (i == ' ') c++;
                        if (c == 1) x += i;
                        else if (c == 2) y += i;
                        else if (c == 3) tl1= i;
                    }
                    stringstream for_x(x);
                    stringstream for_y(y);
                    stringstream for_which(tl1);
                    for_x >> spawnPoint.x;
                    for_y >> spawnPoint.y;
                    for_which >> toLoad1;
                    p = new PowerUp(gameBoard->gSpriteSheetTexture,gameBoard,spawnPoint);
                    p->setWhich(toLoad1);
                    worldEnt->append(p);
                }
                else if( loadType == Entity::NORMBULLET )
                {
                    int c = 0;
                    for(auto i:outputLine)
                    {
                        if (i == ' ') c++;
                        if (c == 1) x += i;
                        else if (c == 2) y += i;
                    }
                    stringstream for_x(x);
                    stringstream for_y(y);
                    for_x >> spawnPoint.x;
                    for_y >> spawnPoint.y;
                    Bullet* bul = new Bullet(gameBoard->gSpriteSheetTexture,gameBoard, pad, Bullet::LEFT);
                    bul->setPos(spawnPoint);
                    playerEnt->append(bul);
                }
                else if(loadType == Entity::MISSILE)
                {
                    int c = 0;
                    for(auto i:outputLine)
                    {
                        if (i == ' ') c++;
                        if (c == 1) x += i;
                        else if (c == 2) y += i;
                    }
                    stringstream for_x(x);
                    stringstream for_y(y);
                    for_x >> spawnPoint.x;
                    for_y >> spawnPoint.y;
                    Missile* miss = new Missile(gameBoard->gSpriteSheetTexture,gameBoard, pad);
                    miss->setPos(spawnPoint);
                    playerEnt->append(miss);
                }
                else if(loadType == Entity::RESISTANTBULLET)
                {
                    int c = 0;
                    for(auto i:outputLine)
                    {
                        if (i == ' ') c++;
                        if (c == 1) x += i;
                        else if (c == 2) y += i;
                    }
                    stringstream for_x(x);
                    stringstream for_y(y);
                    for_x >> spawnPoint.x;
                    for_y >> spawnPoint.y;
                    ResistantBullet* bul = new ResistantBullet(gameBoard->gSpriteSheetTexture,gameBoard, pad, Bullet::LEFT);
                    bul->setPos(spawnPoint);
                    playerEnt->append(bul);
                }
            }
            typeStr = "";
            loadType = -1;
        }
        return;
    }
    return;
}



