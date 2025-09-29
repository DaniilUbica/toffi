#pragma once

#include "Engine/Base/Pickable.h"

class Player;

class Heal : public game_engine::Pickable {
public:
    Heal(std::shared_ptr<game_engine::Character> character, const game_engine::primitives::Texture& texture, game_engine::primitives::Vector2f pos);

    virtual void onPicked() override;
};
