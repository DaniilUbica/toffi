#include "Engine/Character.h"

void Character::takeDamage(float damage) {
    m_health -= damage;
}

void Character::addHP(float health) {
    m_health += health;
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

std::shared_ptr<sf::Sprite> Character::getSprite() const {
    return m_sprite;
}

Direction Character::getDirection() const {
    return m_direction;
}

std::shared_ptr<HealthBar> Character::getHealthBar() const {
    return m_health_bar;
}
