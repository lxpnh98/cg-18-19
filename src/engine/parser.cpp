#include <vector>
#include <string>
#include <unordered_map>
#include <iostream>
#include <fstream>
#include "parser.h"
#include "engine.h"
#include "group.h"
#include "transform.h"
#include "point.h"
#include "loadTexture.h"
#include "colour.h"

#include "tinyxml2.h"

// Glut has to be included last to avoid errors
// (for example, C2381 'exit': redefinition; '__declspec(noreturn)' or '[[noreturn]]' differs)
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

using namespace tinyxml2;
using std::string;
using std::ifstream;

Group *makeGroup(XMLNode *scene);
std::vector<engine::figure> *loadModels(Group *g, std::vector<Transform*> *upT, std::unordered_map<string, GLuint> *textures);

// Loads an XML file containing various references to .3d files
std::vector<engine::figure> *parser::loadXML(const char* path) {

    // Load XML document
    XMLDocument file;
    XMLError result = file.LoadFile(path);

    if (result != XML_SUCCESS) {

        cout << "Erro a carregar ficheiro";
        throw std::runtime_error("Erro no carregamento do ficheiro XML.\n");
    }

    XMLNode *scene = file.FirstChildElement("scene");

    if (scene == nullptr) {

        cout << "Não encontrou scene";
        throw std::runtime_error("Não encontrou scene no ficheiro.\n");

    }

    //XMLElement *first_group = scene->FirstChildElement("group");
    Group *g = makeGroup(scene);

    // Loop through model paths and load models
    std::vector<engine::figure> *loadedModels = loadModels(g, new std::vector<Transform*>(), new std::unordered_map<string, GLuint>());

    return loadedModels;
}

