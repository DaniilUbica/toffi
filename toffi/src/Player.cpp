#include "Player.h"
#include "Engine/PlayerController.h"
#include "Engine/Animation.h"
#include "Engine/Constants.h"
#include "UI/HealthBar.h"
#include "Weapon/RangeWeapon.h"
#include "Weapon/MeleeWeapon.h"

inline float distance(sf::Vector2f v1, sf::Vector2f v2) {
    return std::sqrt((v1.x - v2.x) * (v1.x - v2.x) + (v1.y - v2.y) * (v1.y - v2.y));
}

inline bool compareDistance(sf::Vector2f v1, sf::Vector2f v2, sf::Vector2f target) {
    return distance(v1, target) < distance(v2, target);
}

inline bool isInAttackRange(sf::Vector2f pos, std::shared_ptr<Character> character, float range) {
    sf::Vector2f char_pos = character->getPosition();

    if (abs(char_pos.x - pos.x) <= range || abs(char_pos.y - pos.y) <= range) {
        return true;
    }

    return false;
}

Player::Player(const textures_t& texture, sf::Vector2f start_pos, float health) {
    m_pos = start_pos;
    m_health = health;

    m_controller = std::make_unique<PlayerController>();
    m_idle_animation = std::make_unique<Animation>(texture.at(State::IDLE), 66, 0, 58, 53, 6, ANIMATION_SPEED, 192);
    m_run_animation = std::make_unique<Animation>(texture.at(State::RUN), 66, 0, 58, 53, 6, ANIMATION_SPEED, 193);

    m_sprite = m_idle_animation->Tick(1, m_direction != Direction::RIGHT);
    m_size = sf::Vector2f(m_sprite.getTextureRect().width, m_sprite.getTextureRect().height);

    sf::Color health_color(103, 191, 109);
    sf::Color border_color(96, 127, 97);
    sf::Color background_color(196, 97, 86);
    m_health_bar = std::make_unique<HealthBar>(sf::Vector2f(30.0, 9.0), m_pos, m_health, border_color, background_color, health_color, false, m_size);
}

void Player::Update(float time) {
    m_state = State::IDLE;
    m_controller->controllPlayer(this, time);

    checkCollisionWithMapBorders();

    m_health_bar->Update(m_health, m_pos);

    if (m_state == State::RUN) {
        m_sprite = m_run_animation->Tick(time, m_direction != Direction::RIGHT);
    }
    else {
        m_sprite = m_idle_animation->Tick(time, m_direction != Direction::RIGHT);
    }

    m_size = sf::Vector2f(m_sprite.getTextureRect().width, m_sprite.getTextureRect().height);
    m_sprite.setPosition(m_pos);
}

void Player::addHP(float health) {
    m_health += health * m_heal_scale;
}

void Player::attackEnemies(float time, std::vector<std::shared_ptr<Character>>& characters) {
    if (m_weapon) {
        m_weapon->updateAttackSpeed(m_attack_speed_scale);
		m_weapon->Update(time, m_pos, characters, PLAYER_START_ATTACK_RANGE * m_attack_range_scale);
		m_weapon->Attack();
    }
    else {
        throw std::logic_error("m_weapon is NULL, maybe you didn't call 'initWeapon()'?");
    }
}

void Player::initWeapon(WeaponType weapon_type, float damage_scale, const sf::Texture& texture) {
	// todo: mulptiple weapons
	
    if (weapon_type == WeaponType::RANGE) {
        m_weapon = std::make_shared<RangeWeapon>(texture, m_pos, damage_scale, PLAYER_START_ATTACK_SPEED);
    }
    else {
		m_weapon = std::make_shared<MeleeWeapon>(texture, m_pos, damage_scale, PLAYER_START_ATTACK_SPEED);
    }
}

void Player::checkCollisionWithMapBorders() {
    if (m_pos.y >= WORLD_HEIGHT - m_size.y) {
        m_pos.y = WORLD_HEIGHT - m_size.y;
    }
    if (m_pos.y <= SPRITE_SIZE) {
        m_pos.y = SPRITE_SIZE;
    }
    if (m_pos.x >= WORLD_WIDTH - m_size.x) {
        m_pos.x = WORLD_WIDTH - m_size.x;
    }
    if (m_pos.x <= SPRITE_SIZE) {
        m_pos.x = SPRITE_SIZE;
    }
}

void Player::setState(State state) {
    m_state = state;
}

std::shared_ptr<Weapon> Player::getWeapon() const {
    return m_weapon;
}
