#include "group.h"
#include "colour.h"

using std::vector;

Group::Group() {
    this->up = nullptr;
    this->transforms = new std::vector<Transform *>();
    this->modelPaths = new std::vector<string>();
    this->subGroups = new std::vector<Group *>();
    this->texture = string();
    this->colour = Colour();
    this->type = 0;
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
string Group::getTexture() {
    return this->texture;
}
int Group::getType() {
    return this->type;
}
void Group::setUp(Group *g) {
    this->up = g;
}
void Group::addTransform(Transform *t) {
    this->transforms->push_back(t);
}
void Group::addModel(string m, string t, string corR, string corG, string corB, int type) {
    this->modelPaths->push_back(m);
    this->texture = t;
    this->colour = Colour(stof(corR), stof(corG), stof(corB));
    this->type = type;
}
void Group::addSubGroup(Group *g) {
    this->subGroups->push_back(g);
}
