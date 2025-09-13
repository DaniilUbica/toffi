#include "Bullet.h"
#include "Constants.h"
#include "Engine/Base/Character.h"

void Bullet::commonUpdate(float time) {
    m_pos.x += m_direction.x * BULLET_DEFAULT_SPEED * time;
    m_pos.y += m_direction.y * BULLET_DEFAULT_SPEED * time;

    m_sprite->setPosition(m_pos);

    m_collided = checkCollisionWithMapBorders();
}

Bullet::Bullet(const game_engine::primitives::Texture& texture, game_engine::primitives::Vector2f pos, game_engine::primitives::Vector2f direction) {
    m_texture = texture;
    m_sprite = std::make_shared<game_engine::primitives::Sprite>(m_texture);
    m_pos = pos;
    m_size = game_engine::primitives::Vector2f(BULLET_DEFAULT_SIZE, BULLET_DEFAULT_SIZE);
    m_direction = direction;
    m_damage = BULLET_DEFAULT_DAMAGE;

    m_sprite->setScale({ 0.5, 0.5 });
}

void Bullet::Update(std::vector<std::shared_ptr<game_engine::Character>>& characters, float time) {
    commonUpdate(time);

    m_collided = checkCollisionWithCharacters(characters);
}

void Bullet::Update(std::shared_ptr<game_engine::Character> character, float time) {
    commonUpdate(time);

    m_collided = checkCollisionWithCharacter(character);
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
        if (m_sprite->getGlobalBounds().intersects(c->getSprite()->getGlobalBounds())) {
            c->takeDamage(m_damage);
            return true;
        }
    }

    return false;
}

bool Bullet::checkCollisionWithCharacter(std::shared_ptr<game_engine::Character> character) {
	if (m_sprite->getGlobalBounds().intersects(character->getSprite()->getGlobalBounds())) {
		character->takeDamage(m_damage);
		return true;
	}

    return false;
}
