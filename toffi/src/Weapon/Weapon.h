#pragma once

#include <cmath>

#include "Engine/Base/GameObject.h"
#include "Engine/Core/Timer.h"

class Bullet;

namespace game_engine {
    class Character;
}

enum class WeaponType {
    RANGE,
    MELEE,
    BULLET_WAVE
};

class Weapon : public game_engine::GameObject {
private:
	float distance(game_engine::primitives::Vector2f v1, game_engine::primitives::Vector2f v2) const;
	bool compareDistance(game_engine::primitives::Vector2f v1, game_engine::primitives::Vector2f v2, game_engine::primitives::Vector2f target) const;
	bool isInAttackRange(game_engine::primitives::Vector2f pos, std::shared_ptr<game_engine::Character> character, float range) const;

protected:
    game_engine::primitives::Vector2f   m_pos;
	game_engine::primitives::Vector2f 	m_direction;
    std::shared_ptr<game_engine::Timer> m_reload_timer;
    WeaponType                          m_weapon_type;
    float                               m_damage_scale = 1.f;
    float                               m_reload_time = 1.f;
	bool				                m_gotEnemyInAttackRange = false;

	void commonUpdate(game_engine::primitives::Vector2f pos, std::vector<std::shared_ptr<game_engine::Character>>& characters, float attack_range);
    std::shared_ptr<game_engine::Character> getNearestCharacter(std::vector<std::shared_ptr<game_engine::Character>>& characters) const;
    virtual void attackIfCanAttack() = 0;

    Weapon(game_engine::primitives::Vector2f pos, float damage_scale, float reload_time, const game_engine::primitives::Texture& texture = {});
    Weapon() {};

public:
    virtual ~Weapon() = default;

    virtual void Update(float time, game_engine::primitives::Vector2f pos, std::vector<std::shared_ptr<game_engine::Character>>& characters, float attack_range) = 0;
    virtual void updateAttackSpeed(float scale);


    WeaponType getWeaponType() const;
};

