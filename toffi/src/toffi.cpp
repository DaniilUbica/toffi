#include <SFML/Graphics.hpp>

#include "Constants.h"

#include "Engine/World.h"
#include "Engine/Base/Pickable.h"
#include "Engine/Particles/ParticleSystem.h"
#include "Engine/UI/HealthBar.h"

#include "Primitives/Clock.hpp"

#include "Controllers/ViewController.h"
#include "Controllers/PlayerController.h"

#include "Pickables/PickableSpawner.h"

#include "Enemies/EnemiesManager.h"
#include "Enemies/Enemy.h"

#include "Textures/Textures.h"

#include "Weapon/RangeWeapon.h"
#include "Weapon/MeleeWeapon.h"
#include "Weapon/BulletWaveWeapon.h"
#include "Weapon/Bullet.h"

int main() {
	srand(time(NULL));

    game_engine::primitives::RenderWindow window({ WINDOW_WIDTH, WINDOW_HEIGHT }, "Toffi Adventure");

	auto texture_holder = TextureHolder::instance();
	texture_holder->setTextures();
	auto player_texture = texture_holder->player_textures();

    game_engine::World* world = game_engine::World::getWorld();
    world->initWorld(texture_holder->lvl1_background_texture(), texture_holder->lvl1_border_texture());

	auto pickable_spawner = PickableSpawner::instance();
	pickable_spawner->addPickableTexture(PickableType::HEAL, texture_holder->heal_texture());
	pickable_spawner->addPickableTexture(PickableType::BULLET_WAVE, texture_holder->bullet_texture());

	auto particle_system = game_engine::ParticleSystem::instance();

	auto player = std::make_shared<Player>(player_texture, game_engine::primitives::Vector2f(PLAYER_START_X, PLAYER_START_Y), PLAYER_START_HP);
	player->initWeapon(WeaponType::MELEE, 1.0, texture_holder->sword_texture());
    player->initWeapon(WeaponType::BULLET_WAVE, 1.0, {});

	pickable_spawner->setPlayer(player);

	auto enemies_manager = std::make_unique<EnemiesManager>();
	enemies_manager->setPlayer(player);
	enemies_manager->setBulletTexture(texture_holder->bullet_texture());
	enemies_manager->addTexture(texture_holder->flying_eye_texture());

	ViewController view_controller(player);

	game_engine::primitives::Clock clock;

	while (window.isOpen()) {
        float time = clock.getElapsedTime();
        clock.restart();
        time /= 300;

        const auto event = window.pollEvent();
        const auto key_event = event && event->type() == game_engine::primitives::Event::Type::Keyboard ?
            event->as<game_engine::primitives::KeyEvent>() : nullptr;
        if (event) {
            if (event->type() == game_engine::primitives::Event::Type::Close) {
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

		window.clear(game_engine::primitives::colors::White);

        game_engine::DrawableObject::drawAllDrawableObjects(window);
		particle_system->drawParticles(window);
		
		window.display();
	}

	delete texture_holder;
	delete pickable_spawner;
	delete particle_system;
	delete world;
	return 0;
}
