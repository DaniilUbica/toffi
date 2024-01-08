#include "../include/Engine/Timer.h"
#include "../include/Weapon.h"
#include "../include/Bullet.h"

Weapon::Weapon(sf::Texture& bullet_texture, sf::Vector2f pos, float damage_scale, float reload_time) {
    m_bullet_texture = bullet_texture;
    m_pos = pos;
    m_damage_scale = damage_scale;
    m_reload_time = reload_time;

    m_reload_timer = new Timer(m_reload_time);
}

Weapon::~Weapon() {
    for (auto b : m_bullets) {
        delete b;
    }

    delete m_reload_timer;
}

void Weapon::Update(float time, sf::Vector2f pos, std::vector<Character*>& characters) {
    m_pos = pos;
    if (!m_bullets.empty()) {
        for (auto iter = m_bullets.begin(); iter != m_bullets.end(); iter++) {
            auto bullet = *iter;
            if (bullet) {
                bullet->Update(time);
                if (bullet->checkCollisionWithCharacters(characters) || bullet->checkCollisionWithMapBorders()) {
                    delete bullet;
                    iter = m_bullets.erase(iter);
                    break;
                }
            }
        }
    }
}

void Weapon::Shoot(sf::Vector2f direction) {
    if (!m_reload_timer->isRunning()) {
        Bullet* new_bullet = new Bullet(m_bullet_texture, m_pos, direction);
        new_bullet->updateDamage(m_damage_scale);
        m_bullets.push_back(new_bullet);
        m_reload_timer->Start();
    }
}

void Weapon::updateAttackSpeed(float scale) {
    m_reload_time *= scale;
}

std::vector<Bullet*> Weapon::getBullets() {
    return m_bullets;
}
