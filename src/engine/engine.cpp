#define _USE_MATH_DEFINES
#include <math.h>
#include <vector>
#include <iostream>
#include "engine.h"

// Glut has to be included last to avoid errors
// (for example, C2381 'exit': redefinition; '__declspec(noreturn)' or '[[noreturn]]' differs)
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

using std::vector;
using engine::figure;
using engine::vertex;

vector<figure> engine::scene;

void engine::loadScene(vector<figure> scene) {

	engine::scene = scene;
}

void engine::drawScene() {

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	vector<figure>::iterator fig;

	// Iterate over models

	for (fig = scene.begin(); fig != scene.end(); fig++) {

		std::vector<vertex> vertices = fig->vertices;

        glPushMatrix();
        // Apply transformations
        for (Transform *t : *fig->transforms) {

			if (Translate* tr = dynamic_cast<Translate*>(t)) {
				tr->renderCatmullRomCurve();
			}

            t->apply();
        }

		// Draw vertices
		glBegin(GL_TRIANGLES);
		std::vector<vertex>::iterator j;
		for (j = vertices.begin(); j != vertices.end(); j++) {
			glVertex3f(j->x, j->y, j->z);
		}
		glEnd();

        glPopMatrix();
	}

}
