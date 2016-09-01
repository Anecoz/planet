#pragma once
#include "../graphics/VertexArrayObject.h"
#include "../logic/Camera.h"
#include <glm\glm.hpp>

class Terrain {
public:
	Terrain();
	~Terrain();

	void tick(Camera* cam);
	void render(Camera* cam);

private:
	VertexArrayObject* _mesh;
	glm::vec3 _pos;
};