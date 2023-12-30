#pragma once

#include <SFML/Graphics.hpp>

class Character {
protected:
	float		 m_health;
	float		 m_speed;
	sf::Vector2f m_size;
	sf::Vector2f m_pos;
	sf::Sprite   m_sprite;
public:
	virtual void Update(float time) = 0;
	virtual void takeDamage(float damage);

	void setPosition(sf::Vector2f& pos);

	float getHP();
	sf::Vector2f getSize();
	sf::Vector2f getPosition();
	sf::Sprite getSprite();
};