#pragma once

#include "Shader.h"

class ShaderHandler {
public:
	static Shader* _terrainShader;
	static Shader* _planetShader;

	static void init();

	static void cleanUp();
};
