#include "transform.h"

using namespace std;

Transform::Transform() {}

Rotate::Rotate(double angle, double x, double y, double z) {
    this->angle = angle;
    this->x = x;
    this->y = y;
    this->z = z;
}

Translate::Translate(double x, double y, double z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

Scale::Scale(double x, double y, double z) {
    this->x = x;
    this->y = y;
    this->z = z;
}
