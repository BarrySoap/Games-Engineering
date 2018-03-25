#include <SFML/Graphics.hpp>
#include "pacman.h"
#include "player.h"
#include "ghost.h"
#include "entity.h"
#include "system_renderer.h"
#include <iostream>

using namespace std;
using namespace sf;

EntityManager em;
Font font;

MenuScene::MenuScene()
{
}

void MenuScene::load()
{
	if (!font.loadFromFile("res/fonts/RobotoMono-Regular.ttf")) {
		cout << "Cannot load font!" << endl;
	}

	if (Keyboard::isKeyPressed(Keyboard::Space)) {
		activeScene = gameScene;
	}

	text.setString("Test");
	text.setFont(font);
}

void MenuScene::update(double dt)
{
	if (Keyboard::isKeyPressed(Keyboard::Space)) {
		activeScene = gameScene;
	}

	Scene::update(dt);
	_ents.update(dt);
}

void MenuScene::render(RenderWindow &window)
{
	Scene::render(window);
	_ents.render(window);
	Renderer::queue(&text);
}

void GameScene::respawn()
{
}

void GameScene::update(double dt)
{
	if (Keyboard::isKeyPressed(Keyboard::Tab)) {
		activeScene = menuScene;
	}
	Scene::update(dt);
	_ents.update(dt);
}

void GameScene::render(RenderWindow &window)
{
	Scene::render(window);
	_ents.render(window);
}

void GameScene::load()
{
	Vector2f pos(400, 300);
	auto player = make_shared<Player>();
	player->setPosition(pos);

	_ents.list.push_back(player);

	for (int i = 0; i < 4; i++) {
		auto ghost = make_shared<Ghost>();
		ghost->setPosition(Vector2f(i * 200.0f, i * 200.0f));
		_ents.list.push_back(ghost);
	}
}
