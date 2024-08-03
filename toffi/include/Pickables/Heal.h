#pragma once

#include "Engine/Pickable.h"

class Player;

class Heal : public Pickable {
private:
    std::shared_ptr<Player> m_player;

public:
    Heal(const sf::Texture& texture, sf::Vector2f pos);

    virtual void onPicked() override;

    void setPlayer(std::shared_ptr<Player> player);
};
