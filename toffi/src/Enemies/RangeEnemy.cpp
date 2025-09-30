#include "Enemies/RangeEnemy.h"
#include "Engine/Animation/Animation.h"
#include "Constants.h"
#include "Weapon/Bullet.h"
#include "Player/Player.h"

void RangeEnemy::followPlayer(float time) {
	game_engine::primitives::Vector2f diff = { abs(m_player->getPosition().x - m_pos.x), abs(m_player->getPosition().y - m_pos.y) };
	if (diff.x >= ENEMY_ATTACK_RANGE || diff.y >= ENEMY_ATTACK_RANGE) {
		game_engine::primitives::Vector2f player_pos = m_player->getPosition();
		game_engine::primitives::Vector2f direction = player_pos - m_pos;
		direction /= static_cast<float>(sqrt(direction.x * direction.x + direction.y * direction.y));
		m_pos.x += direction.x * m_speed * time;
		m_pos.y += direction.y * m_speed * time;
	}
}

void RangeEnemy::updateDirection() {
	if (m_player->getPosition().x > m_pos.x) {
        m_direction = game_engine::Direction::RIGHT;
	}
	else {
        m_direction = game_engine::Direction::LEFT;
	}
}

void RangeEnemy::attackIfCanAttack() {
	game_engine::primitives::Vector2f diff = { abs(m_player->getPosition().x - m_pos.x), abs(m_player->getPosition().y - m_pos.y) };
	if ((diff.x <= ENEMY_ATTACK_RANGE && diff.y <= ENEMY_ATTACK_RANGE) && !m_attack_cooldown->isRunning()) {
		game_engine::primitives::Vector2f player_pos = m_player->getPosition();
		game_engine::primitives::Vector2f direction = player_pos - m_pos;

		direction /= static_cast<float>(sqrt(direction.x * direction.x + direction.y * direction.y));
		auto new_bullet = std::make_shared<Bullet>(m_bullet_texture, m_pos, direction);
		new_bullet->updateDamage(ENEMY_BULLET_DAMAGE / BULLET_DEFAULT_DAMAGE);
		m_bullets.push_back(new_bullet);
		m_attack_cooldown->Start();
	}
}

RangeEnemy::RangeEnemy(const game_engine::primitives::Texture& textures, const game_engine::primitives::Texture& bullet_texture, game_engine::primitives::Vector2f pos, float attack_cooldown, float speed, float damage, float health) : Enemy(textures, pos, attack_cooldown, speed, damage, health) {
	m_bullet_texture = bullet_texture;
}

void RangeEnemy::Update(float time) {
	Enemy::Update(time);

	m_sprite->setColor(game_engine::primitives::colors::Green);

	for (auto bullet : m_bullets) {
		bullet->Update(m_player, time);
		if (bullet->getCollided()) {
			m_bullets.erase(std::find(m_bullets.begin(), m_bullets.end(), bullet));
			break;
		}
	}
}
