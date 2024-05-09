#include <SFML/Graphics.hpp>

#include "include/Engine/Constants.h"
#include "include/Engine/World.h"
#include "include/Engine/ViewController.h"
#include "include/Enemies/EnemiesManager.h"
#include "include/Enemies/Enemy.h"
#include "include/UI/HealthBar.h"
#include "include/Textures.h"
#include "include/Weapon/RangeWeapon.h"
#include "include/Bullet.h"

int main() {
	srand(time(NULL));

	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Toffi Adventure");

	auto texture_holder = TextureHolder::instance();
	texture_holder->setTextures();

	Player* player = new Player(texture_holder->player_textures(), sf::Vector2f(PLAYER_START_X, PLAYER_START_Y), PLAYER_START_HP);
	player->initWeapon(WeaponType::RANGE, 1.0, texture_holder->bullet_texture());

	EnemiesManager* enemies_manager = new EnemiesManager();
	enemies_manager->setPlayer(player);
	enemies_manager->addTexture(texture_holder->flying_eye_texture());

	World* world = World::getWorld();
	world->initWorld(texture_holder->lvl1_background_texture(), texture_holder->lvl1_border_texture());

	ViewController view_controller(player);

	sf::Clock clock;

	while (window.isOpen()) {
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time /= 300;

		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}

		auto characters = enemies_manager->getCharacters();
		player->Update(time);
		player->attackEnemies(time, characters);
		enemies_manager->Update(time);
		view_controller.Update(time, window);

		window.clear(sf::Color::White);

		window.draw(world->getBackgroundSprite());
		for (int i = 0; i < world->getBorderVecSize(); i++) {
			window.draw(world->getBorderSprites()[i]);
		}

		if (player->getWeapon()->getWeaponType() == WeaponType::RANGE) {
			auto weapon = dynamic_cast<RangeWeapon*>(player->getWeapon());
			if (weapon) {
				auto bullets = weapon->getBullets();
				for (auto b : bullets) {
					window.draw(b->getSprite());
				}
			}
		}

		window.draw(player->getSprite());
		for (auto e : enemies_manager->getEnemies()) {
			window.draw(e->getSprite());
		}

		player->getHealthBar()->Draw(window);
		
		window.display();
	}

	delete player;
	delete enemies_manager;
	delete texture_holder;
	return 0;
}
