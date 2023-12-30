#include "../include/Player.h"
#include "../include/Engine/PlayerController.h"
#include <iostream>
Player::Player(sf::Texture& texture, sf::Vector2f start_pos) {
    m_pos = start_pos;
    m_sprite.setTexture(texture);

    m_controller = new PlayerController();

    m_sprite.setPosition(m_pos);
}

Player::~Player() {
    delete m_controller;
}

void Player::Update(float time) {
    m_state = State::IDLE;
    m_controller->controllPlayer(this, time);

    m_sprite.setPosition(m_pos);
}

void Player::changeDirection() {

}

void Player::setState(State state) {
    m_state = state;
}

void Player::setDirection(Direction direction) {
    m_direction = direction;
}
