#ifndef GROUP
#define GOUP

#include <vector>
#include <string>
#include "transform.h"

using namespace std;

class Group {
    private:
        Group *up;
        std::vector<Transform *> *transforms;
        std::vector<string> *modelPaths;
        std::vector<Group *> *subGroups;
        string texture;

    public:
        Group();
        std::vector<Transform*> *getTransforms();
        std::vector<string> *getModels();
        std::vector<Group*> *getSubGroups();
        string getTexture();
        void setUp(Group *g);
        void addTransform(Transform *t);
        void addModel(string m, string t);
        void addSubGroup(Group *g);
};

#endif//GROUP
