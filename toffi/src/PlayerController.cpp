#include "Engine/PlayerController.h"
#include "Engine/Constants.h"
#include "Player.h"

bool PlayerController::controller_created = false;

PlayerController::PlayerController() {
    if (controller_created) {
        throw std::logic_error("Only one instance of PlayerController is allowed.");
    }
    controller_created = true;
}

void PlayerController::controllPlayer(Player* player, float time) {
    sf::Vector2f updated_pos = player->getPosition();

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        updated_pos.x -= PLAYER_SPEED * time;
        player->setState(State::RUN);
        player->setDirection(Direction::LEFT);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        updated_pos.x += PLAYER_SPEED * time;
        player->setState(State::RUN);
        player->setDirection(Direction::RIGHT);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        updated_pos.y -= PLAYER_SPEED * time;
        player->setState(State::RUN);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        updated_pos.y += PLAYER_SPEED * time;
        player->setState(State::RUN);
    }

    player->setPosition(updated_pos);
}
