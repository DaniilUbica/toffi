#pragma once

#include "Engine/Base/Pickable.h"

class Player;

class Heal : public game_engine::Pickable {
private:
    std::shared_ptr<Player> m_player;

public:
    Heal(const sf::Texture& texture, sf::Vector2f pos);

    virtual void onPicked() override;

    void setPlayer(std::shared_ptr<Player> player);
};
