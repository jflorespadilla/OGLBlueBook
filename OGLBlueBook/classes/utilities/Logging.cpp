#include "Logging.h"

Logging::Logging() {
	Assimp::DefaultLogger::create();
}

Logging::~Logging() {
	Assimp::DefaultLogger::kill();
}

void Logging::getInfo() {
	Assimp::DefaultLogger::get()->info("Log output:\n\n");
}