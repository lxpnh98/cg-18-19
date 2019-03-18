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

    public:
        Group();
        std::vector<Transform*> *getTransforms();
        std::vector<string> *getModels();
        std::vector<Group*> *getSubGroups();
        void setUp(Group *g);
        void addTransform(Transform *t);
        void addModel(string m);
        void addSubGroup(Group *g);
};

#endif//GROUP
