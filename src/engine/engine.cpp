#define _USE_MATH_DEFINES
#include <math.h>
#include <vector>
#include "engine.h"

// Glut has to be included last to avoid errors
// (for example, C2381 'exit': redefinition; '__declspec(noreturn)' or '[[noreturn]]' differs)
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

using std::vector;
using engine::model;
using engine::vertex;

vector<model> engine::scene;

void engine::loadScene(vector<model> scene) {

	engine::scene = scene;
}

void engine::drawScene() {

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	vector<model>::iterator i;

	// Iterate over models

	for (i = scene.begin(); i != scene.end(); i++) {

		std::vector<vertex> vertices = i->vertices;

		glBegin(GL_TRIANGLES);

		// Iterate over vertices
		std::vector<vertex>::iterator j;

		for (j = vertices.begin(); j != vertices.end(); j++) {

			glVertex3f(j->x, j->y, j->z);

		}

		glEnd();

	}

}