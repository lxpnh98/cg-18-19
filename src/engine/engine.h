#pragma once
#ifndef	ENGINE_H
#define ENGINE_H

#include <vector>
#include "transform.h"

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif


namespace engine {

	struct vertex {
		float x, y, z;
	};

	// A model is a collection of vertices
	struct figure {
        GLuint buffer;
        int bufferSize;
        std::vector<Transform *> *transforms;
        std::vector<Transform *> *upTransforms;
	};

	// Scene that can be loaded with loadScene().
	// "extern" means it has to be defined once in a source (.cpp) file
	extern std::vector<figure> scene;

	// Loads a scene
	void loadScene(std::vector<figure> scene);

	// Draws a frame of the scene
	void drawScene();
};

#endif
