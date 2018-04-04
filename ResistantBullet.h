#ifndef RESISTANTBULLET_H_INCLUDED
#define RESISTANTBULLET_H_INCLUDED
#include "Bullet.h"

class ResistantBullet: public Bullet
{
public:

    ResistantBullet(LTexture*, Board*, Paddle*, int);           //Constructor

    ~ResistantBullet();                     //Destructor

    void render(long int&, SDL_Renderer*);          //Renderer of the resistant bullet

    void addSmashLocation();            //adds the smash location

    void takeCollisionAction(int);          //takes action of collision according to collision subject

private:

    Point* smashes;         //Array for storing smashed points

    int numSmashes;

    int* delays;      //array for storing delays

    int* expFrames;     //array for storing expFrame
};

#endif // RESISTANTBULLET_H_INCLUDED
