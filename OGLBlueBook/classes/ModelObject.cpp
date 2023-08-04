#include "ModelObject.h"

ModelObject::~ModelObject() {
	// Set flat for no loaded file
	// Prompt user to provide a file string
}

ModelObject::ModelObject(const char* file, ModelType modelType) {
	// Look at the model type
	// Load up the file using the appropriate loader
}

void ModelObject::loadModel(const char* file, ModelType modelType) {
	std::fstream ModelFile(file, std::fstream::in);
	
	if (!ModelFile.is_open()) {
		return;
	}

	// Hopefully this glorified switch statement saves me some work later...

	switch (modelType) {
	case ModelType::OBJ:
		// Call model specific load function
		break;
	case ModelType::STL:
		// Call model specific load function
		break;
	case ModelType::VRML:
		// Call model specific load function
		break;
	}
}