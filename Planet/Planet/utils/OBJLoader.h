#pragma once
#include <glm\glm.hpp>
#include <string>
#include <vector>

class OBJLoader
{
public:
	OBJLoader();
	~OBJLoader() = default;

	bool loadFromFile(const std::string& path, std::vector<glm::vec3>& outVerts, std::vector<unsigned>& outIndices);
};

