#ifndef GROUP
#define GOUP

#include <vector>
#include <string>
#include "transform.h"
#include "colour.h"

using namespace std;

class Group {
    private:
        Group *up;
        std::vector<Transform *> *transforms;
        std::vector<string> *modelPaths;
        std::vector<Group *> *subGroups;
        string texture;
        Colour diffuse;
        Colour specular;
        Colour emissive;
        Colour ambient;
        int typeDiff;
        int typeSpec;
        int typeEmis;
        int typeAmbi;
        float typeShine;

    public:
        Group();
        std::vector<Transform*> *getTransforms();
        std::vector<string> *getModels();
        std::vector<Group*> *getSubGroups();
        string getTexture();
        Colour getDiffuse();
        Colour getSpecular();
        Colour getEmissive();
        Colour getAmbient();
        int getTypeDiff();
        int getTypeSpec();
        int getTypeEmis();
        int getTypeAmbi();
        float getTypeShine();
        void setUp(Group *g);
        void addTransform(Transform *t);
        void addModel(string m, string t, Colour diffuse, Colour specular, Colour emissive, Colour ambient, 
                                    int typeDiff, int typeSpec, int typeEmis, int typeAmbi, float typeShine);
        void addSubGroup(Group *g);
};

#endif//GROUP
