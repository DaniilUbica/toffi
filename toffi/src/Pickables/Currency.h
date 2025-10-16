#pragma once

#include "Engine/Base/Pickable.h"

class Player;

class Currency : public game_engine::Pickable {
public:
    Currency(std::shared_ptr<game_engine::Character> character, const game_engine::primitives::Texture& texture, game_engine::primitives::Vector2f pos, unsigned int valueToAdd);

    virtual void onPicked() override;

private:
    unsigned int m_valueToAdd = 0;
};
