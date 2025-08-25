#pragma once

#include <SFML/Graphics.hpp>

class Player;

class ViewController {
private:
    std::shared_ptr<Player>   m_player;
	std::unique_ptr<sf::View> m_view;
public:
    ViewController(std::shared_ptr<Player> player);
    ~ViewController() = default;

    void Update(float time, sf::RenderWindow& window);
};

