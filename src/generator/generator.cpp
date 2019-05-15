#include <stdio.h>
//#include <windows.h>
#include <iostream>
#include <fstream>
#include <vector> 
#include <string>

#include "point.h"
#include "drawBezierPatches.h"

#include "../engine/tinyxml2.h"
using namespace tinyxml2;

#define _USE_MATH_DEFINES
#include <math.h>

void cross(double *a, double *b, double *res) {

    res[0] = a[1] * b[2] - a[2] * b[1];
    res[1] = a[2] * b[0] - a[0] * b[2];
    res[2] = a[0] * b[1] - a[1] * b[0];
}

void normalize(double *a) {

    double l = sqrt(a[0] * a[0] + a[1] * a[1] + a[2] * a[2]);
    a[0] = a[0] / l;
    a[1] = a[1] / l;
    a[2] = a[2] / l;
}

double length(double *v) {

    double res = sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
    return res;

}

#define TI(a)           ((a)/(2*M_PI))
#define TJ(b)           (((b)+(M_PI/2))/M_PI)

using namespace std;

void sendVertices(FILE *out, std::vector<Point> vertices) {
    for (int i = 0; i < vertices.size(); i++) {
        fprintf(out, "%f %f %f %f %f %f %f %f\n",
            vertices[i].getX(), vertices[i].getY(), vertices[i].getZ(),
            vertices[i].getNX(), vertices[i].getNY(), vertices[i].getNZ(),
            vertices[i].getTI(), vertices[i].getTJ());
    }
}

void drawPlane(float width, string fileName) {

    FILE *out;

    out = fopen(fileName.c_str(), "w"); 
    if (out != NULL) {

        std::vector<Point> vertices;

        //T1
        vertices.push_back(Point(width/2, 0.0, -width/2,
                                 0.0, 1.0, 0.0,
                                 1, 1));
        vertices.push_back(Point(-width/2, 0.0, width/2,
                                 0.0, 1.0, 0.0,
                                 0, 0));
        vertices.push_back(Point(width/2, 0.0, width/2,
                                 0.0, 1.0, 0.0,
                                 1, 0));

        //T2
        vertices.push_back(Point(width/2, 0.0, -width/2,
                                 0.0, 1.0, 0.0,
                                 1, 1));
        vertices.push_back(Point(-width/2, 0.0, -width/2,
                                 0.0, 1.0, 0.0,
                                 0, 1));
        vertices.push_back(Point(-width/2, 0.0, width/2,
                                 0.0, 1.0, 0.0,
                                 0, 0));

        // T11
        vertices.push_back(Point(width/2, 0.0, width/2,
                                 0.0, -1.0, 0.0,
                                 1, 0));
        vertices.push_back(Point(-width/2, 0.0, width/2,
                                 0.0, -1.0, 0.0,
                                 0, 0));
        vertices.push_back(Point(width/2, 0.0, -width/2,
                                 0.0, -1.0, 0.0,
                                 1, 1));

        // T21
        vertices.push_back(Point(-width/2, 0.0, width/2,
                                 0.0, -1.0, 0.0,
                                 0, 0));
        vertices.push_back(Point(-width/2, 0.0, -width/2,
                                 0.0, -1.0, 0.0,
                                 0, 1));
        vertices.push_back(Point(width/2, 0.0, -width/2,
                                 0.0, -1.0, 0.0,
                                 1, 1));

        sendVertices(out, vertices);
    }
    std::fclose(out);
}

