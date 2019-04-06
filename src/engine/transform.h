#ifndef TRANSFORM
#define TRANSFORM

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
    public:
        Rotate(double,double, double, double, double);
        void apply();
};

class Translate : public Transform {
    private:
		double time;
        double x;
        double y;
        double z;
    public:
        Translate(double, double, double, double);
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
