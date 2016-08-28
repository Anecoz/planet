#include "OBJLoader.h"
#include <iostream>

OBJLoader::OBJLoader()
{
}

bool OBJLoader::loadFromFile(const std::string& path, std::vector<glm::vec3>& outVerts, std::vector<unsigned>& outIndices) {
	FILE * file = fopen(path.c_str(), "r");
	if (file == NULL) {
		std::cerr << "Impossible to open the file " << path << "!" << std::endl;
		return false;
	}

	std::vector<glm::vec3> tmpVertices;
	std::vector<unsigned> vertexIndices;

	while (1) {

		char lineHeader[128];
		// read the first word of the line
		int res = fscanf(file, "%s", lineHeader);
		if (res == EOF)
			break; // EOF = End Of File. Quit the loop.

		if (strcmp(lineHeader, "v") == 0) {
			glm::vec3 vertex;
			fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
			tmpVertices.push_back(vertex);
		}
		else if (strcmp(lineHeader, "vt") == 0) {
		}
		else if (strcmp(lineHeader, "vn") == 0) {
		}
		else if (strcmp(lineHeader, "f") == 0) {
			std::string vertex1, vertex2, vertex3;
			unsigned int vertexIndex[3], normalIndex[3];
			int matches = fscanf(file, "%d//%d %d//%d %d//%d\n", &vertexIndex[0], &normalIndex[0], &vertexIndex[1], &normalIndex[1], &vertexIndex[2], &normalIndex[2]);
			if (matches != 6) {
				printf("File can't be read by our simple parser : ( Try exporting with other options\n");
				return false;
			}
			vertexIndices.push_back(vertexIndex[0]);
			vertexIndices.push_back(vertexIndex[1]);
			vertexIndices.push_back(vertexIndex[2]);
		}
	}
	
	outVerts = tmpVertices;
	outIndices = vertexIndices;
	return true;
}