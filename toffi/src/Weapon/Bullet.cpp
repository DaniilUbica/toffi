#include "Bullet.h"
#include "Constants.h"
#include "Engine/Base/Character.h"

Bullet::Bullet(const sf::Texture& texture, sf::Vector2f pos, sf::Vector2f direction) {
    m_sprite = std::make_shared<sf::Sprite>(texture);
    m_pos = pos;
    m_size = sf::Vector2f(BULLET_DEFAULT_SIZE, BULLET_DEFAULT_SIZE);
    m_direction = direction;
    m_damage = BULLET_DEFAULT_DAMAGE;
}

void Bullet::Update(float time) {
    m_pos.x += m_direction.x * BULLET_DEFAULT_SPEED * time;
    m_pos.y += m_direction.y * BULLET_DEFAULT_SPEED * time;

    m_sprite->setPosition(m_pos);
    m_sprite->setScale({ 0.5, 0.5 });
}

bool Bullet::checkCollisionWithMapBorders() {
    if (m_pos.y >= game_engine::WORLD_HEIGHT - m_size.y || m_pos.y <= game_engine::SPRITE_SIZE ||
        m_pos.x >= game_engine::WORLD_WIDTH - m_size.x || m_pos.x <= game_engine::SPRITE_SIZE) {
        return true;
    }

    return false;
}

void Bullet::updateDamage(float scale) {
    m_damage *= scale;
}

bool Bullet::checkCollisionWithCharacters(std::vector<std::shared_ptr<game_engine::Character>>& characters) {
    for (auto c : characters) {
        if (m_sprite->getGlobalBounds().findIntersection(c->getSprite()->getGlobalBounds())) {
            c->takeDamage(m_damage);
            return true;
        }
    }

    return false;
}

bool Bullet::checkCollisionWithCharacter(std::shared_ptr<game_engine::Character> character) {
	if (m_sprite->getGlobalBounds().findIntersection(character->getSprite()->getGlobalBounds())) {
		character->takeDamage(m_damage);
		return true;
	}

    return false;
}
