#include <SFML/Graphics.hpp>

#include "Engine/Constants.h"
#include "Engine/World.h"
#include "Engine/ViewController.h"
#include "Engine/PickableSpawner.h"
#include "Engine/Pickable.h"
#include "Engine/ParticleSystem.h"
#include "Enemies/EnemiesManager.h"
#include "Enemies/Enemy.h"
#include "UI/HealthBar.h"
#include "Textures.h"
#include "Weapon/RangeWeapon.h"
#include "Weapon/MeleeWeapon.h"
#include "Bullet.h"

int main() {
	srand(time(NULL));

	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Toffi Adventure");

	auto texture_holder = TextureHolder::instance();
	texture_holder->setTextures();
	auto player_texture = texture_holder->player_textures();

	auto pickable_spawner = PickableSpawner::instance();
	pickable_spawner->addPickableTexture(PickableType::HEAL, texture_holder->heal_texture());
	pickable_spawner->addPickableTexture(PickableType::BULLET_WAVE, texture_holder->bullet_texture());

	auto particle_system = ParticleSystem::instance();

	auto player = std::make_shared<Player>(player_texture, sf::Vector2f(PLAYER_START_X, PLAYER_START_Y), PLAYER_START_HP);
	player->initWeapon(WeaponType::RANGE, 1.0, texture_holder->bullet_texture());

	pickable_spawner->setPlayer(player);

	auto enemies_manager = std::make_unique<EnemiesManager>();
	enemies_manager->setPlayer(player);
	enemies_manager->setBulletTexture(texture_holder->bullet_texture());
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
		pickable_spawner->Update();
		particle_system->Update(time / 1000);
		player->Update(time);
		player->attackEnemies(time, characters);
		enemies_manager->Update(time);
		view_controller.Update(time, window);

		window.clear(sf::Color::White);

		window.draw(world->getBackgroundSprite());
		for (int i = 0; i < world->getBorderVecSize(); i++) {
			window.draw(world->getBorderSprites()[i]);
		}

		for (auto pickable : pickable_spawner->getPickables()) {
			window.draw(pickable->getSprite());
		}

		particle_system->drawParticles(window);
		enemies_manager->drawBullets(window);

		if (player->getWeapon()->getWeaponType() == WeaponType::RANGE) {
			auto weapon = std::dynamic_pointer_cast<RangeWeapon>(player->getWeapon());
			if (weapon) {
				auto bullets = weapon->getBullets();
				for (auto b : bullets) {
					window.draw(b->getSprite());
				}
			}
		}
		else {
			auto weapon = std::dynamic_pointer_cast<MeleeWeapon>(player->getWeapon());
			window.draw(weapon->getWeapon());
		}

		window.draw(player->getSprite());
		for (auto e : enemies_manager->getEnemies()) {
			window.draw(e->getSprite());
		}

		player->getHealthBar()->Draw(window);
		
		window.display();
	}

	delete texture_holder;
	delete pickable_spawner;
	delete particle_system;
	delete world;
	return 0;
}
