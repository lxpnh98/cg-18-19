#include <stdio.h>
//#include <windows.h>
#include <iostream>
#include <fstream>
#include <vector> 
#include <string>

#include "point.h"

#include "../engine/tinyxml2.h"
using namespace tinyxml2;

#define _USE_MATH_DEFINES
#include <math.h>

using namespace std;

/*
TODO:
- Plane (a square in the XZ plane, centred in the origin, made with 2 triangles)
- Box (requires X, Y and Z dimensions, and optionally the number of divisions)
- Sphere (requires radius, slices and stacks)
- Cone (requires bottom radius, height, slices and stacks)
*/

void drawPlane(float width, string fileName) {

	FILE *out;

	// open to write (cleans if file already exists or creates it if not)
	out = fopen(fileName.c_str(), "w");

	if (out != NULL) {
		
		// Vector to store the vertices
		std::vector<Point> vertices;

		//T1
		vertices.push_back(Point(width/2, 0.0, -width/2));
		vertices.push_back(Point(-width/2, 0.0, width/2));
		vertices.push_back(Point(width/2, 0.0, width/2));

		//T2
		vertices.push_back(Point(width/2, 0.0, -width/2));
		vertices.push_back(Point(-width/2, 0.0, -width/2));
		vertices.push_back(Point(-width/2, 0.0, width/2));

		// Sending vertices to .3d file
		for (int i = 0; i < vertices.size(); i++) {

			fprintf(out, "%f %f %f \n", vertices[i].getX(), vertices[i].getY(), vertices[i].getZ());
		}
	}

	fclose(out);

}

// pôr o centro da caixa na origem?
void drawBox(float x, float y, float z, int nrDivisions, string fileName) {

	FILE *out;

	// open to write (cleans if file already exists or creates it if not)
	out = fopen(fileName.c_str(), "w");

	if (out != NULL) {

		// Vector to store the vertices
		std::vector<Point> vertices;

		float incX = x / nrDivisions;
		float incY = y / nrDivisions;
		float incZ = z / nrDivisions;

		float xDiv = 0;
		float yDiv = 0;
		float zDiv = 0;

		// base e topo em que o Y é fixo
		while (zDiv < z) {

			while (xDiv < x) {

				// base
				vertices.push_back(Point(xDiv, 0, zDiv));
				vertices.push_back(Point(xDiv + incX, 0, zDiv));
				vertices.push_back(Point(xDiv, 0, zDiv + incZ));

				// base
				vertices.push_back(Point(xDiv + incX, 0, zDiv));
				vertices.push_back(Point(xDiv + incX, 0, zDiv + incZ));
				vertices.push_back(Point(xDiv, 0, zDiv + incZ));

				// topo
				vertices.push_back(Point(xDiv, y, zDiv));
				vertices.push_back(Point(xDiv, y, zDiv + incZ));
				vertices.push_back(Point(xDiv + incX, y, zDiv));


				// topo
				vertices.push_back(Point(xDiv + incX, y, zDiv));
				vertices.push_back(Point(xDiv, y, zDiv + incZ));
				vertices.push_back(Point(xDiv + incX, y, zDiv + incZ));

				xDiv += incX;
			}

			xDiv = 0;
			zDiv += incZ;
		}

		xDiv = 0;
		yDiv = 0;
		zDiv = 0;

		// lados em que o x é fixo
		while (zDiv < z) {

			while (yDiv < y) {

				// lado esquerdo
				vertices.push_back(Point(x, yDiv, zDiv));
				vertices.push_back(Point(x, yDiv + incY, zDiv + incZ));
				vertices.push_back(Point(x, yDiv, zDiv + incZ));

				// lado esquerdo
				vertices.push_back(Point(x, yDiv + incY, zDiv));
				vertices.push_back(Point(x, yDiv + incY, zDiv + incZ));
				vertices.push_back(Point(x, yDiv, zDiv));

				// lado direito
				vertices.push_back(Point(0, yDiv, zDiv));
				vertices.push_back(Point(0, yDiv, zDiv + incZ));
				vertices.push_back(Point(0, yDiv + incY, zDiv + incZ));

				// lado direito
				vertices.push_back(Point(0, yDiv + incY, zDiv));
				vertices.push_back(Point(0, yDiv, zDiv));
				vertices.push_back(Point(0, yDiv + incY, zDiv + incZ));

				yDiv += incY;
			}

			yDiv = 0;
			zDiv += incZ;
		}

		xDiv = 0;
		yDiv = 0;
		zDiv = 0;

		// lados em que o z é fixo
		while (xDiv < x) {

			while (yDiv < y) {

				// frente
				vertices.push_back(Point(xDiv + incX, yDiv + incY, z));
				vertices.push_back(Point(xDiv, yDiv, z));
				vertices.push_back(Point(xDiv + incX, yDiv, z));

				// frente
				vertices.push_back(Point(xDiv + incX, yDiv + incY, z));
				vertices.push_back(Point(xDiv, yDiv + incY, z));
				vertices.push_back(Point(xDiv, yDiv, z));

				// tras
				vertices.push_back(Point(xDiv + incX, yDiv + incY, 0));
				vertices.push_back(Point(xDiv + incX, yDiv, 0));
				vertices.push_back(Point(xDiv, yDiv, 0));

				// tras
				vertices.push_back(Point(xDiv + incX, yDiv + incY, 0));
				vertices.push_back(Point(xDiv, yDiv, 0));
				vertices.push_back(Point(xDiv, yDiv + incY, 0));

				yDiv += incY;
			}

			yDiv = 0;
			xDiv += incX;
		}


		// Sending vertices to .3d file
		for (int i = 0; i < vertices.size(); i++) {

			fprintf(out, "%f %f %f \n", vertices[i].getX(), vertices[i].getY(), vertices[i].getZ());
		}
	}

	fclose(out);

}

