
#include "light.h"

using namespace std;

Light::Light() {
}

Light::Light(int nrLight, string type, float x, float y, float z) {
	this->type = type;
	this->x = x;
	this->y = y;
	this->z = z;
	this->id = nrLight;
}

void Light::draw() {

	glEnable(GL_LIGHT0 + id);

	GLfloat amb[4] = { 0.1,0.1,0.1, 1 };
	GLfloat diff[4] = { 1, 1, 1, 0 };
	GLfloat pos[4] = { this->x, this->y , this->z, 1 };
	GLfloat spotDir[3] = { 0.0, 0.0, -1.0 };


	if (this->type == "POINT") {

		glLightfv(GL_LIGHT0 + this->id, GL_POSITION, pos);

		glLightfv(GL_LIGHT0 + this->id, GL_POSITION, pos);
		glLightfv(GL_LIGHT0 + this->id, GL_AMBIENT, amb);
		glLightfv(GL_LIGHT0 + this->id, GL_DIFFUSE, diff);

	}

	if (this->type == "SPOTLIGHT") {

		spotDir[0] = this->x;
		spotDir[1] = this->y;
		spotDir[2] = this->z;

		glLightfv(GL_LIGHT0 + this->id, GL_POSITION, pos);

		glLightfv(GL_LIGHT0 + this->id, GL_DIFFUSE, diff);
		glLightfv(GL_LIGHT0 + this->id, GL_SPOT_DIRECTION, spotDir);
		glLightf(GL_LIGHT0 + this->id, GL_SPOT_CUTOFF, 45.0);
		glLightf(GL_LIGHT0 + this->id, GL_SPOT_EXPONENT, 0.0);

	}

	if (this->type == "DIRECTIONAL") {

		pos[3] = 0;

		glLightfv(GL_LIGHT0 + this->id, GL_POSITION, pos);

		glLightfv(GL_LIGHT0 + this->id, GL_AMBIENT, amb);
		glLightfv(GL_LIGHT0 + this->id, GL_DIFFUSE, diff);

	}


}
