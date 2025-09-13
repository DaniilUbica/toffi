#include "Enemies/Enemy.h"
#include "Engine/Animation/Animation.h"
#include "Engine/Particles/ParticleSystem.h"
#include "Pickables/PickableSpawner.h"
#include "Constants.h"
#include "Engine/Core/Timer.h"
#include "Player/Player.h"

void Enemy::followPlayer(float time) {
    if (!m_sprite->getGlobalBounds().intersects(m_player->getSprite()->getGlobalBounds())) {
        game_engine::primitives::Vector2f player_pos = m_player->getPosition();
        game_engine::primitives::Vector2f direction = player_pos - m_pos;
        direction /= static_cast<float>(sqrt(direction.x * direction.x + direction.y * direction.y));
        m_pos.x += direction.x * m_speed * time;
        m_pos.y += direction.y * m_speed * time;
    }
}

void Enemy::updateDirection() {
    if (m_player->getPosition().x > m_pos.x) {
        m_direction = game_engine::Direction::RIGHT;
    }
    else {
        m_direction = game_engine::Direction::LEFT;
    }
}

void Enemy::attackIfCanAttack() {
    if (m_sprite->getGlobalBounds().intersects(m_player->getSprite()->getGlobalBounds()) && !m_attack_cooldown->isRunning()) {
        m_player->takeDamage(m_damage);
        m_attack_cooldown->Start();
    }
}

Enemy::Enemy(const game_engine::primitives::Texture& textures, game_engine::primitives::Vector2f pos, float attack_cooldown, float speed, float damage, float health) : game_engine::Character(textures) {
    m_pos = pos;
    m_speed = speed;
    m_damage = damage;
    m_health = health;
    m_sprite = std::make_shared<game_engine::primitives::Sprite>(textures);

    m_attack_cooldown = std::make_unique<game_engine::Timer>(attack_cooldown);
    m_run_animation = std::make_unique<game_engine::Animation>(textures, 57, 61, 42, 31, 8, ANIMATION_SPEED, 150);
}

Enemy::~Enemy() {
    PickableSpawner::instance()->spawnPickable(m_pos, PickableType::HEAL);
    PickableSpawner::instance()->spawnPickable(m_pos, PickableType::BULLET_WAVE);
    game_engine::ParticleSystem::instance()->burstingBubble(m_pos + m_size / 2.f, m_texture);
}

void Enemy::Update(float time) {
    if (m_player) {
        followPlayer(time);
        updateDirection();
        attackIfCanAttack();
    }

    m_sprite = m_run_animation->Tick(time, m_direction != game_engine::Direction::RIGHT);

    m_sprite->setScale({ 1.3, 1.3 });
    m_sprite->setPosition(m_pos);
}

void Enemy::setPlayer(std::shared_ptr<Player> player) {
    m_player = player;
}
