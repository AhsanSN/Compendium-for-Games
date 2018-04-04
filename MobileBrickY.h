#ifndef MOBILEBRICKY_H
#define MOBILEBRICKY_H
#include "MobileBrick.h"

//Specialized MobileBrick, can move only vertically

class MobileBrickY :virtual public MobileBrick//Reason for virtual inheritance is the multiply inheriting BossBrick. Refer to its .h for explanation
{
public:
    MobileBrickY(LTexture*,Board*,Point);
    void move(List*);
};

#endif // MOBILEBRICKY_H
