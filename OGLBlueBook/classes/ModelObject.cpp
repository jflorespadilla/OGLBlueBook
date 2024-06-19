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
	// Processing the scene will come, but first I should implement loggin.
	// It requires the use of insterfaces. So we'll be learning something new-ish

	return true;
}