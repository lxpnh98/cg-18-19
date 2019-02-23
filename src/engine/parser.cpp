#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include "parser.h"
#include "engine.h"

#include "tinyxml2.h"

using namespace tinyxml2;
using std::string;
using std::ifstream;

// Loads an XML file containing various references to .3d files
std::vector<engine::model> parser::loadXML(const char* path) {

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

	// vector to save paths to models
	std::vector<string> modelPaths;

	XMLElement *models = scene->FirstChildElement("model");

	while (models != nullptr) {

		// get model path
		string newModel = models->Attribute("file");  

		// path to model paths vector
		modelPaths.push_back(newModel);

		// next
		models = models->NextSiblingElement("model"); // Get next model
	}

	// Loop through model paths and load models

	std::vector<engine::model> loadedModels;

	for (auto p : modelPaths) {

		ifstream modelFile;
		modelFile.open(p);
		engine::model newModel;

		while (!modelFile.eof()) {

			engine::vertex vertex;
			modelFile >> vertex.x >> vertex.y >> vertex.z;
			newModel.vertices.push_back(vertex);
		}

		loadedModels.push_back(newModel);
	}

	return loadedModels;
}