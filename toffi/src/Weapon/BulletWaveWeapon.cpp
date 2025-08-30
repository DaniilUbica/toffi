#include "BulletWaveWeapon.h"
#include "Bullet.h"

BulletWaveWeapon::BulletWaveWeapon(sf::Vector2f pos, float damage_scale) {
    m_pos = pos;
    m_damage_scale = damage_scale;
    m_weapon_type = WeaponType::BULLET_WAVE;
}

void BulletWaveWeapon::Update(float time, sf::Vector2f pos, std::vector<std::shared_ptr<game_engine::Character>>& characters, float attack_range) {
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
}
