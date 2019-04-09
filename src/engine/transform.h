#ifndef TRANSFORM
#define TRANSFORM

#include "../generator/point.h"
#include <vector>

using namespace std;

class Transform {
    public:
        Transform();
        virtual void apply();
};

class Rotate : public Transform {
    private:
		double time;
        double angle;
        double x;
        double y;
        double z;
		double rodar = 0;
    public:
        Rotate(double,double, double, double, double);
        void apply();
};

class Translate : public Transform {
    private:
		double time;
		double Y[3] = { 0, 1, 0 };
		int POINT_COUNT;
		double **p;
		double rodar = 0;
    public:
        Translate(double);
		void addPTranslate(Point*);
		void buildRotMatrix(double*, double*, double*, double*);
		void cross(double*, double*, double*);
		void normalize(double*);
		double length(double*);
		void multMatrixVector(double*, double*, double*);
		void getCatmullRomPoint(double, double*, double*, double*, double*, double*, double*);
		void getGlobalCatmullRomPoint(double, double*, double*);
		void renderCatmullRomCurve();
        void apply();
};

class Scale : public Transform {
    private:
        double x;
        double y;
        double z;
    public:
        Scale(double, double, double);
        void apply();
};

#endif //TRANSFORM
