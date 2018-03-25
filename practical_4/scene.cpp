#include <SFML/Graphics.hpp>
#include "scene.h"
#include "system_renderer.h"

using namespace sf;

void Scene::update(double dt)
{
}

void Scene::render(RenderWindow &window)
{
}

std::vector<std::shared_ptr<Entity>>& Scene::getEnts()
{
	return _ents.list;
}
