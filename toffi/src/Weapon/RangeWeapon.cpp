#include "Weapon/RangeWeapon.h"
#include "Engine/Base/Character.h"
#include "Bullet.h"

RangeWeapon::RangeWeapon(const game_engine::primitives::Texture& bullet_texture, game_engine::primitives::Vector2f pos, float damage_scale, float reload_time) : Weapon(pos, damage_scale, reload_time) {
    m_bullet_texture = bullet_texture;
    m_weapon_type = WeaponType::RANGE;
}

void RangeWeapon::Update(float time, game_engine::primitives::Vector2f pos, std::vector<std::shared_ptr<game_engine::Character>>& characters, float attack_range) {
	Weapon::commonUpdate(pos, characters, attack_range);
	
    m_pos = pos;

    if (!m_bullets.empty()) {
        for (auto iter = m_bullets.begin(); iter != m_bullets.end(); iter++) {
            auto bullet = *iter;

            if (bullet) {
                bullet->Update(characters, time);
                if (bullet->getCollided()) {
                    m_bullets.erase(iter);
                    break;
                }
            }
        }
    }

    attackIfCanAttack();
}

void RangeWeapon::attackIfCanAttack() {
    if (m_gotEnemyInAttackRange && !m_reload_timer->isRunning()) {
        auto new_bullet = std::make_shared<Bullet>(m_bullet_texture, m_pos, m_direction);
        new_bullet->updateDamage(m_damage_scale);
        m_bullets.push_back(new_bullet);
        m_reload_timer->Start();
    }
}

void RangeWeapon::shootConcreteBullet(std::shared_ptr<Bullet> bullet) {
	m_bullets.push_back(bullet);
}

std::vector<std::shared_ptr<Bullet>> RangeWeapon::getBullets() const {
    return m_bullets;
}
