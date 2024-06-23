#include "Weapon/RangeWeapon.h"
#include "Engine/Timer.h"
#include "Engine/Character.h"
#include "Bullet.h"

RangeWeapon::RangeWeapon(const sf::Texture& bullet_texture, sf::Vector2f pos, float damage_scale, float reload_time) {
    m_bullet_texture = bullet_texture;
    m_pos = pos;
    m_damage_scale = damage_scale;
    m_reload_time = reload_time;
    m_weapon_type = WeaponType::RANGE;

    m_reload_timer = std::make_unique<Timer>(m_reload_time);
}

void RangeWeapon::Update(float time, sf::Vector2f pos, std::vector<std::shared_ptr<Character>>& characters, float attack_range) {
	Weapon::commonUpdate(pos, characters, attack_range);
	
    m_pos = pos;

    if (!m_bullets.empty()) {
        for (auto iter = m_bullets.begin(); iter != m_bullets.end(); iter++) {
            auto bullet = *iter;

            if (bullet) {
                bullet->Update(time);
                if (bullet->checkCollisionWithCharacters(characters) || bullet->checkCollisionWithMapBorders()) {
                    m_bullets.erase(iter);
                    break;
                }
            }
        }
    }
}

void RangeWeapon::Attack() {
    if (m_gotEnemyInAttackRange && !m_reload_timer->isRunning()) {
        auto new_bullet = std::make_shared<Bullet>(m_bullet_texture, m_pos, m_direction);
        new_bullet->updateDamage(m_damage_scale);
        m_bullets.push_back(new_bullet);
        m_reload_timer->Start();
    }
}

std::vector<std::shared_ptr<Bullet>> RangeWeapon::getBullets() const {
    return m_bullets;
}
