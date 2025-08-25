#pragma once

#include <SFML/Graphics.hpp>
#include "Animation.h"
class Animation;
class HealthBar;

enum class Direction : bool {
	LEFT = 0,
	RIGHT = 1
};

class Character {
protected:
	float		                m_health;
	float		                m_speed;
	sf::Vector2f                m_size;
	sf::Vector2f                m_pos;
    std::shared_ptr<sf::Sprite> m_sprite;
	std::unique_ptr<Animation>  m_run_animation;
	std::shared_ptr<HealthBar>  m_health_bar;
	Direction                   m_direction = Direction::RIGHT;

public:
	virtual ~Character() = default;

	virtual void Update(float time) = 0;
	virtual void takeDamage(float damage);
    virtual void addHP(float health);

	void setPosition(sf::Vector2f& pos);
	void setDirection(Direction direction);

	float getHP() const;
	sf::Vector2f getSize() const;
	sf::Vector2f getPosition() const;
    std::shared_ptr<sf::Sprite> getSprite() const;
	Direction getDirection() const;
	std::shared_ptr<HealthBar> getHealthBar() const;
};
