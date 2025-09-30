#pragma once

#include "Engine/Base/Character.h"
#include "Engine/Core/Timer.h"

#include <cmath>

class Player;
class Timer;

class Enemy : public game_engine::Character {
protected:
	std::shared_ptr<Player>             m_player;
	std::shared_ptr<game_engine::Timer> m_attack_cooldown;
    float                               m_speed;
    float                               m_damage;

    Enemy(const game_engine::primitives::Texture& texture) : game_engine::Character(texture) {};

    virtual void followPlayer(float time);
	virtual void updateDirection();
	virtual void attackIfCanAttack();

public:
    Enemy(const game_engine::primitives::Texture& textures, game_engine::primitives::Vector2f pos, float attack_cooldown, float speed, float damage, float health);
    ~Enemy();

    void Update(float time);

    void setPlayer(std::shared_ptr<Player> player);
};

