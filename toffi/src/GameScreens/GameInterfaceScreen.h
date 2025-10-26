#pragma once

#include "Engine/UI/GameScreen/GameScreenBase.h"

#include "Primitives/Text/Text.hpp"

#include <nod/nod.hpp>

namespace game_engine {
 class Timer;
}

class GameInterfaceScreen : public game_engine::ui::GameScreenBase {
public:
    using game_engine::ui::GameScreenBase::GameScreenBase;

    void constructScreen() override;
    void Update(float time) override;

private:
    std::shared_ptr<game_engine::primitives::Text> m_pointsText;
    std::shared_ptr<game_engine::primitives::Sprite> m_currencySprite; // TODO: image could be animated, so have to use smth like GameObject here
    std::shared_ptr<game_engine::primitives::Text> m_currencyText;
    std::shared_ptr<game_engine::primitives::Text> m_levelTimerText;
    std::shared_ptr<game_engine::Timer> m_levelTimer;
    nod::scoped_connection m_gamePointsConnection;
    nod::scoped_connection m_cashValueConnection;
};
