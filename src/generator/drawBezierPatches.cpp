#include <iostream>
#include <string>
#include <vector>

#include "drawBezierPatches.h"
#include "point.h"

using namespace std;


void drawBezierPatches(string patchesFile, int tesselation, string fileName) {
	FILE *in;
	FILE *out;

    // open to read
    in = fopen(patchesFile.c_str(), "r");
    if (in == NULL) return;

	// open to write (cleans if file already exists or creates it if not)
	out = fopen(fileName.c_str(), "w");
	if (out == NULL) return;
		
    char line[1024]; 
    while (fgets(line, 1023, in) != NULL) {
        cout << line << '\n';
    }

    // Vector to store the vertices
    std::vector<Point> vertices;

    // Sending vertices to .3d file
    for (int i = 0; i < vertices.size(); i++) {
        fprintf(out, "%f %f %f \n", vertices[i].getX(), vertices[i].getY(), vertices[i].getZ());
    }

	fclose(out);

}
