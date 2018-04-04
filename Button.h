#ifndef BUTTON_H
#define BUTTON_H

#include <map>
#include "Entity.h"
#include "Text.h"
#include "SDL.h"

class Button : public Entity
{
public:
    /** Default constructor */
    Button(LTexture*,Point pos = Point());
    /** Default destructor */
    virtual ~Button();
    // Render the button on screen
    void render(SDL_Renderer*);
    // Change the size of the button. by default is 1
    void setSize(float scale);
    // Change the position of the button
    void setPosition(int x, int y);
    // Two Rects, one for raised ,and one for when cursor hovers over it
    SDL_Rect buttonRects[2];
    // The state. Raised or cursor inside
    int State = 0;
    // The text on the button
    Text* buttonText = NULL;



private:
    float buttonSize = 1;

};

#endif // BUTTON_H
