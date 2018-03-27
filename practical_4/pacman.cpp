#include "pacman.h"
#include "entity.h"
#include "player.h"
#include "ghost.h"

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

	shared_ptr<Entity> player = make_shared<Player>();
	_ents.list.push_back(player);
	player->setPosition({ 30.0f, 30.0f });

	for (int i = 0; i < 4; i++) {
		shared_ptr<Entity> ghost = make_shared<Ghost>();
		_ents.list.push_back(ghost);
		ghost->setPosition({ 50.0f * i, 50.0f * i });
	}

}