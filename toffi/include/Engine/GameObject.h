#pragma once

#include <SFML/Graphics.hpp>

class GameObject {
protected:
	sf::Vector2f                m_size;
	sf::Vector2f                m_pos;
	std::shared_ptr<sf::Sprite> m_sprite;

	GameObject() = default;
    virtual ~GameObject() = default;

public:
    std::shared_ptr<sf::Sprite> getSprite() const;
	sf::Vector2f getPosition() const;
	sf::Vector2f getSize() const;
};

