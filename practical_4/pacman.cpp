#include <SFML/Graphics.hpp>
#include "pacman.h"
#include "player.h"
#include "ghost.h"
#include "entity.h"

using namespace std;
using namespace sf;

EntityManager em;

MenuScene::MenuScene()
{
}

void MenuScene::update(double dt)
{
}

void MenuScene::render()
{
}

void MenuScene::load()
{
}

void GameScene::respawn()
{
}

void GameScene::update(double dt)
{
	em.update(dt);
}

void GameScene::render(RenderWindow &window)
{
	em.render(window);
}

void GameScene::load()
{
	Vector2f pos(400, 300);
	auto player = make_shared<Player>();
	player->setPosition(pos);

	em.list.push_back(player);

	for (int i = 0; i < 4; i++) {
		auto ghost = make_shared<Ghost>();
		ghost->setPosition(Vector2f(i * 200.0f, i * 200.0f));
		em.list.push_back(ghost);
	}
}
