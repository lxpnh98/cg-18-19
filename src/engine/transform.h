#ifndef TRANSFORM
#define TRANSFORM

using namespace std;

class Transform {
    public:
    Transform();
};

class Rotate : public Transform {
    private:
        double angle;
        double x;
        double y;
        double z;
    public:
        Rotate(double, double, double, double);
};

class Translate : public Transform {
    private:
        double x;
        double y;
        double z;
    public:
        Translate(double, double, double);
};

class Scale : public Transform {
    private:
        double x;
        double y;
        double z;
    public:
        Scale(double, double, double);
};

#endif //TRANSFORM
