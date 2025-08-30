#include <SFML/Graphics.hpp>

#include "Constants.h"
#include "Engine/World.h"
#include "Controllers/ViewController.h"
#include "Pickables/PickableSpawner.h"
#include "Engine/Base/Pickable.h"
#include "Engine/Particles/ParticleSystem.h"
#include "Enemies/EnemiesManager.h"
#include "Enemies/Enemy.h"
#include "Engine/UI/HealthBar.h"
#include "Textures/Textures.h"
#include "Weapon/RangeWeapon.h"
#include "Weapon/MeleeWeapon.h"
#include "Weapon/BulletWaveWeapon.h"
#include "Weapon/Bullet.h"

int main() {
	srand(time(NULL));

    sf::RenderWindow window(sf::VideoMode({ WINDOW_WIDTH, WINDOW_HEIGHT }), "Toffi Adventure");

	auto texture_holder = TextureHolder::instance();
	texture_holder->setTextures();
	auto player_texture = texture_holder->player_textures();

	auto pickable_spawner = PickableSpawner::instance();
	pickable_spawner->addPickableTexture(PickableType::HEAL, texture_holder->heal_texture());
	pickable_spawner->addPickableTexture(PickableType::BULLET_WAVE, texture_holder->bullet_texture());

	auto particle_system = game_engine::ParticleSystem::instance();

	auto player = std::make_shared<Player>(player_texture, sf::Vector2f(PLAYER_START_X, PLAYER_START_Y), PLAYER_START_HP);
	player->initWeapon(WeaponType::MELEE, 1.0, texture_holder->sword_texture());
    player->initWeapon(WeaponType::BULLET_WAVE, 1.0, {});

	pickable_spawner->setPlayer(player);

	auto enemies_manager = std::make_unique<EnemiesManager>();
	enemies_manager->setPlayer(player);
	enemies_manager->setBulletTexture(texture_holder->bullet_texture());
	enemies_manager->addTexture(texture_holder->flying_eye_texture());

    game_engine::World* world = game_engine::World::getWorld();
	world->initWorld(texture_holder->lvl1_background_texture(), texture_holder->lvl1_border_texture());

	ViewController view_controller(player);

	sf::Clock clock;

	while (window.isOpen()) {
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time /= 300;

        while (const std::optional event = window.pollEvent()) {
        if (event->is<sf::Event::Closed>())
            window.close();
        }

		auto characters = enemies_manager->getCharacters();
		pickable_spawner->Update();
		particle_system->Update(time / 1000);
		player->Update(time);
		player->attackEnemies(time, characters);
		enemies_manager->Update(time);
		view_controller.Update(time, window);

		window.clear(sf::Color::White);

		window.draw(*world->getBackgroundSprite().get());
		for (int i = 0; i < world->getBorderVecSize(); i++) {
			window.draw(world->getBorderSprites()[i]);
		}

		particle_system->drawParticles(window);

        game_engine::Drawable::drawAllDrawableObjects(window);

		player->getHealthBar()->Draw(window);
		
		window.display();
	}

	delete texture_holder;
	delete pickable_spawner;
	delete particle_system;
	delete world;
	return 0;
}
