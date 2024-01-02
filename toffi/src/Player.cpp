#include "../include/Player.h"
#include "../include/Engine/PlayerController.h"
#include "../include/Engine/Animation.h"
#include "../include/Engine/Constants.h"

Player::Player(std::map<State, sf::Texture>& texture, sf::Vector2f start_pos) {
    m_pos = start_pos;

    m_controller = new PlayerController();
    m_idle_animation = new Animation(texture[State::IDLE], 66, 0, 58, 53, 6, ANIMATION_SPEED, 192);
    m_run_animation = new Animation(texture[State::RUN], 67, 0, 57, 53, 6, ANIMATION_SPEED, 191);
}

Player::~Player() {
    delete m_controller;
    delete m_idle_animation;
    delete m_run_animation;
}

void Player::Update(float time) {
    m_state = State::IDLE;
    m_controller->controllPlayer(this, time);

    m_sprite = m_idle_animation->Tick(time, m_direction != Direction::RIGHT);
    m_sprite.setPosition(m_pos);
}

void Player::setState(State state) {
    m_state = state;
}

void Player::setDirection(Direction direction) {
    m_direction = direction;
}
