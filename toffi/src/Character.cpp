#include "..\include\Engine\Character.h"

void Character::takeDamage(float damage) {
    m_health -= damage;
}

void Character::setPosition(sf::Vector2f& pos) {
    m_pos = pos;
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
