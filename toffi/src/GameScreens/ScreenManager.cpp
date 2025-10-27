#include "ScreenManager.h"

#include "StateMachine.h"

ScreenManager::ScreenManager(std::shared_ptr<StateMachine> stateMachine) : game_engine::ui::GameScreenManager(stateMachine) {
    m_stateMachineConnections.push_back(stateMachine->fireUpgradeStage.connect([this]() {
        onUpgradeStage();
    }));
}

void ScreenManager::onUpgradeStage() {
    hideAllGameScreens();
    m_gameScreens[static_cast<int>(ToffiGameState::UPGRADE_STAGE)]->showGameScreen();
}
