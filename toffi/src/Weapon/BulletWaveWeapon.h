#pragma once

#include "Weapon.h"

class BulletWaveWeapon : public Weapon {
    std::vector<std::shared_ptr<Bullet>> m_bullets;

    void attackIfCanAttack() override {};

public:
    BulletWaveWeapon(sf::Vector2f pos, float damage_scale);
    ~BulletWaveWeapon() = default;

    void Update(float time, sf::Vector2f pos, std::vector<std::shared_ptr<game_engine::Character>>& characters, float attack_range) override;

    void setBullets(std::vector<std::shared_ptr<Bullet>>& bullets) { m_bullets = bullets; };

    std::vector<std::shared_ptr<Bullet>> getBullets() const { return m_bullets; };
};
