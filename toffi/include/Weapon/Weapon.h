#pragma once

#include <SFML/Graphics.hpp>

#include "../Engine/Timer.h"

class Bullet;
class Character;
class Timer;

enum class WeaponType {
    RANGE,
    MELEE
};

class Weapon {
protected:
    sf::Vector2f           m_pos;
    std::unique_ptr<Timer> m_reload_timer;
    WeaponType             m_weapon_type;
    float                  m_damage_scale;
    float                  m_reload_time;

public:
    virtual ~Weapon() = default;

    virtual void Update(float time, sf::Vector2f pos, std::vector<std::shared_ptr<Character>>& characters) = 0;
    virtual void Attack(sf::Vector2f direction) = 0;
    virtual void updateAttackSpeed(float scale);

    WeaponType getWeaponType() const;
};

