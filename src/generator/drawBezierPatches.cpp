#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "drawBezierPatches.h"
#include "point.h"

using namespace std;

Point bezierPoint(std::vector<int> patch, std::vector<Point *> points, float u, float v) {

    #define P(i)    points[patch[i]]

    float x1 = (1-u)*(1-u)*(1-u)*P(0)->getX()  + 3*(1-u)*(1-u)*u*P(1)->getX()  + 3*(1-u)*u*u*P(2)->getX()  + u*u*u*P(3)->getX();
    float x2 = (1-u)*(1-u)*(1-u)*P(4)->getX()  + 3*(1-u)*(1-u)*u*P(5)->getX()  + 3*(1-u)*u*u*P(6)->getX()  + u*u*u*P(7)->getX();
    float x3 = (1-u)*(1-u)*(1-u)*P(8)->getX()  + 3*(1-u)*(1-u)*u*P(9)->getX()  + 3*(1-u)*u*u*P(10)->getX() + u*u*u*P(11)->getX();
    float x4 = (1-u)*(1-u)*(1-u)*P(12)->getX() + 3*(1-u)*(1-u)*u*P(13)->getX() + 3*(1-u)*u*u*P(14)->getX() + u*u*u*P(15)->getX();

    float y1 = (1-u)*(1-u)*(1-u)*P(0)->getY()  + 3*(1-u)*(1-u)*u*P(1)->getY()  + 3*(1-u)*u*u*P(2)->getY()  + u*u*u*P(3)->getY();
    float y2 = (1-u)*(1-u)*(1-u)*P(4)->getY()  + 3*(1-u)*(1-u)*u*P(5)->getY()  + 3*(1-u)*u*u*P(6)->getY()  + u*u*u*P(7)->getY();
    float y3 = (1-u)*(1-u)*(1-u)*P(8)->getY()  + 3*(1-u)*(1-u)*u*P(9)->getY()  + 3*(1-u)*u*u*P(10)->getY() + u*u*u*P(11)->getY();
    float y4 = (1-u)*(1-u)*(1-u)*P(12)->getY() + 3*(1-u)*(1-u)*u*P(13)->getY() + 3*(1-u)*u*u*P(14)->getY() + u*u*u*P(15)->getY();

    float z1 = (1-u)*(1-u)*(1-u)*P(0)->getZ()  + 3*(1-u)*(1-u)*u*P(1)->getZ()  + 3*(1-u)*u*u*P(2)->getZ()  + u*u*u*P(3)->getZ();
    float z2 = (1-u)*(1-u)*(1-u)*P(4)->getZ()  + 3*(1-u)*(1-u)*u*P(5)->getZ()  + 3*(1-u)*u*u*P(6)->getZ()  + u*u*u*P(7)->getZ();
    float z3 = (1-u)*(1-u)*(1-u)*P(8)->getZ()  + 3*(1-u)*(1-u)*u*P(9)->getZ()  + 3*(1-u)*u*u*P(10)->getZ() + u*u*u*P(11)->getZ();
    float z4 = (1-u)*(1-u)*(1-u)*P(12)->getZ() + 3*(1-u)*(1-u)*u*P(13)->getZ() + 3*(1-u)*u*u*P(14)->getZ() + u*u*u*P(15)->getZ();

    float x = (1-v)*(1-v)*(1-v)*x1 +  3*(1-v)*(1-v)*v*x2 + 3*(1-v)*v*v*x3 +  v*v*v*x4;
    float y = (1-v)*(1-v)*(1-v)*y1 +  3*(1-v)*(1-v)*v*y2 + 3*(1-v)*v*v*y3 +  v*v*v*y4;
    float z = (1-v)*(1-v)*(1-v)*z1 +  3*(1-v)*(1-v)*v*z2 + 3*(1-v)*v*v*z3 +  v*v*v*z4;

    return Point(x, y, z);
    #undef P
}

void drawBezierPlane(std::vector<Point> *vertices, std::vector<int> patch, std::vector<Point *> points,
                     float u, float v, float step) {
    Point p1 = bezierPoint(patch, points, u     , v);
    Point p2 = bezierPoint(patch, points, u     , v+step);
    Point p3 = bezierPoint(patch, points, u+step, v);
    Point p4 = bezierPoint(patch, points, u+step, v+step);

    vertices->push_back(p1);
    vertices->push_back(p4);
    vertices->push_back(p2);

    vertices->push_back(p4);
    vertices->push_back(p1);
    vertices->push_back(p3);

    // back face
    vertices->push_back(p1);
    vertices->push_back(p2);
    vertices->push_back(p4);

    vertices->push_back(p4);
    vertices->push_back(p3);
    vertices->push_back(p1);
}

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

    // Generate vertices
    for (int i = 0; i < num_patches; i++) {
        float u = 0.0;
        float v = 0.0;
        float step = 1.0 / tesselation;

        for (int j = 0; j < tesselation; j++) {
            for (int k = 0; k < tesselation; k++) {
                drawBezierPlane(&vertices, patches[i], control_points, u, v, step);
                v += step;
            }
            u += step;
            v = 0.0;
        }
    }

    // Sending vertices to .3d file
    for (int i = 0; i < vertices.size(); i++) {
        fprintf(out, "%f %f %f \n", vertices[i].getX(), vertices[i].getY(), vertices[i].getZ());
    }

	fclose(out);

}
