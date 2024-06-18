#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
// Need to learn how to use this library properly
#include <assimp/Importer.hpp> 
#include <assimp/scene.h>
#include <assimp/postprocess.h>

// No clue if I'll still need this. Gonna keep in comment for now.
// enum ModelType {STL, OBJ, VRML};

class ModelObject
{
	public:
		ModelObject();
		~ModelObject();
		bool Import(std::string& fileName);

	private:
};

