#pragma once
#include "Camera.h"
#include "../terrain/Terrain.h"

class EntityHandler {
public:
	EntityHandler();
	~EntityHandler();

	void tick(Camera* cam);
	void render(Camera* cam);

private:
	Terrain* _terrain;
};