#include "group.h"

using std::vector;

class Group {
    Group() {
        up = nullptr;
        transforms = new std::vector<>();
        models = new std::vector<>();
        subGroups = new std::vector<>();
    };

    std::vector<Transform *> getTransforms() {
        return transforms;
    }
    std::vector<string> getModels() {
        return modelPaths;
    }
    std::vector<Group *> getSubGroups() {
        return subGroups;
    }
    void setUp(Group *g) {
        up = g;
    }
    void addTranform(Transform *t) {
        transforms.push_back(t);
    }
    void addModel(string m) {
        modelPaths.push_back(m);
    }
    void addSubGroup(Group *g) {
        subGroups.push_back(g);
    }
}