void drawBox(float x, float y, float z, int nrDivisions, string fileName) {

    FILE *out;

    out = fopen(fileName.c_str(), "w");

    if (out != NULL) {

        std::vector<Point> vertices;

        float incX = x / nrDivisions;
        float incY = y / nrDivisions;
        float incZ = z / nrDivisions;

        float texX = (1.0 / 3.0) / nrDivisions;
        float texZ = 0.25 / nrDivisions;

        float baseX = (1.0 / 3.0);
        float baseZ = 0.0;

        float topoX = (1.0 / 3.0);
        float topoZ = 0.75;

        float frenteX = (1.0 / 3.0);
        float frenteZ = 0.25;

        float trasX = (1.0 / 3.0);
        float trasZ = 0.75;

        float esquerdaX = 1;
        float esquerdaZ = 0.75;

        float direitaX = (1.0/3.0);
        float direitaZ = 0.75;

        float xDiv = 0;
        float yDiv = 0;
        float zDiv = 0;

        int xx, yy, zz;
        // base e topo em que o Y é fixo
        for (zz = 0; zz < nrDivisions; zz++) {
            for (xx = 0; xx < nrDivisions; xx++) {
                // base
                vertices.push_back(Point(xDiv, 0, zDiv,
                                         0.0, -1.0, 0.0,
                                         baseX, baseZ));

                vertices.push_back(Point(xDiv + incX, 0, zDiv,
                                         0.0, -1.0, 0.0,
                                         baseX + texX, baseZ));

                vertices.push_back(Point(xDiv, 0, zDiv + incZ,
                                         0.0, -1.0, 0.0,
                                         baseX, baseZ + texZ));

                // base
                vertices.push_back(Point(xDiv + incX, 0, zDiv,
                                         0.0, -1.0, 0.0,
                                         baseX + texX, baseZ));

                vertices.push_back(Point(xDiv + incX, 0, zDiv + incZ,
                                         0.0, -1.0, 0.0,
                                         baseX + texX, baseZ + texZ));

                vertices.push_back(Point(xDiv, 0, zDiv + incZ,
                                         0.0, -1.0, 0.0,
                                         baseX, baseZ + texZ));

                // topo
                vertices.push_back(Point(xDiv, y, zDiv,
                                         0.0, 1.0, 0.0,
                                         topoX, topoZ));

                vertices.push_back(Point(xDiv, y, zDiv + incZ,
                                         0.0, 1.0, 0.0,
                                         topoX, topoZ - texZ));

                vertices.push_back(Point(xDiv + incX, y, zDiv,
                                         0.0, 1.0, 0.0,
                                         topoX + texX, topoZ));

                // topo
                vertices.push_back(Point(xDiv + incX, y, zDiv,
                                         0.0, 1.0, 0.0,
                                         topoX + texX, topoZ));

                vertices.push_back(Point(xDiv, y, zDiv + incZ,
                                         0.0, 1.0, 0.0,
                                         topoX, topoZ - texZ));

                vertices.push_back(Point(xDiv + incX, y, zDiv + incZ,
                                         0.0, 1.0, 0.0,
                                         topoX + texX, topoZ - texZ));

                xDiv += incX;
                baseX += texX;
                topoX += texX;
            }

            baseX = (1.0 / 3.0);
            baseZ += texZ;
            topoX = (1.0 / 3.0);
            topoZ -= texZ;

            xDiv = 0;
            zDiv += incZ;
        }

        xDiv = 0;
        yDiv = 0;
        zDiv = 0;

        // lados em que o x é fixo
        for (zz = 0; zz < nrDivisions; zz++) {
            for (yy = 0; yy < nrDivisions; yy++) {

                // lado esquerdo
                vertices.push_back(Point(x, yDiv, zDiv,
                                         1.0, 0.0, 0.0,
                                         esquerdaX, esquerdaZ));

                vertices.push_back(Point(x, yDiv + incY, zDiv + incZ,
                                         1.0, 0.0, 0.0,
                                         esquerdaX - texX, esquerdaZ - texZ));

                vertices.push_back(Point(x, yDiv, zDiv + incZ,
                                         1.0, 0.0, 0.0,
                                         esquerdaX, esquerdaZ - texZ));

                // lado esquerdo
                vertices.push_back(Point(x, yDiv + incY, zDiv,
                                         1.0, 0.0, 0.0,
                                         esquerdaX - texX, esquerdaZ));

                vertices.push_back(Point(x, yDiv + incY, zDiv + incZ,
                                         1.0, 0.0, 0.0,
                                         esquerdaX - texX, esquerdaZ - texZ));

                vertices.push_back(Point(x, yDiv, zDiv,
                                         1.0, 0.0, 0.0,
                                         esquerdaX, esquerdaZ));

                // lado direito
                vertices.push_back(Point(0, yDiv, zDiv,
                                         -1.0, 0.0, 0.0,
                                         direitaX, direitaZ));

                vertices.push_back(Point(0, yDiv, zDiv + incZ,
                                         -1.0, 0.0, 0.0,
                                         direitaX, direitaZ - texZ));

                vertices.push_back(Point(0, yDiv + incY, zDiv + incZ,
                                         -1.0, 0.0, 0.0,
                                         direitaX - texX, direitaZ - texZ));

                // lado direito
                vertices.push_back(Point(0, yDiv + incY, zDiv,
                                         -1.0, 0.0, 0.0,
                                         direitaX - texX, direitaZ));

                vertices.push_back(Point(0, yDiv, zDiv,
                                         -1.0, 0.0, 0.0,
                                         direitaX, direitaZ));

                vertices.push_back(Point(0, yDiv + incY, zDiv + incZ,
                                         -1.0, 0.0, 0.0,
                                         direitaX - texX, direitaZ - texZ));

                yDiv += incY;

                esquerdaX -= texX;
                direitaX -= texX;
            }

            esquerdaX = 1.0;
            esquerdaZ -= texZ;
            direitaX = (1.0/3.0);
            direitaZ -= texZ;

            yDiv = 0;
            zDiv += incZ;
        }

        xDiv = 0;
        yDiv = 0;
        zDiv = 0;

        // lados em que o z é fixo
        for (xx = 0; xx < nrDivisions; xx++) {
            for (yy = 0; yy < nrDivisions; yy++) {

                // frente
                vertices.push_back(Point(xDiv + incX, yDiv + incY, z,
                                         0.0, 0.0, 1.0,
                                         frenteX + texX, frenteZ + texZ));

                vertices.push_back(Point(xDiv, yDiv, z,
                                         0.0, 0.0, 1.0,
                                         frenteX, frenteZ));

                vertices.push_back(Point(xDiv + incX, yDiv, z,
                                         0.0, 0.0, 1.0,
                                         frenteX + texX, frenteZ));

                // frente
                vertices.push_back(Point(xDiv + incX, yDiv + incY, z,
                                         0.0, 0.0, 1.0,
                                         frenteX + texX, frenteZ + texZ));

                vertices.push_back(Point(xDiv, yDiv + incY, z,
                                         0.0, 0.0, 1.0,
                                         frenteX, frenteZ + texZ));

                vertices.push_back(Point(xDiv, yDiv, z,
                                         0.0, 0.0, 1.0,
                                         frenteX, frenteZ));

                // tras
                vertices.push_back(Point(xDiv + incX, yDiv + incY, 0,
                                         0.0, 0.0, -1.0,
                                         trasX + texX, trasZ + texZ));

                vertices.push_back(Point(xDiv + incX, yDiv, 0,
                                         0.0, 0.0, -1.0,
                                         trasX + texX, trasZ));

                vertices.push_back(Point(xDiv, yDiv, 0,
                                         0.0, 0.0, -1.0,
                                         trasX, trasZ));

                // tras
                vertices.push_back(Point(xDiv + incX, yDiv + incY, 0,
                                         0.0, 0.0, -1.0,
                                         trasX + texX, trasZ + texZ));

                vertices.push_back(Point(xDiv, yDiv, 0,
                                         0.0, 0.0, -1.0,
                                         trasX, trasZ));

                vertices.push_back(Point(xDiv, yDiv + incY, 0,
                                         0.0, 0.0, -1.0,
                                         trasX, trasZ + texZ));

                xDiv += incX;
                frenteX += texX;
                trasX += texX;
            }

            frenteX = (1.0 / 3.0);
            frenteZ += texZ;
            trasX = (1.0 / 3.0);
            trasZ += texZ;

            xDiv = 0;
            yDiv += incY;
        }
        sendVertices(out, vertices);
    }
    std::fclose(out);
}

