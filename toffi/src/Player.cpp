#include "../include/Player.h"
#include "../include/Engine/PlayerController.h"
#include "../include/Engine/Animation.h"
#include "../include/Engine/Constants.h"
#include "../include/UI/HealthBar.h"
#include "../include/Weapon.h"

inline float distance(sf::Vector2f v1, sf::Vector2f v2) {
    return std::sqrt((v1.x - v2.x) * (v1.x - v2.x) + (v1.y - v2.y) * (v1.y - v2.y));
}

inline bool compareDistance(sf::Vector2f v1, sf::Vector2f v2, sf::Vector2f target) {
    return distance(v1, target) < distance(v2, target);
}

inline bool isInAttackRange(sf::Vector2f pos, Character* character, float range) {
    sf::Vector2f char_pos = character->getPosition();

    if (abs(char_pos.x - pos.x) <= range || abs(char_pos.y - pos.y) <= range) {
        return true;
    }

    return false;
}

Player::Player(std::map<State, sf::Texture>& texture, sf::Vector2f start_pos, float health) {
    m_pos = start_pos;
    m_size = sf::Vector2f(SPRITE_SIZE, SPRITE_SIZE);
    m_health = health;
    m_health_bar = new HealthBar(sf::Vector2f(30.0, 12.0), m_pos, m_health, sf::Color::Cyan, sf::Color::Magenta, sf::Color::Red, false);

    m_controller = new PlayerController();
    m_idle_animation = new Animation(texture[State::IDLE], 66, 0, 58, 53, 6, ANIMATION_SPEED, 192);
    m_run_animation = new Animation(texture[State::RUN], 66, 0, 58, 53, 6, ANIMATION_SPEED, 193);
}

Player::~Player() {
    delete m_controller;
    delete m_idle_animation;
    delete m_run_animation;
    delete m_weapon;
    delete m_health_bar;
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

    m_sprite.setPosition(m_pos);
}

void Player::attackEnemies(float time, std::vector<Character*>& characters) {
    if (m_weapon) {
        m_weapon->updateAttackSpeed(m_attack_speed_scale);
        if (!characters.empty()) {
            auto nearest = std::min_element(characters.begin(), characters.end(), [this](Character* c1, Character* c2) {
                return compareDistance(c1->getPosition(), c2->getPosition(), m_pos);
            });

            if (nearest != characters.end()) {
                sf::Vector2f nearest_character_pos = (*nearest)->getPosition();
                sf::Vector2f direction = nearest_character_pos - m_pos;
                direction /= sqrt(direction.x * direction.x + direction.y * direction.y);
                m_weapon->Update(time, m_pos, characters);
                if (isInAttackRange(m_pos, *nearest, PLAYER_START_ATTACK_RANGE * m_attack_range_scale)) {
                    m_weapon->Shoot(direction);
                }
            }
        }
    }
    else {
        throw std::logic_error("m_weapon is NULL, maybe you didn't call 'initWeapon()'?");
    }
}

void Player::initWeapon(sf::Texture& bullet_texture, float damage_scale) {
    m_weapon = new Weapon(bullet_texture, m_pos, damage_scale, PLAYER_START_ATTACK_SPEED);
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

Weapon* Player::getWeapon() {
    return m_weapon;
}
