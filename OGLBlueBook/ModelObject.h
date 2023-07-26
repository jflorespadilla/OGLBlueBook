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
	ModelObject(char* file, ModelType modelType);
	ModelObject(const ModelObject &modelObject);
	~ModelObject();
	// Load object via file
	// Define an enum for a different series of file types.
};