void drawSphere(float r, int slices, int stacks, string fileName) {

	FILE *out;

	// open to write (cleans if file already exists or creates it if not)
	out = fopen(fileName.c_str(), "w");

	if (out != NULL) {

		// Vector to store the vertices
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

				vertices.push_back(Point(r * cos(beta) * sin(alpha), r * sin(beta), r * cos(beta) * cos(alpha)));
				vertices.push_back(Point(r * cos(beta) * sin(angulo_a1), r * sin(beta), r * cos(beta) * cos(angulo_a1)));
				vertices.push_back(Point(r * cos(angulo_b1) * sin(alpha), r * sin(angulo_b1), r * cos(angulo_b1) * cos(alpha)));

				vertices.push_back(Point(r * cos(beta) * sin(angulo_a1), r * sin(beta), r * cos(beta) * cos(angulo_a1)));
				vertices.push_back(Point(r * cos(angulo_b1) * sin(angulo_a1), r * sin(angulo_b1), r * cos(angulo_b1) * cos(angulo_a1)));
				vertices.push_back(Point(r * cos(angulo_b1) * sin(alpha), r * sin(angulo_b1), r * cos(angulo_b1) * cos(alpha)));

				alpha += a_step;
			}

			beta += b_step;
		}

		// Sending vertices to .3d file
		for (int i = 0; i < vertices.size(); i++) {

			fprintf(out, "%f %f %f \n", vertices[i].getX(), vertices[i].getY(), vertices[i].getZ());
		}
	}

	fclose(out);

}

void drawCone(float r, float h, int slices, int stacks, string fileName) {

	FILE *out;

	// open to write (cleans if file already exists or creates it if not)
	out = fopen(fileName.c_str(), "w");

	if (out != NULL) {

		// Vector to store the vertices
		std::vector<Point> vertices;

		float a = (2 * M_PI) / slices;

		//float hStack = h / stacks;
		//float rStack = ((h - hStack) * r) / h;

		for (int i = 0; i < slices; i++) {

            // triangulos da base rodados (0.5 * step) angulos para alinhar com
            // os triangulos dos lados
			// base
			vertices.push_back(Point(0, 0, 0));
			vertices.push_back(Point(r * cos(a * (i + 0.5)), 0, r * sin(a * (i + 0.5))));
			vertices.push_back(Point(r * cos(a * (i + 1 + 0.5)), 0, r * sin(a * (i + 1 + 0.5))));

            float oldRadius = r;
            float oldHeight = 0;

			// sides
			for (int j = 0; j < stacks; j++) {

				float newHeight = h / stacks * (j+1);
				float newRadius = (h - newHeight) * r / h;

				// triangle1
				vertices.push_back(Point(newRadius * sin(a * i), newHeight, newRadius * cos(a * i)));
				vertices.push_back(Point(oldRadius * sin(a * i), oldHeight, oldRadius * cos(a * i)));
				vertices.push_back(Point(oldRadius * sin(a * (i + 1)), oldHeight, oldRadius * cos(a * (i + 1))));

				// triangle 2
				vertices.push_back(Point(newRadius * sin(a * i), newHeight, newRadius * cos(a * i)));
				vertices.push_back(Point(oldRadius * sin(a * (i + 1)), oldHeight, oldRadius * cos(a * (i + 1))));
				vertices.push_back(Point(newRadius * sin(a * (i + 1)), newHeight, newRadius * cos(a * (i + 1))));

				oldRadius = newRadius;
				oldHeight = newHeight;

			}
		}

		// Sending vertices to .3d file
		for (int i = 0; i < vertices.size(); i++) {

			fprintf(out, "%f %f %f \n", vertices[i].getX(), vertices[i].getY(), vertices[i].getZ());
		}
	}

	fclose(out);

}

