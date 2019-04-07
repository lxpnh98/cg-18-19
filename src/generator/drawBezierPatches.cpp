#include <iostream>
#include <sstream>
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

    // number of patches
    fgets(line, 1023, in);
    int num_patches = atoi(line);

    cout << num_patches << '\n';

    // patch indexes
    std::vector<int> patches[num_patches];
    int tmp;
    for (int i = 0; i < num_patches; i++) {
        fgets(line, 1023, in);
        stringstream ss(line);
        while(ss >> tmp) {
            patches[i].push_back(tmp);
            if (ss.peek() == ',') {
                ss.ignore();
            }
        }
    }

    // number of control points
    fgets(line, 1023, in);
    int num_points = atoi(line);

    // patch indexes
    std::vector<Point *> control_points;
    float x, y, z;
    for (int i = 0; i < num_points; i++) {
        fgets(line, 1023, in);
        stringstream ss(line);
        ss >> x;
        if (ss.peek() == ',') {
            ss.ignore();
        }
        ss >> y;
        if (ss.peek() == ',') {
            ss.ignore();
        }
        ss >> z;
        if (ss.peek() == ',') {
            ss.ignore();
        }
        control_points.push_back(new Point(x, y, z));
    }

    // print info
    cout << num_patches << '\n';
    for (int i = 0; i < num_patches; i++) {
        for(auto n : patches[i]) {
            cout << n << ", ";
        }
        cout << '\n';
    }
    cout << num_points << '\n';
    for(auto p : control_points) {
        cout << p->getX() << ", " << p->getY() << ", " << p->getZ() << '\n';
    }
    cout << '\n';

    // Vector to store the vertices
    std::vector<Point> vertices;

    // Sending vertices to .3d file
    for (int i = 0; i < vertices.size(); i++) {
        fprintf(out, "%f %f %f \n", vertices[i].getX(), vertices[i].getY(), vertices[i].getZ());
    }

	fclose(out);

}
