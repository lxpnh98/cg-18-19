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

// vetores cores
float diffuse[4] = { 1,1,1,1 };
float specular[4] = { 1,1,1,1 };
float emissive[4] = { 1,1,1,1 };
float ambient[4] = { 1,1,1,1 };

vector<figure> engine::scene;

void engine::loadScene(vector<figure> scene) {

	engine::scene = scene;
}

void engine::drawScene() {

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	vector<figure>::iterator fig;
	int type;
	Colour cor;

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

		glBindTexture(GL_TEXTURE_2D, fig->texture);
		glBindBuffer(GL_ARRAY_BUFFER, fig->vertexBuffer);
		glVertexPointer(3,GL_FLOAT,0,0);

		glBindBuffer(GL_ARRAY_BUFFER, fig->normalBuffer);
		glNormalPointer(GL_FLOAT, 0, 0);

		glBindBuffer(GL_ARRAY_BUFFER, fig->textureBuffer);
		glTexCoordPointer(2, GL_FLOAT, 0, 0);

		glDrawArrays(GL_TRIANGLES, 0, (fig->numVertices * 3));
        glBindTexture(GL_TEXTURE_2D, 0);

        glPopMatrix();

		type = fig->type;
        cor = fig->colour;
        switch(type) {
            case 1 :
		       diffuse[1] = cor.getCorR();
                diffuse[2] = cor.getCorG();
                diffuse[3] = cor.getCorB();
                glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
		        break;
            case 2 :
                specular[1] = cor.getCorR();
                specular[2] = cor.getCorG();
                specular[3] = cor.getCorB();
                glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
                break;
            case 3 :
                emissive[1] = cor.getCorR();
                emissive[2] = cor.getCorG();
                emissive[3] = cor.getCorB();
                glMaterialfv(GL_FRONT, GL_EMISSION, emissive);
                break;
            case 4 :
                ambient[1] = cor.getCorR();
                ambient[2] = cor.getCorG();
                ambient[3] = cor.getCorB();
                glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
                break;    
            default:
                break;
        }
	}
}