void drawSphere(float r, int slices, int stacks, string fileName) {

    FILE *out;

    out = fopen(fileName.c_str(), "w");

    if (out != NULL) {

        std::vector<Point> vertices;

        float alpha = 0;
        float beta = -M_PI/2;

        float a_step = ((2 * M_PI) / slices);
        float b_step = (M_PI / stacks);

        float angulo_a1 = 0;
        float angulo_b1 = 0;

        for (int i = 0; i < stacks; i++) {
            
            alpha = 0;
            angulo_b1 = beta + b_step;

            for(int j = 0; j < slices; j++) {

                angulo_a1 = alpha + a_step; 

                vertices.push_back(Point(r * cos(beta) * sin(alpha), r * sin(beta), r * cos(beta) * cos(alpha),
                                             cos(beta) * sin(alpha),     sin(beta),     cos(beta) * cos(alpha),
                                         TI(alpha), TJ(beta)));
                vertices.push_back(Point(r * cos(beta) * sin(angulo_a1), r * sin(beta), r * cos(beta) * cos(angulo_a1),
                                             cos(beta) * sin(angulo_a1),     sin(beta),     cos(beta) * cos(angulo_a1),
                                         TI(angulo_a1), TJ(beta)));
                vertices.push_back(Point(r * cos(angulo_b1) * sin(alpha), r * sin(angulo_b1), r * cos(angulo_b1) * cos(alpha),
                                             cos(angulo_b1) * sin(alpha),     sin(angulo_b1),     cos(angulo_b1) * cos(alpha),
                                         TI(alpha), TJ(angulo_b1)));

                vertices.push_back(Point(r * cos(beta) * sin(angulo_a1), r * sin(beta), r * cos(beta) * cos(angulo_a1),
                                             cos(beta) * sin(angulo_a1),     sin(beta),     cos(beta) * cos(angulo_a1),
                                         TI(angulo_a1), TJ(beta)));
                vertices.push_back(Point(r * cos(angulo_b1) * sin(angulo_a1), r * sin(angulo_b1), r * cos(angulo_b1) * cos(angulo_a1),
                                             cos(angulo_b1) * sin(angulo_a1),     sin(angulo_b1),     cos(angulo_b1) * cos(angulo_a1),
                                         TI(angulo_a1), TJ(angulo_b1)));
                vertices.push_back(Point(r * cos(angulo_b1) * sin(alpha), r * sin(angulo_b1), r * cos(angulo_b1) * cos(alpha),
                                             cos(angulo_b1) * sin(alpha),     sin(angulo_b1),     cos(angulo_b1) * cos(alpha),
                                         TI(alpha), TJ(angulo_b1)));

                alpha += a_step;
            }

            beta += b_step;
        }

        sendVertices(out, vertices);
    }
    std::fclose(out);
}

