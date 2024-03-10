#include "../include/Enemies/Enemy.h"
#include "../include/Engine/Animation.h"
#include "../include/Engine/Constants.h"
#include "../include/Engine/Timer.h"
#include "../include/Player.h"

void Enemy::followPlayer(float time) {
    if (!m_sprite.getGlobalBounds().intersects(m_player->getSprite().getGlobalBounds())) {
        sf::Vector2f player_pos = m_player->getPosition();
        sf::Vector2f direction = player_pos - m_pos;
        direction /= sqrt(direction.x * direction.x + direction.y * direction.y);
        m_pos.x += direction.x * m_speed * time;
        m_pos.y += direction.y * m_speed * time;
    }
}

void Enemy::updateDirection() {
    if (m_player->getPosition().x > m_pos.x) {
        m_direction = Direction::RIGHT;
    }
    else {
        m_direction = Direction::LEFT;
    }
}

void Enemy::attackIfCanAttack() {
    if (m_sprite.getGlobalBounds().intersects(m_player->getSprite().getGlobalBounds()) && !m_attack_cooldown->isRunning()) {
        m_player->takeDamage(m_damage);
        m_attack_cooldown->Start();
    }
}

Enemy::Enemy(const sf::Texture& textures, sf::Vector2f pos, float attack_cooldown, float speed, float damage, float health) {
    m_pos = pos;
    m_speed = speed;
    m_damage = damage;
    m_health = health;

    m_attack_cooldown = new Timer(attack_cooldown);
    m_run_animation = new Animation(textures, 57, 61, 42, 31, 8, ANIMATION_SPEED, 150);
}

Enemy::~Enemy() {
    delete m_attack_cooldown;
}

void Enemy::Update(float time) {
    if (m_player) {
        followPlayer(time);
        updateDirection();
        attackIfCanAttack();
    }

    m_sprite = m_run_animation->Tick(time, m_direction != Direction::RIGHT);

    m_sprite.setScale(1.3, 1.3);
    m_sprite.setPosition(m_pos);
}

void Enemy::setPlayer(Player* player) {
    m_player = player;
}
