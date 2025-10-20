#include "GameManager.h"

#include "Engine/World.h"
#include "Engine/TimersHolder.hpp"
#include "Engine/GameStateMachine.h"
#include "Engine/Base/Pickable.h"
#include "Engine/Particles/ParticleSystem.h"
#include "Engine/UI/UIComponents/HealthBar.h"
#include "Engine/UI/UIComponents/DamageIndicator.h"
#include "Engine/UI/GameScreen/GameScreenManager.h"

#include "Constants.h"

#include "GameScreens/GameOverScreen.h"
#include "GameScreens/GameInterfaceScreen.h"

#include "Controllers/ViewController.h"
#include "Controllers/GamePointsController.h"
#include "Controllers/CashValueController.h"

#include "Pickables/PickableSpawner.h"

#include "Enemies/EnemiesManager.h"
#include "Enemies/Enemy.h"

#include "Weapon/RangeWeapon.h"
#include "Weapon/MeleeWeapon.h"
#include "Weapon/BulletWaveWeapon.h"
#include "Weapon/Bullet.h"

#include "Textures/Textures.h"

GameManager::GameManager(const game_engine::primitives::RenderWindow& window) : m_window(window) {}

void GameManager::initGame() {
    m_gameStateMachine = game_engine::GameStateMachine::instance();
    m_stateMachineConnections.push_back(m_gameStateMachine->fireGamePaused.connect([]() {
        game_engine::TimersHolder::pauseAllTimers();
    }));
    m_stateMachineConnections.push_back(m_gameStateMachine->fireGameResumed.connect([]() mutable {
        game_engine::TimersHolder::resumeAllTimers();
    }));
    m_stateMachineConnections.push_back(m_gameStateMachine->fireGameRestarted.connect([this]() {
        restartGame();
    }));
    m_stateMachineConnections.push_back(m_gameStateMachine->fireGameOver.connect([this]() {
        const auto& value = m_gameDataDB->getBestScore();
        if ((value && value.value() < GamePointsController::instance()->points()) || !value) {
            m_gameDataDB->setBestScore(GamePointsController::instance()->points());
        }
    }));

    m_dbManager = std::make_shared<game_engine::database::DataBaseManager>();
    m_gameDataDB = std::make_unique<GameDataDBWrapper>(m_dbManager);
    m_gameDataDB->init();

    m_gameScreenManager = game_engine::ui::GameScreenManager::instance();
    m_gameScreenManager->addGameScreen(game_engine::GameState::GAME_OVER, std::make_unique<GameOverScreen>());
    m_gameScreenManager->addGameScreen(game_engine::GameState::RUNNING, std::make_unique<GameInterfaceScreen>());

    m_textureHolder = TextureHolder::instance();
    m_textureHolder->setTextures();

    m_world = game_engine::World::instance();
    m_world->initWorld(m_textureHolder->lvl1_background_texture(), m_textureHolder->lvl1_border_texture());

    m_particleSystem = game_engine::ParticleSystem::instance();

    m_player = std::make_shared<Player>(m_textureHolder->player_textures(), game_engine::primitives::Vector2f(PLAYER_START_X, PLAYER_START_Y), PLAYER_START_HP);
    m_player->initWeapon(WeaponType::RANGE, 1.0, m_textureHolder->bullet_texture());
    m_player->initWeapon(WeaponType::MELEE, 1.0, m_textureHolder->sword_texture());
    m_player->initWeapon(WeaponType::BULLET_WAVE, 1.0, {});

    m_pickableSpawner = PickableSpawner::instance();
    m_pickableSpawner->setPlayer(m_player);
    m_pickableSpawner->addPickableTexture(PickableType::HEAL, m_textureHolder->heal_texture());
    m_pickableSpawner->addPickableTexture(PickableType::BULLET_WAVE, m_textureHolder->bullet_texture());
    m_pickableSpawner->addPickableTexture(PickableType::CURRENCY, m_textureHolder->coin_texture());

    m_enemiesManager = std::make_unique<EnemiesManager>();
    m_enemiesManager->setPlayer(m_player);
    m_enemiesManager->setBulletTexture(m_textureHolder->bullet_texture());
    m_enemiesManager->addTexture(m_textureHolder->flying_eye_texture());

    m_viewController = ViewController::instance();
    m_viewController->setPlayer(m_player);

    m_gamePointsController = GamePointsController::instance();
    m_cashValueController = CashValueController::instance();

    m_gameStateMachine->setState(game_engine::GameState::RUNNING); // TODO: this is a temporary solution. Remove after main menu impl
    m_gameOverAtNextIter = false;
}

void GameManager::deinitGame() {
    m_stateMachineConnections.clear();

    game_engine::TimersHolder::stopAllTimers();

    game_engine::ui::DamageIndicatorsHolder::deleteAllIndicators();

    m_player = nullptr;
    m_enemiesManager = nullptr;
    m_viewController = nullptr;
    m_pickableSpawner = nullptr;
    m_world = nullptr;
    m_gameStateMachine = nullptr;
    m_gameScreenManager = nullptr;
    m_gamePointsController = nullptr;
    m_cashValueController = nullptr;

    game_engine::DrawableObject::deleteAllDrawableObjects();
}

void GameManager::restartGame() {
    deinitGame();
    initGame();
}

void GameManager::Update(float time) {
    game_engine::TimersHolder::deleteExpiredTimers();
    auto characters = m_enemiesManager->getCharacters();

    if (m_gameStateMachine->currentState() == game_engine::GameState::RUNNING) {
        m_pickableSpawner->Update(time);
        game_engine::ParticleSystem::instance()->Update(time / 1000);
        m_player->Update(time);
        m_player->attackEnemies(time, characters);
        m_enemiesManager->Update(time);
        m_viewController->Update(time, m_window);
        m_gameScreenManager->Update(time);

        game_engine::ui::DamageIndicatorsHolder::Update(time);

        if (m_gameOverAtNextIter) {
            m_gameStateMachine->setState(game_engine::GameState::GAME_OVER);
        }
        if (m_player->getHP() <= 0) {
            m_gameOverAtNextIter = true;
        }
    }
}

void GameManager::handleEvent(std::unique_ptr<game_engine::primitives::Event> event) {
    const auto key_event = event && event->type() == game_engine::primitives::Event::Type::Keyboard ? event->as<game_engine::primitives::KeyEvent>() : nullptr;
    if (event) {
        if (event->type() == game_engine::primitives::Event::Type::Close) {
            m_window.close();
        }
    }
    if (key_event && key_event->action() == game_engine::primitives::KeyEvent::Action::Press) {
        if (key_event->key() == game_engine::primitives::KeyEvent::Key::Escape) {
            if (m_gameStateMachine->currentState() == game_engine::GameState::RUNNING) {
                m_gameStateMachine->setState(game_engine::GameState::PAUSED);
            }
            else if (m_gameStateMachine->currentState() == game_engine::GameState::PAUSED) {
                m_gameStateMachine->setState(game_engine::GameState::RUNNING);
            }
        }
        else if (key_event->key() == game_engine::primitives::KeyEvent::Key::R) {
            m_gameStateMachine->setState(game_engine::GameState::RUNNING);
        }
    }
}

void GameManager::drawGameObjects() {
    game_engine::DrawableObject::drawAllDrawableObjects(m_window);
    game_engine::ParticleSystem::instance()->drawParticles(m_window);
}
