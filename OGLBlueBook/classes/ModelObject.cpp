#include "ModelObject.h"

ModelObject::~ModelObject() {
	// Set flat for no loaded file
	// Prompt user to provide a file string
}

ModelObject::ModelObject(const char* file, ModelType modelType) {
	// Look at the model type
	// Load up the file using the appropriate loader
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
	/*std::fstream ModelFile(file, std::fstream::in);
	
	if (!ModelFile.is_open()) {
		return;
	}*/

	// Hopefully this glorified switch statement saves me some work later...

	/*switch (modelType) {
	case ModelType::OBJ:
		loadOBJModel(ModelFile);
		break;
	case ModelType::STL:
		loadSTLModel(ModelFile);
		break;
	case ModelType::VRML:
		loadVRML(ModelFile);
		break;
	}
	ModelFile.close();*/
}