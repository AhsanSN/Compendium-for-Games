#ifndef FILEIO_H
#define FILEIO_H
#include <iostream>
#include <fstream>
#include "Game.h"
class Game;
using namespace std;

class FileIO
{
public:
    FileIO(int=LOAD_LEVEL);         //Constructor with default mode as the level loading mode

    ~FileIO();

    enum FILEIO_MODES {LOAD_LEVEL,SAVE_STATE,LOAD_STATE};

    int openFile(string);

    bool checkFile();       //checks if the loaded file is in correct format

    void handleFile(Board*, Game*);         //does the processing of the loaded file or loaded state, or the saving of a game state

    void closeFile();

private:
    const unsigned int COL=20;          //num of possible brick columns for level loading

    const unsigned int ROW=16;          //maximum allowed num of possible brick rows in level loading

    ifstream inFile;

    ofstream outFile;

    int mode;               //at a time one mode will be active
};

#endif // FILEIO_H