void drawCone(float r, float h, int slices, int stacks, string fileName) {

    FILE *out;

    out = fopen(fileName.c_str(), "w");

    if (out != NULL) {

        std::vector<Point> vertices;

        float raioP = 1.0/6.0;

        float centroX = raioP;
        float centroY = raioP;

        float centroGrandeX = 0.0;
        float centroGrandeY = 1.0;

        float step = (centroGrandeY - 2*centroY) / stacks;

        float a = (2 * M_PI) / slices;

        for (int i = 0; i < slices; i++) {

            // base
			vertices.push_back(Point(0, 0, 0,
                                     0.0, -1.0, 0.0,
									 centroX, centroY));

            vertices.push_back(Point(r * sin(a * (i + 1)), 0, r * cos(a * (i + 1)),
                                         0.0, -1.0, 0.0,
                     centroX + centroX * sin(a * (i + 1)), centroY + centroY * cos(a * (i + 1))));

			vertices.push_back(Point(r * sin(a * i), 0, r *  cos(a * i),
                                         0.0, -1.0, 0.0,
					 centroX + centroX * sin(a * i), centroY + centroY * cos(a * i)));


            float oldRadius = r;
            float oldHeight = 0;

            double p1[3], p2[3], p3[3], v1[3], v2[3], n[3];

            p1[0] = 0.0;
            p1[1] = h;
            p1[2] = 0.0;

            p2[0] = r * sin(a * i);
            p2[1] = 0.0;
            p2[2] = r * cos(a * i);

            p3[0] = r * sin(a * (i + 1));
            p3[1] = 0.0;
            p3[2] = r * cos(a * (i + 1));

            v1[0] = p3[0]-p2[0];
            v1[1] = p3[1]-p2[1];
            v1[2] = p3[2]-p2[2];

            v2[0] = p1[0]-p2[0];
            v2[1] = p1[1]-p2[1];
            v2[2] = p1[2]-p2[2];

            cross(v1, v2, n);
            normalize(n);

            // sides
            for (int j = 0; j < stacks; j++) {

                float newHeight = h / stacks * (j+1);
                float newRadius = (h - newHeight) * r / h;

                // triangle1
                vertices.push_back(Point(newRadius * sin(a * i),   newHeight, newRadius * cos(a * i),
                                                     n[0], n[1], n[2],
                           (newRadius/r)*(2.0/3)*sin(a * i / 4), 1-((newRadius/r)*(2.0/3)*cos(a * i / 4))));

                vertices.push_back(Point(oldRadius * sin(a * i),   oldHeight, oldRadius * cos(a * i),
                                                     n[0], n[1], n[2],
                           (oldRadius/r)*(2.0/3)*sin(a * i / 4), 1-((oldRadius/r)*(2.0/3)*cos(a * i / 4))));

                vertices.push_back(Point(oldRadius * sin(a * (i + 1)),  oldHeight, oldRadius * cos(a * (i + 1)),
                                                     n[0], n[1], n[2],
                           (oldRadius/r)*(2.0/3)*sin(a * (i + 1) / 4), 1-(oldRadius/r)*(2.0/3)*cos(a * (i + 1) / 4)));

                // triangle 2
                vertices.push_back(Point(newRadius * sin(a * i),   newHeight, newRadius * cos(a * i),
                                                     n[0], n[1], n[2],
                           (newRadius/r)*(2.0/3)*sin(a * i / 4), 1-((newRadius/r)*(2.0/3)*cos(a * i / 4))));

                vertices.push_back(Point(oldRadius * sin(a * (i + 1)),  oldHeight, oldRadius * cos(a * (i + 1)),
                                                     n[0], n[1], n[2],
                           (oldRadius/r)*(2.0/3)*sin(a * (i + 1) / 4), 1-(oldRadius/r)*(2.0/3)*cos(a * (i + 1) / 4)));

                vertices.push_back(Point(newRadius * sin(a * (i + 1)),  newHeight, newRadius * cos(a * (i + 1)),
                                                     n[0], n[1], n[2],
                           (newRadius/r)*(2.0/3)*sin(a * (i + 1) / 4), 1-(newRadius/r)*(2.0/3)*cos(a * (i + 1) / 4)));

                oldRadius = newRadius;
                oldHeight = newHeight;

            }
        }

        sendVertices(out, vertices);
    }
    std::fclose(out);
}

