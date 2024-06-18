#include "ModelObject.h"

ModelObject::ModelObject() {
	// Intitalize values here
}

ModelObject::~ModelObject() {
	// Clean up if necessary
}

bool ModelObject::Import(std::string& fileName) {
	// Now that I read the assimp files, perhaps I don't whant an importer as a
	// private data variable. There's no reason to keep it once import is ran.
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(fileName, aiProcess_CalcTangentSpace |
		aiProcess_Triangulate |
		aiProcess_JoinIdenticalVertices |
		aiProcess_SortByPType);

	if (scene == nullptr) {
		std::cerr << importer.GetErrorString();
		return false;
	}
	// I'll need to process the scene here, according to the docs.
	// I that will be my next reading assignment.


	return true;
}