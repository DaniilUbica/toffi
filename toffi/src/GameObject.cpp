#include "../include/Engine/GameObject.h"

sf::Sprite GameObject::getSprite() {
    return m_sprite;
}

sf::Vector2f GameObject::getPosition() {
    return m_pos;
}

sf::Vector2f GameObject::getSize() {
    return m_size;
}