void drawPyramid(float height, float width, float length, string fileName) {

    FILE *out;

    out = fopen(fileName.c_str(), "w");

    if (out != NULL) {

        std::vector<Point> vertices; 

        float largura = width/2;
        float comprimento = length/2;

        float ladoX = 0.25;
        float ladoY = 0.25;

        float altura = 1.0;
        float trianguloX = 0.0;
        float trianguloY = 0.25;
        float step = 0.25;

        double p1[3], p2[3], p3[3], v1[3], v2[3], n[3];

        p1[0] = 0.0;
        p1[1] = height;
        p1[2] = 0.0;

        p2[0] = -comprimento;
        p2[1] = 0.0;
        p2[2] = largura;

        p3[0] = comprimento;
        p3[1] = 0.0;
        p3[2] = largura;

        v1[0] = p3[0]-p2[0];
        v1[1] = p3[1]-p2[1];
        v1[2] = p3[2]-p2[2];

        v2[0] = p1[0]-p2[0];
        v2[1] = p1[1]-p2[1];
        v2[2] = p1[2]-p2[2];

        cross(v1, v2, n);
        normalize(n);

        // Triângulo da Frente
        vertices.push_back(Point(0.0, height, 0.0,
                                 n[0], n[1], n[2],
                                 trianguloX + step/2, altura));

        vertices.push_back(Point(-comprimento, 0.0, largura,
                                 n[0], n[1], n[2],
                                 trianguloX, trianguloY));

        vertices.push_back(Point(comprimento, 0.0, largura,
                                 n[0], n[1], n[2],
                                 trianguloX + step, trianguloY));

        trianguloX += step;

        p2[0] = comprimento;
        p2[1] = 0.0;
        p2[2] = largura;

        p3[0] = comprimento;
        p3[1] = 0.0;
        p3[2] = -largura;

        v1[0] = p3[0]-p2[0];
        v1[1] = p3[1]-p2[1];
        v1[2] = p3[2]-p2[2];

        v2[0] = p1[0]-p2[0];
        v2[1] = p1[1]-p2[1];
        v2[2] = p1[2]-p2[2];

        cross(v1, v2, n);
        normalize(n);

        // Right
        vertices.push_back(Point(0.0, height, 0.0,
                                 n[0], n[1], n[2],
                                 trianguloX + step/2, altura));

        vertices.push_back(Point(comprimento, 0.0, largura,
                                 n[0], n[1], n[2],
                                 trianguloX, trianguloY));

        vertices.push_back(Point(comprimento, 0.0, -largura,
                                 n[0], n[1], n[2],
                                 trianguloX + step, trianguloY));

        trianguloX += step;

        p2[0] = comprimento;
        p2[1] = 0.0;
        p2[2] = -largura;

        p3[0] = -comprimento;
        p3[1] = 0.0;
        p3[2] = -largura;

        v1[0] = p3[0]-p2[0];
        v1[1] = p3[1]-p2[1];
        v1[2] = p3[2]-p2[2];

        v2[0] = p1[0]-p2[0];
        v2[1] = p1[1]-p2[1];
        v2[2] = p1[2]-p2[2];

        cross(v1, v2, n);
        normalize(n);

        // Back
        vertices.push_back(Point(0.0, height, 0.0,
                                 n[0], n[1], n[2],
                                 trianguloX + step/2, altura));

        vertices.push_back(Point(comprimento, 0.0, -largura,
                                 n[0], n[1], n[2],
                                 trianguloX, trianguloY));

        vertices.push_back(Point(-comprimento, 0.0, -largura,
                                 n[0], n[1], n[2],
                                 trianguloX + step, trianguloY));

        trianguloX += step;

        p2[0] = -comprimento;
        p2[1] = 0.0;
        p2[2] = -largura;

        p3[0] = -comprimento;
        p3[1] = 0.0;
        p3[2] = largura;

        v1[0] = p3[0]-p2[0];
        v1[1] = p3[1]-p2[1];
        v1[2] = p3[2]-p2[2];

        v2[0] = p1[0]-p2[0];
        v2[1] = p1[1]-p2[1];
        v2[2] = p1[2]-p2[2];

        cross(v1, v2, n);
        normalize(n);

        // Left 
        vertices.push_back(Point(0.0, height, 0.0,
                                 n[0], n[1], n[2],
                                 trianguloX + step/2, altura));

        vertices.push_back(Point(-comprimento, 0.0, -largura,
                                 n[0], n[1], n[2],
                                 trianguloX, trianguloY));

        vertices.push_back(Point(-comprimento, 0.0, largura,
                                 n[0], n[1], n[2],
                                 trianguloX + step, trianguloY));

        // ponteiro dos relógios

        // Debaixo    
        vertices.push_back(Point(-comprimento, 0.0, -largura,
                                 0.0, -1.0, 0.0,
                                 0.0, 0.0));

        vertices.push_back(Point(comprimento, 0.0, largura,
                                 0.0, -1.0, 0.0,
                                 ladoX, ladoY));

        vertices.push_back(Point(-comprimento, 0.0, largura,
                                 0.0, -1.0, 0.0,
                                 0.0, ladoY));

        // Debaixo      
        vertices.push_back(Point(comprimento, 0.0, -largura,
                                 0.0, -1.0, 0.0,
                                 ladoX, 0.0));

        vertices.push_back(Point(comprimento, 0.0, largura,
                                 0.0, -1.0, 0.0,
                                 ladoX, ladoY));

        vertices.push_back(Point(-comprimento, 0.0, -largura,
                                 0.0, -1.0, 0.0,
                                 0.0, 0.0));

        sendVertices(out, vertices);
    }
    std::fclose(out);
}

