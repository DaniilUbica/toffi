#include "Engine/UI/GameScreen/GameScreenManager.h"

class StateMachine;

namespace {
    using game_screen_t = std::unique_ptr<game_engine::ui::GameScreenBase>;
}

class ScreenManager final : public game_engine::ui::GameScreenManager {
public:
    ScreenManager(std::shared_ptr<StateMachine> stateMachine);

private:
    void onUpgradeStage();
};
