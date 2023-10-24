#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
// Need to learn how to use this library properly
#include <assimp/Importer.hpp> 

// Add model type formats as necessary
enum ModelType {STL, OBJ, VRML};

class ModelObject
{
	public:
		ModelObject();
		~ModelObject();

	private:
};

