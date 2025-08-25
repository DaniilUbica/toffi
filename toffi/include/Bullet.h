#pragma once

#include "GameObject.h"

class Character;

class Bullet : public GameObject {
private:
    sf::Vector2f m_direction;
    float        m_damage;

public:
    Bullet(const sf::Texture& texture, sf::Vector2f pos, sf::Vector2f direction);

    void Update(float time);
    bool checkCollisionWithCharacters(std::vector<std::shared_ptr<Character>>& characters);
	bool checkCollisionWithCharacter(std::shared_ptr<Character> character);
    bool checkCollisionWithMapBorders();
    void updateDamage(float scale);
};

