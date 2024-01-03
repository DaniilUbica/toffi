#pragma once

#include <SFML/Graphics.hpp>

class Player;

class ViewController {
private:
    Player*   m_player{ nullptr };
    sf::View* m_view{ nullptr };
public:
    ViewController(Player* player);
    ~ViewController();

    void Update(float time, sf::RenderWindow& window);
};

