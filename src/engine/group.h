#include "transform.h"

using namespace std;

class Group {

private:
    Group *up;
    std::vector<Transform *> transforms;
    std::vector<string> modelPaths;
    std::vector<Group *> subGroups;

public:
	std::vector<Transform> getTransforms();
	std::vector<string> getModels();
	std::vector<Group> getSubGroups();
    void setUp(Group *g);
    void addTranform(Transform *t);
    void addModel(string m);
    void addSubGroup(Group *g);
};
