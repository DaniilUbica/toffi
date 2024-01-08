#pragma once

#include "../Engine/Character.h"

class Player;
class Timer;

class Enemy : public Character {
private:
    Player* m_player;
    Timer*  m_attack_cooldown;
    float   m_speed;
    float   m_damage;

    void followPlayer(float time);
    void updateDirection();
    void attackIfCanAttack();
public:
    Enemy(sf::Texture& textures, sf::Vector2f pos, float attack_cooldown, float speed, float damage, float health);
    ~Enemy();

    void Update(float time);

    void setPlayer(Player* player);
};

