#pragma once

#include "Engine/Character.h"

class PlayerController;

enum class State {
    IDLE,
    RUN
};

enum class Direction {
    LEFT,
    RIGHT
};

class Player : public Character {
private:
    State             m_state;
    Direction         m_direction;
    PlayerController* m_controller;

public:
    Player() = delete;
    Player(sf::Texture& texture, sf::Vector2f start_pos);
    ~Player();

    void Update(float time) override;
    void changeDirection();

    void setState(State state);
    void setDirection(Direction direction);
};