void drawPyramid(float length, float height, float width, string fileName) {

	FILE *out;

	// open to write (cleans if file already exists or creates it if not)
	out = fopen(fileName.c_str(), "w");

	if (out != NULL) {

		// Vector to store the vertices
		std::vector<Point> vertices; 

		// Triângulo da Frente
		vertices.push_back(Point(0.0, height, 0.0));
		vertices.push_back(Point(-length, 0.0, width));
		vertices.push_back(Point(length, 0.0, width));

		// Right
		vertices.push_back(Point(0.0, height, 0.0));
		vertices.push_back(Point(length, 0.0, width));
		vertices.push_back(Point(length, 0.0, -width));

		// Back
		vertices.push_back(Point(0.0, height, 0.0));
		vertices.push_back(Point(length, 0.0, -width));
		vertices.push_back(Point(-length, 0.0, -width));

		// Left 
		vertices.push_back(Point(0.0, height, 0.0));
		vertices.push_back(Point(-length, 0.0, -width));
		vertices.push_back(Point(-length, 0.0, width));

		// ponteiro dos relógios

		// Debaixo    
		vertices.push_back(Point(-length, 0.0, -width));
		vertices.push_back(Point(length, 0.0, width));
		vertices.push_back(Point(-length, 0.0, width));

		// Debaixo      
		vertices.push_back(Point(length, 0.0, -width));
		vertices.push_back(Point(length, 0.0, width));
		vertices.push_back(Point(-length, 0.0, -width));

		// Sending vertices to .3d file
		for (int i = 0; i < vertices.size(); i++) {

			fprintf(out, "%f %f %f \n", vertices[i].getX(), vertices[i].getY(), vertices[i].getZ());
		}
	}

	fclose(out);

}

void drawCylinder(float r, float height, int slices, string fileName) {

	FILE *out;

	// open to write (cleans if file already exists or creates it if not)
	out = fopen(fileName.c_str(), "w");

	if (out != NULL) {

		// Vector to store the vertices
		std::vector<Point> vertices;

		float a = (2 * M_PI) / slices;

		for (int i = 0; i < slices; i++) {

			// top
			vertices.push_back(Point(0, height / 2, 0));
			vertices.push_back(Point(r * cos(a * (i + 1)), height / 2, r * sin(a * (i + 1))));
			vertices.push_back(Point(r * cos(a * i), height / 2, r * sin(a * i)));

			// bottom
			vertices.push_back(Point(0, -height / 2, 0));
			vertices.push_back(Point(r * cos(a * i), -height / 2, r * sin(a * i)));
			vertices.push_back(Point(r * cos(a * (i + 1)), -height / 2, r * sin(a * (i + 1))));

			// side 1
			vertices.push_back(Point(r * cos(a * (i + 1)), height / 2, r * sin(a * (i + 1))));
			vertices.push_back(Point(r * cos(a * i), -height / 2, r * sin(a * i)));
			vertices.push_back(Point(r * cos(a * i), height / 2, r * sin(a * i)));

			// side 2
			vertices.push_back(Point(r * cos(a * (i + 1)), -height / 2, r * sin(a * (i + 1))));
			vertices.push_back(Point(r * cos(a * i), -height / 2, r * sin(a * i)));
			vertices.push_back(Point(r * cos(a * (i + 1)), height / 2, r * sin(a * (i + 1))));

		}

		// Sending vertices to .3d file
		for (int i = 0; i < vertices.size(); i++) {

			fprintf(out, "%f %f %f \n", vertices[i].getX(), vertices[i].getY(), vertices[i].getZ());
		}
	}

	fclose(out);

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

		// PLANE
		if (primitive.compare("plane") == 0 && argc == 4) {

			std::cout << "A criar um plano..." << std::endl;

			float width = std::stof(argv[2]);

			std::string file = argv[3];

			// Call triangle function
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

			// Call cilinder function
			drawCylinder(radius, height, slices, file);

			std::cout << "Cilindro criado." << std::endl;

			// writes to scene.xml
			writeToXML(file);

			std::cout << "Path do cilindro escrita no scene.xml com sucesso" << std::endl;
		}

		else {

			std::cout << argv[1] << " não é um sólido válido." << std::endl;
		}
	}

	return 0;
}
