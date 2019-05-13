#include "colour.h"

Colour::Colour() {
    this->red = 0.0;
    this->green = 0.0;
    this->blue = 0.0;
};

Colour::Colour(float corR, float corG, float corB) {
    this->red = corR;
    this->green = corG;
    this->blue = corB;
};

float Colour::getCorR() {
    return this->red;
}
float Colour::getCorG() {
    return this->green;
}
float Colour::getCorB() {
    return this->blue;
}