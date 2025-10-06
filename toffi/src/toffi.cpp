#include "Constants.h"

#include "Engine/World.h"
#include "Engine/TimersHolder.hpp"
#include "Engine/GameStateMachine.h"
#include "Engine/Base/Pickable.h"
#include "Engine/Particles/ParticleSystem.h"
#include "Engine/UI/UIComponents/HealthBar.h"
#include "Engine/UI/UIComponents/DamageIndicator.h"
#include "Engine/UI/GameScreen/GameScreenManager.h"

#include "GameScreens/GameOverScreen.h"

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

    game_engine::primitives::Clock clock;

    const auto stateMachine = game_engine::GameStateMachine::instance();
    stateMachine->fireGamePaused.connect([]() {
        game_engine::TimersHolder::pauseAllTimers();
    });
    stateMachine->fireGameResumed.connect([clock]() mutable {
        game_engine::TimersHolder::resumeAllTimers();
        clock.reset();
    });

    const auto gameScreenManager = game_engine::ui::GameScreenManager::instance();
    gameScreenManager->addGameScreen(game_engine::GameState::GAME_OVER, std::make_unique<GameOverScreen>());

    game_engine::primitives::RenderWindow window({ WINDOW_WIDTH, WINDOW_HEIGHT }, "Toffi Adventure");

    auto texture_holder = TextureHolder::instance();
    texture_holder->setTextures();
    auto player_texture = texture_holder->player_textures();

    game_engine::World* world = game_engine::World::getWorld();
    world->initWorld(texture_holder->lvl1_background_texture(), texture_holder->lvl1_border_texture());

    auto pickable_spawner = PickableSpawner::instance();
    pickable_spawner->addPickableTexture(PickableType::HEAL, texture_holder->heal_texture());
    pickable_spawner->addPickableTexture(PickableType::BULLET_WAVE, texture_holder->bullet_texture());
    pickable_spawner->addPickableTexture(PickableType::CURRENCY, texture_holder->coin_texture());

    auto particle_system = game_engine::ParticleSystem::instance();

    auto player = std::make_shared<Player>(player_texture, game_engine::primitives::Vector2f(PLAYER_START_X, PLAYER_START_Y), PLAYER_START_HP);
    player->initWeapon(WeaponType::RANGE, 1.0, texture_holder->bullet_texture());
    player->initWeapon(WeaponType::MELEE, 1.0, texture_holder->sword_texture());
    player->initWeapon(WeaponType::BULLET_WAVE, 1.0, {});

    pickable_spawner->setPlayer(player);

    auto enemies_manager = std::make_unique<EnemiesManager>();
    enemies_manager->setPlayer(player);
    enemies_manager->setBulletTexture(texture_holder->bullet_texture());
    enemies_manager->addTexture(texture_holder->flying_eye_texture());

    auto view_controller = ViewController::instance();
    view_controller->setPlayer(player);

    stateMachine->setState(game_engine::GameState::RUNNING); // TODO: this is a temporary solution. Remove after main menu impl

    while (window.isOpen()) {
        float time = clock.getElapsedTime();
        time /= 300;
        clock.restart();

        game_engine::TimersHolder::deleteExpiredTimers();

        const auto event = window.pollEvent();
        const auto key_event = event && event->type() == game_engine::primitives::Event::Type::Keyboard ?
            event->as<game_engine::primitives::KeyEvent>() : nullptr;
        if (event) {
            if (event->type() == game_engine::primitives::Event::Type::Close) {
                window.close();
            }
        }
        if (key_event && key_event->action() == game_engine::primitives::KeyEvent::Action::Press) {
            if (key_event->key() == game_engine::primitives::KeyEvent::Key::Escape) {
                if (stateMachine->currentState() == game_engine::GameState::RUNNING) {
                    stateMachine->setState(game_engine::GameState::PAUSED);
                }
                else if (stateMachine->currentState() == game_engine::GameState::PAUSED) {
                    stateMachine->setState(game_engine::GameState::RUNNING);
                }
            }
            else if (key_event->key() == game_engine::primitives::KeyEvent::Key::R) {
                stateMachine->setState(game_engine::GameState::RUNNING);
            }
        }

        auto characters = enemies_manager->getCharacters();

        if (stateMachine->currentState() == game_engine::GameState::RUNNING) {
            pickable_spawner->Update(time);
            particle_system->Update(time / 1000);
            player->Update(time);
            player->attackEnemies(time, characters);
            enemies_manager->Update(time);
            view_controller->Update(time, window);

            game_engine::ui::DamageIndicatorsHolder::Update(time);

            if (player->getHP() <= 0) {
                stateMachine->setState(game_engine::GameState::GAME_OVER);
            }
        }

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
