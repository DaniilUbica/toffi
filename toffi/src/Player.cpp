#include "../include/Player.h"
#include "../include/Engine/PlayerController.h"
#include "../include/Engine/Animation.h"
#include "../include/Engine/Constants.h"
#include "../include/Weapon.h"

inline float distance(sf::Vector2f v1, sf::Vector2f v2) {
    return std::sqrt((v1.x - v2.x) * (v1.x - v2.x) + (v1.y - v2.y) * (v1.y - v2.y));
}

inline bool compareDistance(sf::Vector2f v1, sf::Vector2f v2, sf::Vector2f target) {
    return distance(v1, target) < distance(v2, target);
}

Player::Player(std::map<State, sf::Texture>& texture, sf::Vector2f start_pos) {
    m_pos = start_pos;
    m_size = sf::Vector2f(SPRITE_SIZE, SPRITE_SIZE);

    m_controller = new PlayerController();
    m_idle_animation = new Animation(texture[State::IDLE], 66, 0, 58, 53, 6, ANIMATION_SPEED, 192);
    m_run_animation = new Animation(texture[State::RUN], 66, 0, 58, 53, 6, ANIMATION_SPEED, 193);
}

Player::~Player() {
    delete m_controller;
    delete m_idle_animation;
    delete m_run_animation;
    delete m_weapon;
}

void Player::Update(float time) {
    m_state = State::IDLE;
    m_controller->controllPlayer(this, time);

    checkCollisionWithMapBorders();

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
        auto nearest = std::min_element(characters.begin(), characters.end(), [this](Character* c1, Character* c2) {
            return compareDistance(c1->getPosition(), c2->getPosition(), m_pos);
        });

        sf::Vector2f nearest_character_pos = (*nearest)->getPosition();
        sf::Vector2f direction = nearest_character_pos - m_pos;
        direction /= sqrt(direction.x * direction.x + direction.y * direction.y);
        m_weapon->Shoot(direction);
        m_weapon->Update(time, characters);
    }
    else {
        throw std::logic_error("m_weapon is NULL, maybe you didn't call 'initWeapon()'?");
    }
}

void Player::initWeapon(sf::Texture& bullet_texture, float damage_scale) {
    m_weapon = new Weapon(bullet_texture, m_pos, damage_scale);
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