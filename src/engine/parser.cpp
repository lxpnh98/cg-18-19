#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include "parser.h"
#include "engine.h"
#include "group.h"
#include "transform.h"

#include "tinyxml2.h"

using namespace tinyxml2;
using std::string;
using std::ifstream;

Group *makeGroup(XMLNode *scene);
std::vector<engine::figure> *loadModels(Group *g, std::vector<Transform*> *upT);

// Loads an XML file containing various references to .3d files
std::vector<engine::figure> *parser::loadXML(const char* path) {

	// Load XML document
	XMLDocument file;
	XMLError result = file.LoadFile(path);

	if (result != XML_SUCCESS) {

		throw std::runtime_error("Erro no carregamento do ficheiro XML.\n");
	}

	XMLNode *scene = file.FirstChildElement("scene");

	if (scene == nullptr) {

		throw std::runtime_error("Não encontrou scene no ficheiro.\n");
	}

	//XMLElement *first_group = scene->FirstChildElement("group");
    Group *g = makeGroup(scene);

	// Loop through model paths and load models
    std::vector<engine::figure> *loadedModels = loadModels(g, new std::vector<Transform*>());

	return loadedModels;
}

Group *makeGroup(XMLNode *scene) {
    Group *g = new Group();

    XMLNode *tag = scene->FirstChild();

	while (tag != nullptr) {

        string tagName = tag->Value();
        XMLElement *tagElement = tag->ToElement();

        if (strcmp(tagName.c_str(), "translate") == 0) {
            g->addTransform(new Translate(tagElement->DoubleAttribute("time"),
										  tagElement->DoubleAttribute("X"),
                                          tagElement->DoubleAttribute("Y"),
                                          tagElement->DoubleAttribute("Z")));
        } else if (strcmp(tagName.c_str(), "rotate") == 0) {
            g->addTransform(new Rotate(tagElement->DoubleAttribute("time"),
									   tagElement->DoubleAttribute("angle"),
                                       tagElement->DoubleAttribute("axisX"), 
                                       tagElement->DoubleAttribute("axisY"),
                                       tagElement->DoubleAttribute("axisZ")));
        } else if (strcmp(tagName.c_str(), "scale") == 0) {
            g->addTransform(new Scale(tagElement->DoubleAttribute("X"),
                                      tagElement->DoubleAttribute("Y"),
                                      tagElement->DoubleAttribute("Z")));
        } else if (strcmp(tagName.c_str(), "models") == 0) {
            XMLNode *models = tag->FirstChild();
            XMLElement *modelsElement;
            while (models != nullptr) {
                modelsElement = models->ToElement();
                // get model path
                string newModel = modelsElement->Attribute("file");  

                // path to model paths vector
                g->addModel(newModel);

                // next
                models = models->NextSibling(); // Get next model
            }
        } else if (strcmp(tagName.c_str(), "group") == 0) {
            Group *subGroup = makeGroup(tag->DeepClone(nullptr));
            subGroup->setUp(g);
            g->addSubGroup(subGroup);
		} else {
			printf("invalid tag\n");
		}
        // next
        tag = tag->NextSibling();
	}
    return g;
}

// upTs - tranforms from ascendent groups (initially empty)
std::vector<engine::figure> *loadModels(Group *g, std::vector<Transform*> *upTs) {
    std::vector<engine::figure> *loadedModels = new std::vector<engine::figure>();

    // transforms from current group
    std::vector<Transform*> *newTs = g->getTransforms();
    std::vector<Transform*> *Ts = new std::vector<Transform*>();
    Ts->insert(Ts->end(), upTs->begin(), upTs->end()); // concat upTs
    Ts->insert(Ts->end(), newTs->begin(), newTs->end()); // concat newTs

	std::vector<string> *modelPaths = g->getModels();
	for (auto p : *modelPaths) {

		ifstream modelFile;
		modelFile.open(p);
		engine::figure newModel;

        // copy transforms to figure
        newModel.transforms = new std::vector<Transform*>();
        newModel.transforms->insert(newModel.transforms->end(), Ts->begin(), Ts->end());
        // load vertices
		while (!modelFile.eof()) {
			engine::vertex vertex;
			modelFile >> vertex.x >> vertex.y >> vertex.z;
			newModel.vertices.push_back(vertex);
		}
		loadedModels->push_back(newModel);
	}

    // load models in subgroups
    for (auto subGroup : *g->getSubGroups()) {
        std::vector<engine::figure> *subModels = loadModels(subGroup, Ts);
        loadedModels->insert(loadedModels->end(), subModels->begin(), subModels->end()); 
    }

    return loadedModels;
}

