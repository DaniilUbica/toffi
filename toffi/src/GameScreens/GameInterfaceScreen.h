#pragma once

#include "Engine/UI/GameScreen/GameScreenBase.h"

#include "Primitives/Text/Text.hpp"

#include <nod/nod.hpp>

class GameInterfaceScreen : public game_engine::ui::GameScreenBase {
public:
    using game_engine::ui::GameScreenBase::GameScreenBase;

    void constructScreen() override;
    void Update(float time) override;

private:
    std::shared_ptr<game_engine::primitives::Text> m_pointsText;
    nod::scoped_connection m_gamePointsConntection;
};
