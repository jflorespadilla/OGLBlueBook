#pragma once
// Going to replicate a similar class found in the sb7 source
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>

// Add model type formats as necessary
enum ModelType {STL, OBJ, VRML};

class ModelObject
{
	ModelObject();
	ModelObject(const char* file, ModelType modelType);
	ModelObject(const ModelObject &modelObject);
	~ModelObject();
	void loadModel(const char* file, ModelType modelType);
	void loadSTLModel(const std::fstream& ModelFile);
	void loadOBJModel(const std::fstream& ModelFile);
	void loadVRML(const std::fstream& ModelFile);
};

