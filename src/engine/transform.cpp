#include <iostream>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "transform.h"

using namespace std;

Transform::Transform() {}
void Transform::apply() {}

Rotate::Rotate(double time, double angle, double x, double y, double z) {
	this->time = time;
	this->angle = angle;
    this->x = x;
    this->y = y;
    this->z = z;
    
}

void Rotate::apply() {
    glRotated(this->angle, this->x, this->y, this->z);
}

Translate::Translate(double time, double x, double y, double z) {
	this->time = time;
	this->x = x;
    this->y = y;
    this->z = z;

}

void Translate::apply() {
    glTranslated(this->x, this->y, this->z);
}

Scale::Scale(double x, double y, double z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

void Scale::apply() {
    glScaled(this->x, this->y, this->z);
}
