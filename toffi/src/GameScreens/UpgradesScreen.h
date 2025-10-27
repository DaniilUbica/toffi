#pragma once

#include "Engine/UI/GameScreen/GameScreenBase.h"

class UpgradesScreen : public game_engine::ui::GameScreenBase {
public:
    using game_engine::ui::GameScreenBase::GameScreenBase;

    void constructScreen() override;
    void Update(float time) override {};
};
