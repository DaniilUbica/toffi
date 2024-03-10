#include "../include/UI/HealthBar.h"

HealthBar::HealthBar(sf::Vector2f size, sf::Vector2f pos, float health, sf::Color border_color,
    sf::Color background_color, sf::Color health_color, bool is_static, sf::Vector2f parent_size) {

    m_size = size;
    m_pos = sf::Vector2f(pos.x + m_parent_size.x / 2 - m_size.x / 2, pos.y - m_size.y - m_parent_offset);
    m_parent_size = parent_size;
    m_health = health;
    m_is_static = is_static;

    sf::Vector2f border_size = m_size;
    m_size -= sf::Vector2f(m_border_size * 2, m_border_size * 2);
    sf::Vector2f border_pos = m_pos;
    m_pos += sf::Vector2f(m_border_size * 2, m_border_size * 2);

    m_border.setPosition(border_pos);
    m_background.setPosition(m_pos);
    m_health_bar.setPosition(m_pos);

    m_border.setSize(border_size);
    m_border.setFillColor(border_color);

    m_background.setSize(m_size);
    m_background.setFillColor(background_color);

    m_health_bar.setFillColor(health_color);
    m_health_bar.setSize(m_size);

    m_chunk_size = m_size.x / health;
}

void HealthBar::Update(float health, sf::Vector2f pos) {
    if (!m_is_static) {
        m_pos = sf::Vector2f(pos.x + m_parent_size.x / 2 - m_size.x / 2 - m_border_size, pos.y - m_size.y - m_parent_offset);

        sf::Vector2f border_pos = m_pos;
        m_pos += sf::Vector2f(m_border_size, m_border_size);

        m_border.setPosition(border_pos);
        m_background.setPosition(m_pos);
        m_health_bar.setPosition(m_pos);
    }

    sf::Vector2f new_size;
    if (health > 0) {
        new_size = sf::Vector2f(m_chunk_size * health, m_size.y);
    }
    else {
        new_size = sf::Vector2f(0.0, m_size.y);
    }

    m_health_bar.setSize(new_size);
}

void HealthBar::Draw(sf::RenderWindow& window) {
    window.draw(m_border);
    window.draw(m_background);
    window.draw(m_health_bar);
}
