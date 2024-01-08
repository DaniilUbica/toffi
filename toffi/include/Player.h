#pragma once

#include "Engine/Character.h"

class PlayerController;
class Weapon;

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
    Weapon*           m_weapon;

    void checkCollisionWithMapBorders();

public:
    Player() = delete;
    Player(std::map<State, sf::Texture>& textures, sf::Vector2f start_pos);
    ~Player();

    void Update(float time) override;
    void attackEnemies(float time, std::vector<Character*>& characters);
    void initWeapon(sf::Texture& bullet_texture, float damage_scale);

    void setState(State state);
};