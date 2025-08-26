#pragma once

#include "Engine/Base/Character.h"
#include "Engine/Core/Timer.h"

class Player;
class Timer;

class Enemy : public game_engine::Character {
protected:
	std::shared_ptr<Player>             m_player;
	std::unique_ptr<game_engine::Timer> m_attack_cooldown;
    float                               m_speed;
    float                               m_damage;

	Enemy() = default;
	
    virtual void followPlayer(float time);
	virtual void updateDirection();
	virtual void attackIfCanAttack();

public:
    Enemy(const sf::Texture& textures, sf::Vector2f pos, float attack_cooldown, float speed, float damage, float health);
    ~Enemy() = default;

    void Update(float time);

    void setPlayer(std::shared_ptr<Player> player);
};

