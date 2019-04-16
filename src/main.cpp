#include "engine/engine.h"
#include "engine/parser.h"

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

#define _USE_MATH_DEFINES
#include <math.h>

//Variáveis de câmera
float cPosX = 0.0f, cPosY = 0.0f, cPosZ = 20.0f;
float cDirX = 0.0f, cDirY = 0.0f, cDirZ = 0.0f;
float cTiltX = 0.0f, cTiltY = 1.0f, cTiltZ = 0.0f;
float Zoom = 80.0f, zoomMin = 4.0f;
float cAngleA = 0.0f, cAngleB = 0.0f;
float offsetX = 0.0f, offsetY = 0.0f, offsetZ = 0.0f;

//Método de calculo da posição da câmera
void cameraCalc() {
	cPosX = Zoom * (cos(cAngleB) * sin(cAngleA)) + cDirX;
	cPosY = Zoom * sin(cAngleB) + cDirY;
	cPosZ = Zoom * cos(cAngleB) * cos(cAngleA) + cDirZ;
}

void processKeys(unsigned char key, int xx, int yy) {

	switch (key) {
		case '1': glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); break;
		case '2': glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); break;
		case '3': glPolygonMode(GL_FRONT_AND_BACK, GL_POINT); break;
        case 'a': cDirX -= 3.0f; break; // Camara move para a esquerda
        case 'd': cDirX += 3.0f; break; // Camara move para a direita
		case 'w': cDirZ -= 3.0f; break; // Camara move para a cima
		case 's': cDirZ += 3.0f; break; // Camara move para a baixo

		case '+': if (Zoom > zoomMin) Zoom = Zoom - 2.0f; break; // Zoom in
		case '-': Zoom = Zoom + 2.0f;  break; // Zoom out
		case 'h': cAngleA = cAngleA - 0.005f; break; // Roda a camara para a esquerda
		case 'k': cAngleA = cAngleA + 0.005f; break; // Roda a camara para a direita
		case 'u': if (cAngleB < M_PI / 2) { cAngleB = (cAngleB + 0.005f); } break; // Roda a camara para a cima
		case 'j': if (cAngleB > -M_PI / 2) { cAngleB = cAngleB - 0.005f; } break; // Roda a camara para a baixo
	}
}

void keyBoardHandler(int key, int x, int y) {

	switch (key) {
		case GLUT_KEY_UP: if (cAngleB < M_PI / 2) { cAngleB = (cAngleB + 0.07f); } break; // Roda a camara para a cima
		case GLUT_KEY_DOWN: if (cAngleB > -M_PI / 2) { cAngleB = cAngleB - 0.07f; } break; // Roda a camara para a baixo
		case GLUT_KEY_LEFT: cAngleA = cAngleA - 0.02f; break; // Roda a camara para a esquerda
		case GLUT_KEY_RIGHT: cAngleA = cAngleA + 0.02f; break; // Roda a camara para a direita
		case GLUT_KEY_PAGE_UP: if (Zoom > zoomMin) Zoom = Zoom - 0.1f; break; // Zoom in
		case GLUT_KEY_PAGE_DOWN: Zoom = Zoom + 0.1f; break; // Zoom out
	}
}

void drawCoordinates() {

	glBegin(GL_LINES);
    glPushMatrix();
	glColor3f(1, 0, 0); glVertex3f(0, 0, 0); glVertex3f(10, 0, 0);
	glColor3f(0, 1, 0); glVertex3f(0, 0, 0); glVertex3f(0, 10, 0);
	glColor3f(0, 0, 1); glVertex3f(0, 0, 0); glVertex3f(0, 0, 10);
    glPopMatrix();
	glEnd();

	glFlush();
}

void changeSize(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window with zero width).
	if(h == 0)
		h = 1;

	// compute window's aspect ratio 
	float ratio = w * 1.0 / h;

	// Set the projection matrix as current
	glMatrixMode(GL_PROJECTION);
	// Load Identity Matrix
	glLoadIdentity();
	
	// Set the viewport to be the entire window
    glViewport(0, 0, w, h);

	// Set perspective
	gluPerspective(45.0f ,ratio, 1.0f ,10000.0f);

	// return to the model view matrix mode
	glMatrixMode(GL_MODELVIEW);
}

void renderScene(void) {
	// clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// set the camera
	glLoadIdentity();
	// Cálculo da posição da câmera
	cameraCalc();
	gluLookAt(cPosX, cPosY, cPosZ,
		   	  cDirX, cDirY, cDirZ,
			  cTiltX, cTiltY, cTiltZ);

// put drawing instructions here
	drawCoordinates();
    glColor3f(1, 1, 1);
	engine::drawScene();

	// End of frame
	glutSwapBuffers();
}

int main(int argc, char **argv) {

	// This function will init GLUT itself
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);

	glutInitWindowPosition(100, 100);

	glutInitWindowSize(800, 800);

	glutCreateWindow("CG@DI");

	glutSpecialFunc(keyBoardHandler);
	glutKeyboardFunc(processKeys);

	// put callback registration here

	// The callback function responsible for redrawing the window’s contents. 
	glutDisplayFunc(renderScene);

	// The registered function will be called when the window is created and when it is resized.
	glutReshapeFunc(changeSize);

	// This makes it particularly suitable for situations where repeated redraw is required, for instance in continuous animations.
	glutIdleFunc(renderScene);

	// OpenGL settings 
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

    glewInit();

	// Load scene XML
	std::vector<engine::figure> *scene = parser::loadXML((argc > 1 ? argv[1] : "scene.xml"));

	// Send scene models to engine
	engine::loadScene(*scene);

	// enter GLUT's main loop
	glutMainLoop();
	
	return 1;
}

