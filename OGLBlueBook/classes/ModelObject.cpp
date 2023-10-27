#include "ModelObject.h"

ModelObject::ModelObject() {
	// Intitalize values here
}

ModelObject::~ModelObject() {
	// Clean up if necessary
}

bool ModelObject::Import(std::string& fileName) {
	const aiScene* scene = importer.ReadFile(fileName, aiProcess_CalcTangentSpace |
		aiProcess_Triangulate |
		aiProcess_JoinIdenticalVertices |
		aiProcess_SortByPType);

	if (scene == nullptr) {
		std::cerr << importer.GetErrorString();
		return false;
	}
	// Add some logic here to actually save values and process the scene

	// Need to further study what it takes to produce a mesh

	return true;
}