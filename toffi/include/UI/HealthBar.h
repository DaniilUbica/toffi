#pragma once

#include <SFML/Graphics.hpp>

class HealthBar {
private:
    sf::RectangleShape m_border;
    sf::RectangleShape m_background;
    sf::RectangleShape m_health_bar;
    sf::Vector2f       m_pos;
    sf::Vector2f       m_size;
    float              m_health;
    float              m_chunk_size;
    float              m_border_size = 2.0;
    bool               m_is_static;

public:
    HealthBar(sf::Vector2f size, sf::Vector2f pos, float health, sf::Color border_color,
        sf::Color background_color, sf::Color health_color, bool is_static);

    void Update(float health, sf::Vector2f pos);
    void Draw(sf::RenderWindow& window);
};