void drawCylinder(float r, float height, int slices, string fileName) {

    FILE *out;

    out = fopen(fileName.c_str(), "w");

    if (out != NULL) {

        std::vector<Point> vertices;

        float a = (2 * M_PI) / slices;
        float altura = height / 2;

        float centroX = 0.4375;
        float centroY = 0.25;

        float tex_fator = 1.0/slices;
        float tex_raio = centroX - centroY;

        for (int i = 0; i < slices; i++) {

            // top
            vertices.push_back(Point(0, altura, 0,
                                     0.0, 1.0, 0.0,
                                     centroX, tex_raio));

            vertices.push_back(Point(r * sin(a * i),          altura, r * cos(a * i),
                                     0.0, 1.0, 0.0,
                    centroX + tex_raio * sin(a * i), tex_raio + tex_raio * cos(a * i)));

            vertices.push_back(Point(r * sin(a * (i + 1)),          altura, r * cos(a * (i + 1)),
                                     0.0, 1.0, 0.0,
                    centroX + tex_raio * sin(a * (i + 1)), tex_raio + tex_raio * cos(a * (i + 1))));

            // bottom
            vertices.push_back(Point(0, -altura, 0,
                                     0.0, -1.0, 0.0,
                                     0.8125, 0.1875));

            vertices.push_back(Point(r * sin(a * (i + 1)),        -altura, r * cos(a * (i + 1)),
                                     0.0, -1.0, 0.0,
                     0.8125 + tex_raio * sin(a * (i + 1)), 0.1875 + tex_raio * cos(a * (i + 1))));

            vertices.push_back(Point(r * sin(a * i),        -altura, r * cos(a * i),
                                     0.0, -1.0, 0.0,
                     0.8125 + tex_raio * sin(a * i), 0.1875 + tex_raio * cos(a * i)));

            // side 1
            vertices.push_back(Point(r * sin(a * (i + 1)), altura, r * cos(a * (i + 1)),
                                         sin(a * (i + 1)), 0.0,     cos(a * (i + 1)),
                                      (i + 1) * tex_fator, 1));

            vertices.push_back(Point(r * sin(a * i), altura, r * cos(a * i),
                                         sin(a * i), 0.0,     cos(a * i),
                                     i  * tex_fator, 1));

            vertices.push_back(Point(r * sin(a * i), -altura, r * cos(a * i),
                                         sin(a * i), 0.0,     cos(a * i),
                                      i * tex_fator, 0.375));

            // side 2
            vertices.push_back(Point(r * sin(a * i), -altura, r * cos(a * i),
                                         sin(a * i), 0.0,     cos(a * i),
                                      i * tex_fator, 0.375));

            vertices.push_back(Point(r * sin(a * (i + 1)), -altura, r * cos(a * (i + 1)),
                                         sin(a * (i + 1)), 0.0,     cos(a * (i + 1)),
                                      (i + 1) * tex_fator, 0.375));

            vertices.push_back(Point(r * sin(a * (i + 1)), altura, r * cos(a * (i + 1)),
                                         sin(a * (i + 1)), 0.0,     cos(a * (i + 1)),
                                      (i + 1) * tex_fator, 1));
        }

        sendVertices(out, vertices);
    }
    std::fclose(out);
}

