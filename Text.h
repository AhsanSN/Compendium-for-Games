#ifndef TEXT_H
#define TEXT_H
#include <map>
#include "Entity.h"
#include "SDL.h"

using namespace std;

class Text:public Entity
{
public:
    // Default constructor
    Text(string text,LTexture*,Point pos = Point());
    // Default destructor
    virtual ~Text();
    // Copy constructor
    Text(const Text& other);
    //render on screen
    void render(SDL_Renderer* gRenderer);
    //change the size
    void setSize(float tSize);
    //handle the events.
    void handleEvents(SDL_Event& e);
    //change the position on the screen
    void setPosition(float x, float y);
    //change the text
    void setText(string str);
    //text color. black or white
    int color;
protected:

private:
    //dict of chars. and their respective positions on the sprite sheet
    map<char,SDL_Rect> Characters;
    // default size
    float textSize = 1;
    int SCREEN_WIDTH,SCREEN_HEIGHT;
    // the text, literally
    string text;
};

#endif // TEXT_H
