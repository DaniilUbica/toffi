#pragma once

#include "Primitives/RenderWindow/RenderWindow.hpp"
#include "Primitives/View/View.hpp"

class Player;

class ViewController {
private:
    std::shared_ptr<Player> m_player;
	std::unique_ptr<game_engine::primitives::View> m_view;
public:
    ViewController(std::shared_ptr<Player> player);
    ~ViewController() = default;

    void Update(float time, game_engine::primitives::RenderWindow& window);
};