void writeToXML(string fileName) {

    tinyxml2::XMLDocument doc;

    if (doc.LoadFile("scene.xml") != tinyxml2::XML_SUCCESS) {

        XMLNode * pRoot = doc.NewElement("scene");

        doc.InsertFirstChild(pRoot);

        tinyxml2::XMLElement* newElement = doc.NewElement("model");

        newElement->SetAttribute("file", fileName.c_str());

        pRoot->InsertFirstChild(newElement);

        doc.SaveFile("scene.xml");

    }

    else {

        XMLElement * pRoot = doc.FirstChildElement("scene");

        tinyxml2::XMLElement* newElement = doc.NewElement("model");

        newElement->SetAttribute("file", fileName.c_str());

        pRoot->InsertFirstChild(newElement);

        doc.SaveFile("scene.xml");

    }

}

int main(int argc, char** argv) {

    // Checks if program receives something to process
    if (argv[1] != NULL) { 

        std::string primitive = argv[1];

        if (primitive.compare("plane") == 0 && argc == 4) {

            std::cout << "A criar um plano..." << std::endl;

            float width = std::stof(argv[2]);

            std::string file = argv[3];

            // Call plane function
            drawPlane(width, file);

            std::cout << "Plano criado com sucesso." << std::endl;

            // writes to scene.xml
            writeToXML(file);

            std::cout << "Path do plano escrita no scene.xml com sucesso" << std::endl;
        }

        else if (primitive.compare("box") == 0 && argc == 7) {

            std::cout << "A criar uma caixa..." << std::endl;

            float x, y, z;

            x = std::stof(argv[2]);
            y = std::stof(argv[3]);
            z = std::stof(argv[4]);

            int nrDivisions = std::stoi(argv[5]);

            std::string file = argv[6];

            // Call box function
            drawBox(x, y, z, nrDivisions, file);

            std::cout << "Caixa criada com sucesso." << std::endl;

            // writes to scene.xml
            writeToXML(file);

            std::cout << "Path da caixa escrita no scene.xml com sucesso" << std::endl;
        }

        else if (primitive.compare("sphere") == 0 && argc == 6) {

            std::cout << "A criar uma esfera..." << std::endl;

            float radius = std::stof(argv[2]);

            int slices = std::stoi(argv[3]);

            int stacks = std::stoi(argv[4]);

            std::string file = argv[5];

            // Call sphere function
            drawSphere(radius, slices, stacks, file);

            std::cout << "Esfera criada com sucesso." << std::endl;

            // writes to scene.xml
            writeToXML(file);

            std::cout << "Path da esfera escrita no scene.xml com sucesso" << std::endl;
        }

        else if (primitive.compare("cone") == 0 && argc == 7) {

            std::cout << "A criar um cone..." << std::endl;

            float radius = std::stof(argv[2]);

            float height = std::stof(argv[3]);

            int slices = std::stoi(argv[4]);

            int stacks = std::stoi(argv[5]);

            std::string file = argv[6];

            // Call cone function
            drawCone(radius, height, slices, stacks, file);

            std::cout << "Cone criado com sucesso." << std::endl;

            // writes to scene.xml
            writeToXML(file);

            std::cout << "Path do cone escrita no scene.xml com sucesso" << std::endl;
        }

        else if (primitive.compare("pyramid") == 0 && argc == 6) {

            std::cout << "A criar uma pirâmide..." << std::endl;

            float height = std::stof(argv[2]);

            float width = std::stof(argv[3]);

            float length = std::stof(argv[4]);

            std::string file = argv[5];

            // Call pyramid function
            drawPyramid(height, width, length, file);

            std::cout << "Pirâmide criada com sucesso." << std::endl;

            // writes to scene.xml
            writeToXML(file);

            std::cout << "Path da pirâmide escrita no scene.xml com sucesso" << std::endl;
        }

        else if (primitive.compare("cylinder") == 0 && argc == 6) {

            std::cout << "A criar um cilindro..." << std::endl;

            float radius = std::stof(argv[2]);

            float height = std::stof(argv[3]);

            int slices = std::stoi(argv[4]);

            std::string file = argv[5];

            // Call cylinder function
            drawCylinder(radius, height, slices, file);

            std::cout << "Cilindro criado." << std::endl;

            // writes to scene.xml
            writeToXML(file);

            std::cout << "Path do cilindro escrita no scene.xml com sucesso" << std::endl;
        }

        else if (primitive.compare("bezier") == 0 && argc == 5) {

            std::cout << "A criar um cilindro..." << std::endl;

            std::string in_file = argv[2];

            int tesselation = std::stoi(argv[3]);

            std::string file = argv[4];

            drawBezierPatches(in_file, tesselation, file);

            std::cout << "Modelo de patches Bezier criado." << std::endl;

            // writes to scene.xml
            writeToXML(file);

            std::cout << "Path do modelo escrita no scene.xml com sucesso" << std::endl;
        }
        else {

            std::cout << argv[1] << " não é um sólido válido." << std::endl;
        }
    }
    return 0;
}
