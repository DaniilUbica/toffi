#pragma once

#include "Engine/Character.h"

class PlayerController;
class Animation;

enum class State {
    IDLE,
    RUN
};

enum class Direction : bool {
    LEFT = 0,
    RIGHT = 1
};

using textures_t = std::map<State, sf::Texture>;

class Player : public Character {
private:
    State             m_state;
    Direction         m_direction = Direction::RIGHT;
    PlayerController* m_controller;
    Animation*        m_idle_animation;
    Animation*        m_run_animation;

    void checkCollisionWithMapBorders();

public:
    Player() = delete;
    Player(std::map<State, sf::Texture>& textures, sf::Vector2f start_pos);
    ~Player();

    void Update(float time) override;

    void setState(State state);
    void setDirection(Direction direction);
};