#pragma once
// Going to replicate a similar class found in the sb7 source
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>

#include <assimp/Importer.hpp> 

// Add model type formats as necessary
enum ModelType {STL, OBJ, VRML};

class ModelObject
{
	public:
		ModelObject();
		ModelObject(const char* file, ModelType modelType);
		ModelObject(const ModelObject &modelObject);
		~ModelObject();
		void loadSTLModel(const std::fstream& ModelFile);
		void loadOBJModel(const std::fstream& ModelFile);
		void loadVRML(const std::fstream& ModelFile);
		void loadModel(const char* file, ModelType modelType);

	private:
		// u,v coords?
		// positional vectors?
};

