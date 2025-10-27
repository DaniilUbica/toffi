#pragma once

#include "Engine/IGameManager.h"
#include "Engine/DataBase/DataBaseManager.h"
#include "Engine/TimersHolder.hpp"

#include "Database/GameDataDBWrapper.h"

#include <nod/nod.hpp>

#include <memory>
#include <list>

namespace game_engine {
    class ParticleSystem;
    class World;
}

class TextureHolder;
class PickableSpawner;
class Player;
class EnemiesManager;
class ViewController;
class GamePointsController;
class CashValueController;
class StateMachine;
class ScreenManager;

class GameManager : public game_engine::IGameManager {
public:
    GameManager(const game_engine::primitives::RenderWindow& window);

    void initGame() override;
    void deinitGame() override;
    void restartGame() override;

    void Update(float time) override;
    void handleEvent(std::unique_ptr<game_engine::primitives::Event> event) override;
    void drawGameObjects() override;

    std::shared_ptr<StateMachine> gameStateMachine() const { return m_gameStateMachine; };

private:
    void startNewLevel();

    bool m_gameOverAtNextIter = false;

    std::list<nod::scoped_connection> m_stateMachineConnections;

    std::unique_ptr<EnemiesManager> m_enemiesManager;
    std::shared_ptr<Player> m_player;
    std::shared_ptr<ViewController> m_viewController;
    std::shared_ptr<TextureHolder> m_textureHolder;
    std::shared_ptr<PickableSpawner> m_pickableSpawner;
    std::shared_ptr<GamePointsController> m_gamePointsController;
    std::shared_ptr<CashValueController> m_cashValueController;
    std::unique_ptr<GameDataDBWrapper> m_gameDataDB;
    std::shared_ptr<ScreenManager> m_gameScreenManager;

    std::shared_ptr<StateMachine> m_gameStateMachine;
    std::shared_ptr<game_engine::World> m_world;
    std::shared_ptr<game_engine::ParticleSystem> m_particleSystem;

    std::shared_ptr<game_engine::database::DataBaseManager> m_dbManager;

    std::shared_ptr<game_engine::Timer> m_levelTimer;

    game_engine::primitives::RenderWindow m_window;
};
