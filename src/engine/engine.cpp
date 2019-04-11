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


        glPushMatrix();
        // Apply transformations from above groups
        for (Transform *t : *fig->upTransforms) {
            // Draw CatmullRom curve before applying its transformation
			if (Translate* tr = dynamic_cast<Translate*>(t)) {
				tr->renderCatmullRomCurve();
			}
            t->apply();
        }

        // Apply transformations from current group
        for (Transform *t : *fig->transforms) {
            t->apply();
        }

        glEnableClientState(GL_VERTEX_ARRAY);
        glBindBuffer(GL_ARRAY_BUFFER, fig->buffer);
        glVertexPointer(3,GL_FLOAT,0,0);
        glDrawArrays(GL_TRIANGLES, 0, fig->bufferSize);

        glPopMatrix();
	}

}
