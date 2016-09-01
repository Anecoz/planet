#include "Terrain.h"
#include "../utils/OBJLoader.h"
#include "../graphics/ShaderHandler.h"
#include <glm\gtx\transform.hpp>
#include <iostream>

Terrain::Terrain() {
	VertVec verts;
	IndVec indices;
	OBJLoader loader;
	if (loader.loadFromFile("grid.obj", verts, indices)) {
		std::cout << "Loaded terrain obj!" << std::endl;
	}
	else {
		std::cout << "Could not load terrain obj" << std::endl;
	}
	_mesh = new VertexArrayObject(verts, indices);

	_pos = glm::vec3(0, 0, 0);
}

Terrain::~Terrain() {
	delete _mesh;
}

void Terrain::tick(Camera* cam) {
	// UPDATE POSITION TO FOLLOW CAMERA
	glm::vec3 camPos = cam->getPos();
	_pos.x = camPos.x;
	_pos.y = 0;
	_pos.z = camPos.z;
	//std::cout << "Terrain now at: " << _pos.x << ", " << _pos.y << ", " << _pos.z << std::endl;
}

void Terrain::render(Camera* cam) {
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	ShaderHandler::_terrainShader->comeHere();
	ShaderHandler::_terrainShader->uploadMatrix(cam->getProj(), "projMatrix");
	ShaderHandler::_terrainShader->uploadMatrix(cam->getCameraMatrix(), "camMatrix");
	ShaderHandler::_terrainShader->uploadMatrix(glm::translate(_pos), "modelMatrix");

	_mesh->draw();
	
	ShaderHandler::_terrainShader->pissOff();
}