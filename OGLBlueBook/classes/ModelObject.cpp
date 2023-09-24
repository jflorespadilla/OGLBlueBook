#include "ModelObject.h"

ModelObject::ModelObject(const char* file, ModelType modelType) {
	// Look at the model type
	// Load up the file using the appropriate loader
}

ModelObject::~ModelObject() {
	// Set flat for no loaded file
	// Prompt user to provide a file string
}

void ModelObject::loadOBJModel(const std::fstream& ModelFile) {
	// Parce file
	// Load data
}

void ModelObject::loadSTLModel(const std::fstream& ModelFile) {
	// Parce file
	// Load data
}

void ModelObject::loadVRML(const std::fstream& ModelFile) {
	// Parce file
	// Load data
}

void ModelObject::loadModel(const char* file, ModelType modelType) {

	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(file, aiComponent_TEXCOORDS | aiComponent_COLORS);

	if (nullptr == scene) {
		std::cerr << importer.GetErrorString();
		return;
	}
}