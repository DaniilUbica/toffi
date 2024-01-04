#pragma once

#include "Engine/Character.h"

class PlayerController;

enum class State {
    IDLE,
    RUN
};

using textures_t = std::map<State, sf::Texture>;

class Player : public Character {
private:
    State             m_state;
    PlayerController* m_controller;
    Animation*        m_idle_animation;

    void checkCollisionWithMapBorders();

public:
    Player() = delete;
    Player(std::map<State, sf::Texture>& textures, sf::Vector2f start_pos);
    ~Player();

    void Update(float time) override;

    void setState(State state);
};