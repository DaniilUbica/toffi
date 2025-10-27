#include "Engine/GameStateMachine.h"

enum class ToffiGameState {
    UPGRADE_STAGE = static_cast<int>(game_engine::GameState::GAME_STATES_SIZE)
};

class StateMachine final : public game_engine::GameStateMachine {
public:
    StateMachine();
    ~StateMachine();

    void setState(int newState) override;

    nod::signal<void()> fireUpgradeStage;
    nod::signal<void()> fireNewLevel;
};
