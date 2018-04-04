#ifndef MISSILE_H_INCLUDED
#define MISSILE_H_INCLUDED
#include "Smasher.h"
#include "List.h"
#include <math.h>

class Missile: public Smasher
{

public:
    Missile(LTexture*, Board*, Paddle*); // Constructor

    virtual ~Missile(); //Destructor

    enum MISSILE_TYPES {INITIAL, FINAL, NUM_MISSILE_TYPES}; // Missile sprite types

    enum MISSILE_STATES {INITIALIZING = 50, LOADING = 75, PREPARINGTOMOVE = 100, ONITSPATH = 150}; // Missile states in terms of the current count

    enum ORIENTATION_TYPES {LEFT, RIGHT}; // The possible waves that the missile may make during the course of its journey - left-orientated and right-oriented curves

    void render(SDL_Renderer*); // Render function for missile

    void move(List*); // Moves the missile as per the count variable. It takes worldEnt list as input so that it can choose a brick to target.

    bool getBrick(List*); // Called in move. Selects a brick that is unmarked and has the minimum distance from the initial position of the missile.

    void initializePosition(); // Initialize the missile according to the position of the paddle.

    void checkBrickTracking(int); // Checks whether brick is stuck or is still moving towards its target

protected:

    SDL_Rect spriteClips[NUM_MISSILE_TYPES]; // Info regarding the sprite clips of the missile

    bool brickIdentified; // Flag which tells whether the missile is able to identify a brick

    Entity* brick; // Storing the address of the brick being targeted

    int count; // Stores the current frame

    int orientation; // Maintains the orientation of the current missile

    bool brickTracked; // If the brick being tracked by missile is already exploded, this variable is set to False

    bool goneAstray; // Flag used to set free the targeted missile once

    int lastPos; // Maintains the y-coordinate of the last position of the missile

    Mix_Chunk* missileFire = NULL; //Sound for missile launch
};

#endif // MISSILE_H_INCLUDED
