#include "group.h"
#include "colour.h"
#include "light.h"

using std::vector;

Group::Group() {
    this->up = nullptr;
    this->transforms = new std::vector<Transform *>();
    this->modelPaths = new std::vector<string>();
    this->subGroups = new std::vector<Group *>();
	this->lights = new std::vector<Light *>();
    this->texture = string();
    this->diffuse = Colour();
    this->specular = Colour();
    this->emissive = Colour();
    this->ambient = Colour();
    this->typeDiff = 0;
    this->typeSpec = 0;
    this->typeEmis = 0;
    this->typeAmbi = 0;
    this->typeShine = 0.0;
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

vector<Light *> *Group::getLight() {
	return this->lights;
}

string Group::getTexture() {
    return this->texture;
}
Colour Group::getDiffuse() {
    return this->diffuse;
}
Colour Group::getSpecular() {
    return this->specular;
}
Colour Group::getEmissive() {
    return this->emissive;
}
Colour Group::getAmbient() {
    return this->ambient;
}
int Group::getTypeDiff() {
    return this->typeDiff;
}
int Group::getTypeSpec() {
    return this->typeSpec;
}
int Group::getTypeEmis() {
    return this->typeEmis;
}
int Group::getTypeAmbi() {
    return this->typeAmbi;
}
float Group::getTypeShine() {
    return this->typeShine;
}
void Group::setUp(Group *g) {
    this->up = g;
}
void Group::addTransform(Transform *t) {
    this->transforms->push_back(t);
}
void Group::addModel(string m, string t, Colour diffuse, Colour specular, Colour emissive, Colour ambient,
                                    int typeDiff, int typeSpec, int typeEmis, int typeAmbi, float typeShine) {
    this->modelPaths->push_back(m);
    this->texture = t;
    this->diffuse = diffuse;
    this->specular = specular;
    this->emissive = emissive;
    this->ambient = ambient;
    this->typeDiff = typeDiff;
    this->typeSpec = typeSpec;
    this->typeEmis = typeEmis;
    this->typeAmbi = typeAmbi;
    this->typeShine = typeShine;
}
void Group::addSubGroup(Group *g) {
    this->subGroups->push_back(g);
}

void Group::addLight(Light* l) {
	this->lights->push_back(l);
}