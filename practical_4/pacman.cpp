#include "pacman.h"
#include "entity.h"
#include "player.h"
#include "ghost.h"
#include "ecm.h"
#include "cmp_sprite.h"
#include "cmp_actor_movement.h"
#include "cmp_player_movement.h"

#define GHOST_COUNT 4

using namespace std;
using namespace sf;

void MenuScene::update(float dt) {
	if (Keyboard::isKeyPressed(Keyboard::Space)) {
		activeScene = gameScene;
	}
	Scene::update(dt);
}

void MenuScene::render() {
	Scene::render();
}

void MenuScene::load() {
	Font font;
	font.loadFromFile("res/fonts/RobotoMono-Regular.ttf");
	text.setFont(font);
	text.setCharacterSize(24);
	text.setString("Almost Pacman");
	text.setPosition(gameWidth / 2, gameHeight / 2);
}

void GameScene::update(float dt) {
	if (Keyboard::isKeyPressed(Keyboard::Tab)) {
		activeScene = menuScene;
	}
	Scene::update(dt);
}

void GameScene::render() {
	Scene::render();
}

void GameScene::respawn() {}

void GameScene::load() {
	auto p1 = make_shared<Entity>();

	auto s = p1->addComponent<ShapeComponent>();
	s->setShape<sf::CircleShape>(12.0f);
	s->getShape().setFillColor(Color::Yellow);
	s->getShape().setOrigin({ 12.0f, 12.0f });

	p1->addComponent<PlayerMovementComponent>();

	_ents.list.push_back(p1);

	const sf::Color ghost_cols[]{ {208, 62, 25},		// Blinky
								  {219, 133, 28},		// Clyde
								  {70, 191, 238},		// Inky
								  {234, 130, 229} };	// Pinky

	for (int i = 0; i < GHOST_COUNT; ++i) {
		auto ghost = make_shared<Entity>();
		auto s = ghost->addComponent<ShapeComponent>();
		s->setShape<sf::CircleShape>(12.0f);
		s->getShape().setFillColor(ghost_cols[i % 4]);
		s->getShape().setOrigin({ 12.0f, 12.0f });

		ghost->setPosition({ 20.0f, 20.0f });
		_ents.list.push_back(ghost);
	}
}