Group *makeGroup(XMLNode *scene) {
    Group *g = new Group();

    XMLNode *tag = scene->FirstChild();

    Colour diffuse  = Colour();
    Colour specular = Colour();
    Colour emissive = Colour();
    Colour ambient  = Colour();
    int typeDiff = 0;
    int typeSpec = 0;
    int typeEmis = 0;
    int typeAmbi = 0;
    float typeShine = 0.0;

	int nrLight = 0;

    while (tag != nullptr) {

        string tagName = tag->Value();
        XMLElement *tagElement = tag->ToElement();

        if (strcmp(tagName.c_str(), "models") == 0) {

            XMLNode *models = tag->FirstChild();
            XMLElement *modelsElement;
            while (models != nullptr) {
                modelsElement = models->ToElement();
                // get model path
                string newModel = modelsElement->Attribute("file");

                string texture;
                if (modelsElement->Attribute("texture")) {
                    texture = modelsElement->Attribute("texture");
                }

                if (modelsElement->Attribute("diffR") && modelsElement->Attribute("diffG") && modelsElement->Attribute("diffB")) {
                    diffuse = Colour(stof(modelsElement->Attribute("diffR")), stof(modelsElement->Attribute("diffG")), 
                                    stof(modelsElement->Attribute("diffB")));
                    typeDiff = 1;
                }
                if (modelsElement->Attribute("specR") && modelsElement->Attribute("specG") && modelsElement->Attribute("specB")) {
                    specular = Colour(stof(modelsElement->Attribute("specR")), stof(modelsElement->Attribute("specG")), 
                                    stof(modelsElement->Attribute("specB")));
                    typeSpec = 1;
                }
                if (modelsElement->Attribute("emisR") && modelsElement->Attribute("emisG") && modelsElement->Attribute("emisB")) {
                    emissive = Colour(stof(modelsElement->Attribute("emisR")), stof(modelsElement->Attribute("emisG")), 
                                    stof(modelsElement->Attribute("emisB")));
                    typeEmis = 1;
                }
                if (modelsElement->Attribute("ambiR") && modelsElement->Attribute("ambiG") && modelsElement->Attribute("ambiB")) {
                    ambient = Colour(stof(modelsElement->Attribute("ambiR")), stof(modelsElement->Attribute("ambiG")), 
                                    stof(modelsElement->Attribute("ambiB")));
                    typeAmbi = 1;
                }
                if (modelsElement->Attribute("shine")) {
                    typeShine = stof(modelsElement->Attribute("shine"));
                }

                // path to model paths vector
                g->addModel(newModel, texture, diffuse, specular, emissive, ambient,
                            typeDiff, typeSpec, typeEmis, typeAmbi, typeShine);

                // next
                models = models->NextSibling(); // Get next model
            }
		}
		else if (strcmp(tagName.c_str(), "lights") == 0) {

			XMLNode *lights = tag->FirstChild();
			XMLElement *lightsElement;
			string type = "";

			glEnable(GL_LIGHTING);

			float x = 0;
			float y = 0;
			float z = 0;

			while (lights != nullptr) {

				lightsElement = lights->ToElement();

				if (lightsElement->Attribute("type")) {
					type = lightsElement->Attribute("type");
				}
				if (lightsElement->Attribute("X")) {
					x = stof(lightsElement->Attribute("X"));
				}
				if (lightsElement->Attribute("Y")) {
					y = stof(lightsElement->Attribute("Y"));
				}
				if (lightsElement->Attribute("Z")) {
					z = stof(lightsElement->Attribute("Z"));
				}

				Light* light = new Light(nrLight, type, x, y, z);

				g->addLight(light);

				// next
				lights = lights->NextSibling();

				nrLight++;

			}

		}

        else if (strcmp(tagName.c_str(), "translate") == 0) {

            double xT = 0;
            double yT = 0;
            double zT = 0;
            
            double timeT = 0;

            if (tagElement->Attribute("time")) {

                timeT = atoi(tagElement->Attribute("time"));

            }

            Translate* t = new Translate(timeT);

            XMLNode * node1 = tag->FirstChild();

            for (; node1; node1 = node1->NextSibling()) {

                XMLElement* pElement1 = node1->ToElement();

                if (strcmp(pElement1->Name(), "point") == 0) {

                    if (pElement1->Attribute("X")) {
                        xT = pElement1->DoubleAttribute("X");
                    }
                    if (pElement1->Attribute("Y")) {
                        yT = pElement1->DoubleAttribute("Y");
                    }
                    if (pElement1->Attribute("Z")) {
                        zT = pElement1->DoubleAttribute("Z");
                    }

                    t->addPTranslate(new Point(xT, yT, zT));
                }
            }

            g->addTransform(t);

        } else if (strcmp(tagName.c_str(), "rotate") == 0) {

            double angle = 0;
            double axisx = 0;
            double axisy = 0;
            double axisz = 0;
            double time = 0;

            if (tagElement->Attribute("angle")) {
                angle = tagElement->DoubleAttribute("angle");
            }

            if (tagElement->Attribute("time")) {
                time = tagElement->DoubleAttribute("time");
            }

            if (tagElement->Attribute("axisX")) {
                axisx = tagElement->DoubleAttribute("axisX");
            }
            if (tagElement->Attribute("axisY")) {
                axisy = tagElement->DoubleAttribute("axisY");
            }
            if (tagElement->Attribute("axisZ")) {
                axisz = tagElement->DoubleAttribute("axisZ");
            }

            Rotate* r = new Rotate(time, angle, axisx, axisy, axisz);

            g->addTransform(r);

        } else if (strcmp(tagName.c_str(), "scale") == 0) {

            g->addTransform(new Scale(tagElement->DoubleAttribute("X"),
                                      tagElement->DoubleAttribute("Y"),
                                      tagElement->DoubleAttribute("Z")));

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
std::vector<engine::figure> *loadModels(Group *g, std::vector<Transform*> *upTs, std::unordered_map<string, GLuint> *textures) {
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

        std::vector<float> vertexVec = std::vector<float>();
        std::vector<float> normalVec = std::vector<float>();
        std::vector<float> textureVec = std::vector<float>();

        // copy transforms to figure
        newModel.transforms = new std::vector<Transform*>();
        newModel.transforms->insert(newModel.transforms->end(), newTs->begin(), newTs->end());
        newModel.upTransforms = new std::vector<Transform*>();
        newModel.upTransforms->insert(newModel.upTransforms->end(), upTs->begin(), upTs->end());

        // load vertices
        while (!modelFile.eof()) {
            engine::vertex vertex;
            modelFile >> vertex.x >> vertex.y >> vertex.z
                      >> vertex.nx >> vertex.ny >> vertex.nz
                      >> vertex.ti >> vertex.tj;
            vertexVec.push_back(vertex.x);
            vertexVec.push_back(vertex.y);
            vertexVec.push_back(vertex.z);
            normalVec.push_back(vertex.nx);
            normalVec.push_back(vertex.ny);
            normalVec.push_back(vertex.nz);
            textureVec.push_back(vertex.ti);
            textureVec.push_back(vertex.tj);
        }

        float *vertexArray = (float *)malloc(sizeof(float) * vertexVec.size());
        float *normalArray = (float *)malloc(sizeof(float) * normalVec.size());
        float *textureArray = (float *)malloc(sizeof(float) * textureVec.size());
        int i;
        for (i = 0; i < (vertexVec.size() / 3) - 1; i++) {
            vertexArray[3*i + 0] = vertexVec[3*i + 0];
            vertexArray[3*i + 1] = vertexVec[3*i + 1];
            vertexArray[3*i + 2] = vertexVec[3*i + 2];

            normalArray[3*i + 0] = normalVec[3*i + 0];
            normalArray[3*i + 1] = normalVec[3*i + 1];
            normalArray[3*i + 2] = normalVec[3*i + 2];

            textureArray[2*i + 0] = textureVec[2*i + 0];
            textureArray[2*i + 1] = textureVec[2*i + 1];
        }

        GLuint b[3];
        glGenBuffers(3, b);

        glBindBuffer(GL_ARRAY_BUFFER, b[0]);
        glBufferData(GL_ARRAY_BUFFER, i * 3 * sizeof(float), vertexArray, GL_STATIC_DRAW);

        glBindBuffer(GL_ARRAY_BUFFER, b[1]);
        glBufferData(GL_ARRAY_BUFFER, i * 3 * sizeof(float), normalArray, GL_STATIC_DRAW);

        glBindBuffer(GL_ARRAY_BUFFER, b[2]);
        glBufferData(GL_ARRAY_BUFFER, i * 2 * sizeof(float), textureArray, GL_STATIC_DRAW);

        glEnableClientState(GL_VERTEX_ARRAY);
        glEnableClientState(GL_NORMAL_ARRAY);
        glEnableClientState(GL_TEXTURE_COORD_ARRAY);

        string texture = g->getTexture();
        if (!texture.empty()) {
            if (textures->find(texture) != textures->end()) {
                newModel.texture = (*textures)[texture];
            } else {
                // load texture
                GLuint t = loadTexture(texture);
                newModel.texture = t;
                (*textures)[texture] = t;
            }
        } else {
            newModel.texture = 0;
        }

        newModel.vertexBuffer = b[0];
        newModel.normalBuffer = b[1];
        newModel.textureBuffer = b[2];
        newModel.numVertices = i/3;
        newModel.diffuse   = g->getDiffuse();
        newModel.specular  = g->getSpecular();
        newModel.emissive  = g->getEmissive();
        newModel.ambient   = g->getAmbient();
        newModel.typeDiff  = g->getTypeDiff();
        newModel.typeSpec  = g->getTypeSpec();
        newModel.typeEmis  = g->getTypeEmis();
        newModel.typeAmbi  = g->getTypeAmbi();
        newModel.typeShine = g->getTypeShine();

		newModel.lights = g->getLight();

        loadedModels->push_back(newModel);
    }

    // load models in subgroups
    for (auto subGroup : *g->getSubGroups()) {
        std::vector<engine::figure> *subModels = loadModels(subGroup, Ts, textures);
        loadedModels->insert(loadedModels->end(), subModels->begin(), subModels->end()); 
    }

    return loadedModels;
}
