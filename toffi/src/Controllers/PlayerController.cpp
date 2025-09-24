#include "PlayerController.h"
#include "Primitives/Event.hpp"
#include "Constants.h"
#include "Player/Player.h"

bool PlayerController::controller_created = false;

PlayerController::PlayerController(Player* player) : m_player(player) {
    if (controller_created) {
        throw std::logic_error("Only one instance of PlayerController is allowed.");
    }
    controller_created = true;
}

void PlayerController::controllPlayer(float time) {
    using namespace game_engine::primitives;

    Vector2f updated_pos = m_player->getPosition();

    if (KeyEvent::isKeyPressed(KeyEvent::Key::A)) {
        updated_pos.x -= PLAYER_SPEED * time;
        m_player->setState(State::RUN);
        m_player->setDirection(game_engine::Direction::LEFT);
    }
    else if (KeyEvent::isKeyPressed(KeyEvent::Key::D)) {
        updated_pos.x += PLAYER_SPEED * time;
        m_player->setState(State::RUN);
        m_player->setDirection(game_engine::Direction::RIGHT);
    }
    if (KeyEvent::isKeyPressed(KeyEvent::Key::W)) {
        updated_pos.y -= PLAYER_SPEED * time;
        m_player->setState(State::RUN);
    }
    else if (KeyEvent::isKeyPressed(KeyEvent::Key::S)) {
        updated_pos.y += PLAYER_SPEED * time;
        m_player->setState(State::RUN);
    }

    m_player->setPosition(updated_pos);
}
