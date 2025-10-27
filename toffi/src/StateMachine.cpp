#include "StateMachine.h"

StateMachine::StateMachine() {}

StateMachine::~StateMachine() {}

void StateMachine::setState(int newState) {
    const auto gameState = static_cast<ToffiGameState>(newState);

    if (m_prevState == static_cast<int>(ToffiGameState::UPGRADE_STAGE) && m_currentState == static_cast<int>(game_engine::GameState::RUNNING)) {
        m_prevState = m_currentState;
        m_currentState = newState;

        fireNewLevel();
        return;
    }

    if (newState < static_cast<int>(ToffiGameState::UPGRADE_STAGE)) {
        GameStateMachine::setState(newState);
        return;
    }

    m_prevState = m_currentState;
    m_currentState = newState;

    switch (gameState) {
        case ToffiGameState::UPGRADE_STAGE:
            if (m_prevState == static_cast<int>(game_engine::GameState::RUNNING)) {
                fireUpgradeStage();
            }
            break;
        default:
            break;
    }
}
