#include "../include/Weapon.h"
#include "../include/Bullet.h"

Weapon::Weapon(sf::Texture& bullet_texture, sf::Vector2f pos, float damage_scale) {
    m_bullet_texture = bullet_texture;
    m_pos = pos;
    m_damage_scale = damage_scale;
}

Weapon::~Weapon() {
    for (auto b : m_bullets) {
        delete b;
    }
}

void Weapon::Update(float time, std::vector<Character*>& characters) {
    for (auto iter = m_bullets.begin(); iter != m_bullets.end(); iter++) {
        auto bullet = *iter;
        if (bullet) {
            bullet->Update(time);
            if (bullet->checkCollisionWithCharacters(characters) || bullet->checkCollisionWithMapBorders()) {
                delete bullet;
                m_bullets.erase(iter);
            }
        }
    }
}

void Weapon::Shoot(sf::Vector2f direction) {
    Bullet* new_bullet = new Bullet(m_bullet_texture, m_pos, direction);
    new_bullet->updateDamage(m_damage_scale);
    m_bullets.push_back(new_bullet);
}