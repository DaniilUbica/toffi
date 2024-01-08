﻿#include <SFML/Graphics.hpp>

#include "include/Engine/Constants.h"
#include "include/Engine/World.h"
#include "include/Engine/ViewController.h"
#include "include/Enemies/EnemiesManager.h"
#include "include/Enemies/Enemy.h"
#include "include/UI/HealthBar.h"
#include "include/Player.h"
#include "include/Textures.h"
#include "include/Weapon.h"
#include "include/Bullet.h"

int main() {
	srand(time(NULL));

	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Toffi Adventure");

	textures::setTextures();

	Player* player = new Player(textures::player_textures, sf::Vector2f(PLAYER_START_X, PLAYER_START_Y), PLAYER_START_HP);
	player->initWeapon(textures::bullet_texture, 1.0);

	EnemiesManager* enemies_manager = new EnemiesManager();
	enemies_manager->setPlayer(player);
	enemies_manager->addTexture(textures::flying_eye_texture);

	World* world = World::getWorld();
	world->initWorld(textures::lvl1_border_texture);

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

		auto bullets = player->getWeapon()->getBullets();
		for (auto b : bullets) {
			window.draw(b->getSprite());
		}

		for (int i = 0; i < world->getBorderVecSize(); i++) {
			window.draw(world->getBorderSprites()[i]);
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
	return 0;
}