#pragma once

#include <SFML/Graphics.hpp>

class Animation;

enum class Direction : bool {
	LEFT = 0,
	RIGHT = 1
};

class Character {
protected:
	float		 m_health;
	float		 m_speed;
	sf::Vector2f m_size;
	sf::Vector2f m_pos;
	sf::Sprite   m_sprite;
	Animation*   m_run_animation;
	Direction    m_direction = Direction::RIGHT;

public:
	virtual ~Character();

	virtual void Update(float time) = 0;
	virtual void takeDamage(float damage);

	void setPosition(sf::Vector2f& pos);
	void setDirection(Direction direction);

	float getHP();
	sf::Vector2f getSize();
	sf::Vector2f getPosition();
	sf::Sprite getSprite();
	Direction getDirection();
};