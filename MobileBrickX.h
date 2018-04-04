#ifndef MOBILEBRICKX_H
#define MOBILEBRICKX_H
#include "MobileBrick.h"

//Specialized MobileBrick, can move only horizontally

class MobileBrickX: virtual public MobileBrick//Reason for virtual inheritance is the multiply inheriting BossBrick. Refer to its .h for explanation
{
public:
    MobileBrickX(LTexture*,Board*,Point);
    void move(List*);
};

#endif // MOBILEBRICKX_H
