#include "EntityHandler.h"

EntityHandler::EntityHandler() {
	_terrain = new Terrain();
}

EntityHandler::~EntityHandler() {
	delete _terrain;
}

void EntityHandler::tick(Camera* cam) {
	_terrain->tick(cam);
}

void EntityHandler::render(Camera* cam) {
	_terrain->render(cam);
}