#include <stdio.h>
#include <windows.h>
#include <iostream>
#include <fstream>
#include <vector> 
#include <string>

#include "point.h"

#define _USE_MATH_DEFINES
#include <math.h>

using namespace std;

/*
TODO:
- Plane (a square in the XZ plane, centred in the origin, made with 2 triangles)
- Box (requires X, Y and Z dimensions, and optionally the number of divisions)
- Sphere (requires radius, slices and stacks)
- Cone (requires bottom radius, height, slices and stacks)
- EXTRA: 
	pyramid (height, width)
	cylinder (radius, height, length, slices)
*/

void getPlane(float width, string fileName) {

	FILE *out;

	// open to write (cleans if file already exists or creates it if not)
	fopen_s(&out, fileName.c_str(), "w");

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

void getBox(float x, float y, float z, int nrDivisions, string fileName) {

	FILE *out;

	// open to write (cleans if file already exists or creates it if not)
	fopen_s(&out, fileName.c_str(), "w");

	if (out != NULL) {

		// Vector to store the vertices
		std::vector<Point> vertices;

		// TODO

		// Sending vertices to .3d file
		for (int i = 0; i < vertices.size(); i++) {

			fprintf(out, "%f %f %f \n", vertices[i].getX(), vertices[i].getY(), vertices[i].getZ());
		}
	}

	fclose(out);

}

void getSphere(float r, int slices, int stacks, string fileName) {

	FILE *out;

	// open to write (cleans if file already exists or creates it if not)
	fopen_s(&out, fileName.c_str(), "w");

	if (out != NULL) {

		// Vector to store the vertices
		std::vector<Point> vertices;

		// TODO

		// Sending vertices to .3d file
		for (int i = 0; i < vertices.size(); i++) {

			fprintf(out, "%f %f %f \n", vertices[i].getX(), vertices[i].getY(), vertices[i].getZ());
		}
	}

	fclose(out);

}

void getCone(float r, float height, int slices, int stacks, string fileName) {

	FILE *out;

	// open to write (cleans if file already exists or creates it if not)
	fopen_s(&out, fileName.c_str(), "w");

	if (out != NULL) {

		// Vector to store the vertices
		std::vector<Point> vertices;

		// TODO

		// Sending vertices to .3d file
		for (int i = 0; i < vertices.size(); i++) {

			fprintf(out, "%f %f %f \n", vertices[i].getX(), vertices[i].getY(), vertices[i].getZ());
		}
	}

	fclose(out);

}

void getPyramid(float length, float height, float width, string fileName) {

	FILE *out;

	// open to write (cleans if file already exists or creates it if not)
	fopen_s(&out, fileName.c_str(), "w");

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

void getCylinder(float r, float height, int stacks, int slices, string fileName) {

	FILE *out;

	// open to write (cleans if file already exists or creates it if not)
	fopen_s(&out, fileName.c_str(), "w");

	if (out != NULL) {

		// Vector to store the vertices
		std::vector<Point> vertices;

		// TODO

		// Sending vertices to .3d file
		for (int i = 0; i < vertices.size(); i++) {

			fprintf(out, "%f %f %f \n", vertices[i].getX(), vertices[i].getY(), vertices[i].getZ());
		}
	}

	fclose(out);

}

int main(int argc, char** argv) {

	SetConsoleOutputCP(CP_UTF8); // UTF-8 mode for Windows console

	if (argv[1] != NULL) { // Checks if program receives nothing to process

		std::string form = argv[1];

		// PLANE
		if (form.compare("plane") == 0 && argc == 4) {

			std::cout << "Queres criar um plano." << std::endl;

			float width = std::stof(argv[2]);

			std::string file = argv[3];

			// Call triangle function
			getPlane(width, file);
		}

		else if (form.compare("box") == 0 && argc == 7) {

			std::cout << "Queres criar um cubo." << std::endl;

			float x, y, z;

			x = std::stof(argv[2]);
			y = std::stof(argv[3]);
			z = std::stof(argv[4]);

			int nrDivisions = std::stoi(argv[5]);

			std::string file = argv[6];

			// Call box function
			getBox(x, y, z, nrDivisions, file);
		}

		else if (form.compare("sphere") == 0 && argc == 6) {

			std::cout << "Queres criar uma esfera." << std::endl;
		
			float radius = std::stof(argv[2]);

			int slices = std::stoi(argv[3]);

			int stacks = std::stoi(argv[4]);

			std::string file = argv[5];

			// Call sphere function
			getSphere(radius, slices, stacks, file);
		}

		else if (form.compare("cone") == 0 && argc == 7) {

			std::cout << "Queres criar um cone." << std::endl;

			float radius = std::stof(argv[2]);

			float height = std::stof(argv[3]);

			int slices = std::stoi(argv[4]);

			int stacks = std::stoi(argv[5]);

			std::string file = argv[6];

			// Call cone function
			getCone(radius, height, slices, stacks, file);

		}

		else if (form.compare("pyramid") == 0 && argc == 6) {

			std::cout << "Queres criar uma pirâmide." << std::endl;

			float height = std::stof(argv[2]);

			float width = std::stof(argv[3]);

			float length = std::stof(argv[4]);

			std::string file = argv[5];

			// Call pyramid function
			getPyramid(height, width, length, file);

		}

		else if (form.compare("cilinder") == 0 && argc == 7) {

			std::cout << "Queres criar um cilindro." << std::endl;

			float radius = std::stof(argv[2]);

			float height = std::stof(argv[3]);

			int slices = std::stoi(argv[4]);

			int stacks = std::stoi(argv[5]);

			std::string file = argv[6];

			// Call cilinder function
			getCylinder(radius, height, slices, stacks, file);

		}

		else {

			std::cout << argv[1] << " não é um sólido válido." << std::endl;
		}
	}


	return 0;
}