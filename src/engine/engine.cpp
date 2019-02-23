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

namespace engine {
	
	void engine::drawFrame() {
		// teste piramide

		glBegin(GL_TRIANGLES);

		// Triângulo da Frente
		glColor3f(1.0f, 1.0f, 0.0f); // yellow
		glVertex3f(0.0f, 1.0f, 0.0f);
		glVertex3f(-1.0f, 0.0f, 1.0f);
		glVertex3f(1.0f, 0.0f, 1.0f);

		// Right
		glColor3f(1.0f, 0.0f, 0.0f); // Red
		glVertex3f(0.0f, 1.0f, 0.0f);
		glVertex3f(1.0f, 0.0f, 1.0f);
		glVertex3f(1.0f, 0.0f, -1.0f);

		// Back
		glColor3f(1.0f, 0.0f, 1.0f); // pink
		glVertex3f(0.0f, 1.0f, 0.0f);
		glVertex3f(1.0f, 0.0f, -1.0f);
		glVertex3f(-1.0f, 0.0f, -1.0f);

		// Left
		glColor3f(0.0f, 0.0f, 1.0f); // blue      
		glVertex3f(0.0f, 1.0f, 0.0f);
		glVertex3f(-1.0f, 0.0f, -1.0f);
		glVertex3f(-1.0f, 0.0f, 1.0f);

		// ponteiro dos relógios

		// Debaixo
		glColor3f(0.0f, 0.0f, 1.0f); // blue      
		glVertex3f(-1.0f, 0.0f, -1.0f);
		glVertex3f(1.0f, 0.0f, 1.0f);
		glVertex3f(-1.0f, 0.0f, 1.0f);

		// Debaixo
		glColor3f(1.0f, 0.0f, 1.0f); // pink      
		glVertex3f(1.0f, 0.0f, -1.0f);
		glVertex3f(1.0f, 0.0f, 1.0f);
		glVertex3f(-1.0f, 0.0f, -1.0f);

		glEnd();

		// Iterate over models
	}
}