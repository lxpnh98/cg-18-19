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

	std::vector<string> *modelPaths = g->getModels();
    std::vector<engine::figure> *loadedModels = new std::vector<engine::figure>();

	for (auto p : *modelPaths) {

		ifstream modelFile;
		modelFile.open(p);
		engine::figure newModel;

		while (!modelFile.eof()) {

			engine::vertex vertex;
			modelFile >> vertex.x >> vertex.y >> vertex.z;
			newModel.vertices.push_back(vertex);
		}

		loadedModels->push_back(newModel);
	}

	return loadedModels;
}

Group *makeGroup(XMLNode *scene) {
    Group *g = new Group();

    XMLNode *tag = scene->FirstChild();

	while (scene != nullptr) {

        string tagName = tag->Value();
        XMLElement *tagElement = tag->ToElement();

        if (strcmp(tagName.c_str(), "translate") == 0) {
            
            g->addTransform(new Translate(tagElement->DoubleAttribute("X"),
                                          tagElement->DoubleAttribute("Y"),
                                          tagElement->DoubleAttribute("Z")));
        }
        if (strcmp(tagName.c_str(), "rotate") == 0) {
            g->addTransform(new Rotate(tagElement->DoubleAttribute("angle"),
                                       tagElement->DoubleAttribute("axisX"), 
                                       tagElement->DoubleAttribute("axisY"),
                                       tagElement->DoubleAttribute("axisZ")));
        }
        if (strcmp(tagName.c_str(), "scale") == 0) {
            g->addTransform(new Scale(tagElement->DoubleAttribute("X"), tagElement->DoubleAttribute("Y"), tagElement->DoubleAttribute("Z")));
        }
        if (strcmp(tagName.c_str(), "models") == 0) {
            XMLNode *models = scene->FirstChild();
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
        }
        if (strcmp(tagName.c_str(), "group") == 0) {
            Group *subGroup = makeGroup(scene);
            subGroup->setUp(g);
            g->addSubGroup(subGroup);
        }

        // next
        scene = scene->NextSibling();
	}
    return g;
}
