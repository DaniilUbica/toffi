#pragma once

#include "Engine/UI/GameScreen/GameScreenBase.h"

namespace {
    using drawable_t = std::shared_ptr<game_engine::primitives::Drawable>;
}

class GameOverScreen : public game_engine::ui::GameScreenBase {
public:
    ~GameOverScreen() {}
    virtual void constructScreen() override;
    
    void setAllScreenObjectsVisible(bool visible) override;
    void draw(const game_engine::primitives::RenderWindow &window) override;

private:
    std::vector<std::pair<drawable_t, bool /* visible */>> m_primitivesDrawableObjects;
};
