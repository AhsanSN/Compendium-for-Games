#include "Point.h"
using namespace std;
ostream& operator <<(ostream& stream,const Point& toPrint) //Used for writing the position of the point to the file in one go
{
    stream << toPrint.x<< ' ' << toPrint.y;
    return stream;
}
