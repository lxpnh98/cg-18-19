#include "group.h"

using std::vector;

Group::Group() {
    this->up = nullptr;
    this->transforms = new std::vector<Transform *>();
    this->modelPaths = new std::vector<string>();
    this->subGroups = new std::vector<Group *>();
};

std::vector<Transform *> *Group::getTransforms() {
    return this->transforms;
}
std::vector<string> *Group::getModels() {
    return this->modelPaths;
}
std::vector<Group *> *Group::getSubGroups() {
    return this->subGroups;
}
void Group::setUp(Group *g) {
    this->up = g;
}
void Group::addTransform(Transform *t) {
    this->transforms->push_back(t);
}
void Group::addModel(string m) {
    this->modelPaths->push_back(m);
}
void Group::addSubGroup(Group *g) {
    this->subGroups->push_back(g);
}
