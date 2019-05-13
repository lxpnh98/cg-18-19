#ifndef COLOUR
#define COLOUR

#include <string>

class Colour {
    private:
        float red;
        float green;
        float blue;

    public:
        Colour();
        Colour(float corR, float corG, float corB);
        float getCorR();
        float getCorG();
        float getCorB();
};

#endif//Colour