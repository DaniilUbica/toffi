#include "..\include\Engine\Character.h"

Character::~Character() {
    delete m_run_animation;
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

float Character::getHP() {
    return m_health;
}

sf::Vector2f Character::getSize() {
    return m_size;
}

sf::Vector2f Character::getPosition() {
    return m_pos;
}

sf::Sprite Character::getSprite() {
    return m_sprite;
}

Direction Character::getDirection()
{
    return m_direction;
}

HealthBar* Character::getHealthBar() {
    return m_health_bar;
}
