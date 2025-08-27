#pragma once

#include <SFML/Graphics.hpp>

#include <cmath>

#include "Engine/Core/Timer.h"

class Bullet;

namespace game_engine {
    class Character;
    class Timer;
}

enum class WeaponType {
    RANGE,
    MELEE
};

class Weapon {
private:
	float distance(sf::Vector2f v1, sf::Vector2f v2);
	bool compareDistance(sf::Vector2f v1, sf::Vector2f v2, sf::Vector2f target);
	bool isInAttackRange(sf::Vector2f pos, std::shared_ptr<game_engine::Character> character, float range);

protected:
    sf::Vector2f                        m_pos;
	sf::Vector2f 		                m_direction;
    std::unique_ptr<game_engine::Timer> m_reload_timer;
    WeaponType                          m_weapon_type;
    float                               m_damage_scale = 1.f;
    float                               m_reload_time = 1.f;
	bool				                m_gotEnemyInAttackRange = false;

	void commonUpdate(sf::Vector2f pos, std::vector<std::shared_ptr<game_engine::Character>>& characters, float attack_range);

public:
    virtual ~Weapon() = default;

    virtual void Update(float time, sf::Vector2f pos, std::vector<std::shared_ptr<game_engine::Character>>& characters, float attack_range) = 0;
    virtual void Attack() = 0;
    virtual void updateAttackSpeed(float scale);


    WeaponType getWeaponType() const;
};

