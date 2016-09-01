#include "ShaderHandler.h"
#include <GL\glew.h>
#include <string>

Shader* ShaderHandler::_terrainShader;
Shader* ShaderHandler::_planetShader;

void ShaderHandler::init() {
	_terrainShader = new Shader("shaders/terrain.vert", "shaders/terrain.frag");
	_planetShader = new Shader("shaders/terrain.vert", "shaders/terrain.frag");

	/*_terrainShader->comeHere();
	glActiveTexture(GL_TEXTURE0);
	_terrainShader->uploadTexture(0, std::string("itemTex"));
	_terrainShader->pissOff();*/
}

void ShaderHandler::cleanUp() {
	delete _terrainShader;	_terrainShader = nullptr;
	delete _planetShader; _planetShader = nullptr;
}