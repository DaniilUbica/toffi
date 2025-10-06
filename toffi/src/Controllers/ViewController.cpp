#include "ViewController.h"
#include "Constants.h"
#include "Player/Player.h"

ViewController::ViewController() {
    m_view = std::make_unique<game_engine::primitives::View>(game_engine::primitives::FloatRect({0.f, 0.f}, {1.f, 1.f}));
}

std::shared_ptr<ViewController> ViewController::instance() {
    if (const auto sp = s_instance.lock()) {
        return sp;
    }

    const auto sp = std::shared_ptr<ViewController>(new ViewController());
    s_instance = sp;
    
    return sp;
}

void ViewController::Update(float time, game_engine::primitives::RenderWindow& window) {
    const game_engine::primitives::Vector2f player_pos = m_player->getPosition();
    game_engine::primitives::Vector2f view_pos = { player_pos.x - VIEW_WIDTH / 2, player_pos.y - VIEW_HEIGHT / 2 };

    if (player_pos.x - VIEW_WIDTH / 2 <= 0) {
        view_pos.x = 0;
    }
    if (player_pos.x + VIEW_WIDTH / 2 >= game_engine::WORLD_WIDTH + game_engine::SPRITE_SIZE) {
        view_pos.x = game_engine::WORLD_WIDTH - VIEW_WIDTH + game_engine::SPRITE_SIZE;
    }
    if (player_pos.y - VIEW_HEIGHT / 2 <= 0) {
        view_pos.y = 0;
    }
    if (player_pos.y + VIEW_HEIGHT / 2 >= game_engine::WORLD_HEIGHT + game_engine::SPRITE_SIZE) {
        view_pos.y = game_engine::WORLD_HEIGHT - VIEW_HEIGHT + game_engine::SPRITE_SIZE;
    }

    m_view->setCenter({view_pos.x + VIEW_WIDTH/2.f, view_pos.y + VIEW_HEIGHT/2.f});
    m_view->setSize({VIEW_WIDTH, VIEW_HEIGHT});
    window.setView(*m_view);
}
