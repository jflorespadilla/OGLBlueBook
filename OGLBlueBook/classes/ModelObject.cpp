#include "ModelObject.h"

ModelObject::ModelObject() {
	// Intitalize values here
}

ModelObject::~ModelObject() {
	// Clean up if necessary
}

void ModelObject::Import(std::string fileName) {
	const aiScene* scene = importer.ReadFile(fileName, aiProcess_CalcTangentSpace |
		aiProcess_Triangulate |
		aiProcess_JoinIdenticalVertices |
		aiProcess_SortByPType);
}