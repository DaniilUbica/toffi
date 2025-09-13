#pragma once

#include "Engine/Base/Pickable.h"

class Player;

class Heal : public game_engine::Pickable {
private:
    std::shared_ptr<Player> m_player;

public:
    Heal(const game_engine::primitives::Texture& texture, game_engine::primitives::Vector2f pos);

    virtual void onPicked() override;

    void setPlayer(std::shared_ptr<Player> player);
};
