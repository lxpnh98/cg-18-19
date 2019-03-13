#ifndef TRANSFORM
#define TRANSFORM

using namespace std;

class Transform {};

class Rotate : public Transform {
    private:
        float angle;
        float x;
        float y;
        float z;
    public:
        //gets
};

class Translate : public Transform {
    private:
        float x;
        float y;
        float z;
    public:
        //gets
};

class Scale : public Transform {
    private:
        float x;
        float y;
        float z;
    public:
        //gets
};

#endif //TRANSFORM
