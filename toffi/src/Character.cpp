#include "../include/Engine/Character.h"

Character::~Character() {
    if (m_run_animation) {
        delete m_run_animation;
    }
}

void Character::takeDamage(float damage) {
    m_health -= damage;
}

void Character::setPosition(sf::Vector2f& pos) {
    m_pos = pos;
}

void Character::setDirection(Direction direction) {
    m_direction = direction;
}

float Character::getHP() const {
    return m_health;
}

sf::Vector2f Character::getSize() const {
    return m_size;
}

sf::Vector2f Character::getPosition() const {
    return m_pos;
}

sf::Sprite Character::getSprite() const {
    return m_sprite;
}

Direction Character::getDirection() const {
    return m_direction;
}

HealthBar* Character::getHealthBar() const {
    return m_health_bar;
}
