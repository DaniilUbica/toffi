#include "Enemies/RangeEnemy.h"
#include "Engine/Animation/Animation.h"
#include "Constants.h"
#include "Engine/Core/Timer.h"
#include "Weapon/Bullet.h"
#include "Player/Player.h"

void RangeEnemy::followPlayer(float time) {
	sf::Vector2f diff = { abs(m_player->getPosition().x - m_pos.x), abs(m_player->getPosition().y - m_pos.y) };
	if (diff.x >= ENEMY_ATTACK_RANGE || diff.y >= ENEMY_ATTACK_RANGE) {
		sf::Vector2f player_pos = m_player->getPosition();
		sf::Vector2f direction = player_pos - m_pos;
		direction /= sqrt(direction.x * direction.x + direction.y * direction.y);
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
	sf::Vector2f diff = { abs(m_player->getPosition().x - m_pos.x), abs(m_player->getPosition().y - m_pos.y) };
	if ((diff.x <= ENEMY_ATTACK_RANGE && diff.y <= ENEMY_ATTACK_RANGE) && !m_attack_cooldown->isRunning()) {
		sf::Vector2f player_pos = m_player->getPosition();
		sf::Vector2f direction = player_pos - m_pos;

		direction /= sqrt(direction.x * direction.x + direction.y * direction.y);
		auto new_bullet = std::make_shared<Bullet>(m_bullet_texture, m_pos, direction);
		new_bullet->updateDamage(ENEMY_BULLET_DAMAGE / BULLET_DEFAULT_DAMAGE);
		m_bullets.push_back(new_bullet);
		m_attack_cooldown->Start();
	}
}

RangeEnemy::RangeEnemy(const sf::Texture& textures, const sf::Texture& bullet_texture, sf::Vector2f pos, float attack_cooldown, float speed, float damage, float health) {
	m_pos = pos;
	m_speed = speed;
	m_damage = damage;
	m_health = health;
	m_bullet_texture = bullet_texture;

	m_attack_cooldown = std::make_unique<game_engine::Timer>(attack_cooldown);
	m_run_animation = std::make_unique<game_engine::Animation>(textures, 57, 61, 42, 31, 8, ANIMATION_SPEED, 150);
}

void RangeEnemy::Update(float time) {
	Enemy::Update(time);

	m_sprite->setColor(sf::Color::Green);

	for (auto bullet : m_bullets) {
		bullet->Update(time);
		if (bullet->checkCollisionWithCharacter(m_player) || bullet->checkCollisionWithMapBorders()) {
			m_bullets.erase(std::find(m_bullets.begin(), m_bullets.end(), bullet));
			break;
		}
	}
}
