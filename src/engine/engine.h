#pragma once
#ifndef	ENGINE_H
#define ENGINE_H

#include <vector>

namespace engine {

	struct vertex {
		float x, y, z;
	};

	// A model is a collection of vertices
	struct figure {
		std::vector<vertex> vertices;
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
