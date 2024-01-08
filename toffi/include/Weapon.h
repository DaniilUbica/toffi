#pragma once

#include <SFML/Graphics.hpp>

class Bullet;
class Character;

class Weapon {
private:
    std::vector<Bullet*> m_bullets;
    sf::Texture          m_bullet_texture;
    sf::Vector2f         m_pos;
    float                m_damage_scale;

public:
    Weapon(sf::Texture& bullet_texture, sf::Vector2f pos, float damage_scale);
    ~Weapon();

    void Update(float time, std::vector<Character*>& characters);
    void Shoot(sf::Vector2f direction);
};

