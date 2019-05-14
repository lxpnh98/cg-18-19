#pragma once
#ifndef ENGINE_H
#define ENGINE_H

#include <vector>
#include "transform.h"
#include "colour.h"

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

namespace engine {

    struct vertex {
        float x, y, z;
        float nx, ny, nz;
        float ti, tj;
    };

    // A model is a collection of vertices
    struct figure {
        GLuint vertexBuffer;
        GLuint normalBuffer;
        GLuint textureBuffer;
        int numVertices;
        std::vector<Transform *> *transforms;
        std::vector<Transform *> *upTransforms;
        GLuint texture;
        Colour diffuse;
        Colour specular;
        Colour emissive;
        Colour ambient;
        int typeDiff;
        int typeSpec;
        int typeEmis;
        int typeAmbi;
        float typeShine;
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
