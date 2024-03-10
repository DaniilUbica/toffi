#pragma once

#include <SFML/Graphics.hpp>

class Animation;
class HealthBar;

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
	HealthBar*   m_health_bar;
	Direction    m_direction = Direction::RIGHT;

public:
	virtual ~Character();

	virtual void Update(float time) = 0;
	virtual void takeDamage(float damage);

	void setPosition(sf::Vector2f& pos);
	void setDirection(Direction direction);

	float getHP() const;
	sf::Vector2f getSize() const;
	sf::Vector2f getPosition() const;
	sf::Sprite getSprite() const;
	Direction getDirection() const;
	HealthBar* getHealthBar() const;
};