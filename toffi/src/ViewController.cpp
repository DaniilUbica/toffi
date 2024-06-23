#include "Engine/ViewController.h"
#include "Engine/Constants.h"
#include "Player.h"

ViewController::ViewController(std::shared_ptr<Player> player) {
    m_player = player;
    m_view = std::make_unique<sf::View>(sf::FloatRect(0.f, 0.f, 1.f, 1.f));
}

void ViewController::Update(float time, sf::RenderWindow& window) {
    sf::Vector2f player_pos = m_player->getPosition();
    sf::Vector2f view_pos = { player_pos.x - VIEW_WIDTH / 2, player_pos.y - VIEW_HEIGHT / 2 };

    if (player_pos.x - VIEW_WIDTH / 2 <= 0) {
        view_pos.x = 0;
    }
    if (player_pos.x + VIEW_WIDTH / 2 >= WORLD_WIDTH + SPRITE_SIZE) {
        view_pos.x = WORLD_WIDTH - VIEW_WIDTH + SPRITE_SIZE;
    }
    if (player_pos.y - VIEW_HEIGHT / 2 <= 0) {
        view_pos.y = 0;
    }
    if (player_pos.y + VIEW_HEIGHT / 2 >= WORLD_HEIGHT + SPRITE_SIZE) {
        view_pos.y = WORLD_HEIGHT - VIEW_HEIGHT + SPRITE_SIZE;
    }

    m_view->reset(sf::FloatRect(view_pos.x, view_pos.y, VIEW_WIDTH, VIEW_HEIGHT));
    window.setView(*m_view);
}
