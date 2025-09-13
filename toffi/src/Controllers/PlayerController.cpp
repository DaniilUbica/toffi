#include "PlayerController.h"
#include "Constants.h"
#include "Player/Player.h"

#include <SFML/Graphics.hpp>

bool PlayerController::controller_created = false;

PlayerController::PlayerController() {
    if (controller_created) {
        throw std::logic_error("Only one instance of PlayerController is allowed.");
    }
    controller_created = true;
}

void PlayerController::controllPlayer(Player* player, float time) {
    game_engine::primitives::Vector2f updated_pos = player->getPosition();

//    if (game_engine::primitives::Keyboard::isKeyPressed(game_engine::primitives::Keyboard::Key::A)) {
//        updated_pos.x -= PLAYER_SPEED * time;
//        player->setState(State::RUN);
//        player->setDirection(game_engine::Direction::LEFT);
//    }
//    else if (game_engine::primitives::Keyboard::isKeyPressed(game_engine::primitives::Keyboard::Key::D)) {
//        updated_pos.x += PLAYER_SPEED * time;
//        player->setState(State::RUN);
//        player->setDirection(game_engine::Direction::RIGHT);
//    }
//    if (game_engine::primitives::Keyboard::isKeyPressed(game_engine::primitives::Keyboard::Key::W)) {
//        updated_pos.y -= PLAYER_SPEED * time;
//        player->setState(State::RUN);
//    }
//    else if (game_engine::primitives::Keyboard::isKeyPressed(game_engine::primitives::Keyboard::Key::S)) {
//        updated_pos.y += PLAYER_SPEED * time;
//        player->setState(State::RUN);
//    }

    player->setPosition(updated_pos);
}
