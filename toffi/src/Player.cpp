#include "../include/Player.h"
#include "../include/Engine/PlayerController.h"
#include "../include/Engine/Animation.h"
#include "../include/Engine/Constants.h"

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