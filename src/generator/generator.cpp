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
•   Plane (a square in the XZ plane, centred in the origin, made with 2 triangles)
•   Box (requires X, Y and Z dimensions, and optionally the number of divisions)
•   Sphere (requires radius, slices and stacks)
•   Cone (requires bottom radius, height, slices and stacks)
•   EXTRA: • pyramid (height, width)
		   • cylinder (radius, height, length, slices)
*/

void plane(float width, string fileName) {

	FILE *out;

	fopen_s(&out, fileName.c_str(), "w"); //open to write (cleans if file already exists or creates it if not)

	if (out != NULL) {
		std::vector<Point> vertices; // Vector to store the vertices

		//T1
		vertices.push_back(Point(width / 2, 0.0, -width / 2));
		vertices.push_back(Point(-width / 2, 0.0, width / 2));
		vertices.push_back(Point(width / 2, 0.0, width / 2));

		//T2
		vertices.push_back(Point(width / 2, 0.0, -width / 2));
		vertices.push_back(Point(-width / 2, 0.0, -width / 2));
		vertices.push_back(Point(-width / 2, 0.0, width / 2));

		// Sending vertices to .3d file
		for (int nVert = 0; nVert < vertices.size(); nVert++) {

			fprintf(out, "%f %f %f \n", vertices[nVert].getX(), vertices[nVert].getY(), vertices[nVert].getZ());
		}
	}

	fclose(out);

}

int main(int argc, char** argv) {

	SetConsoleOutputCP(CP_UTF8); // UTF-8 mode for Windows console

	if (argv[1] != NULL) { // Checks if program receives nothing to process

		std::string form = argv[1];
		std::cout << form << " é argv1." << std::endl;

		// PLANE
		if (form.compare("plane") == 0 && argc == 4) {
			std::cout << "Está a criar um plano." << std::endl;

			// Prints width and filename just for DEBUG purposes
			std::cout << "WIDTH: " << argv[2] << std::endl;
			float width = std::stof(argv[2]);
			std::cout << width << std::endl;

			std::cout << "FILENAME: " << argv[3] << std::endl;

			// Call triangle criation function
			plane(width, argv[3]);
		}
		// BOX
		else if (form.compare("box") == 0 && argc == 7) {
		}
		else {
			std::cout << argv[1] << " não é válido." << std::endl;
		}
	}


	return 0;
}