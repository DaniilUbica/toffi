#pragma once

#include <SFML/Graphics.hpp>

class Bullet;
class Character;
class Timer;

class Weapon {
private:
    std::vector<Bullet*> m_bullets;
    sf::Texture          m_bullet_texture;
    sf::Vector2f         m_pos;
    Timer*               m_reload_timer;
    float                m_damage_scale;
    float                m_reload_time;

public:
    Weapon(sf::Texture& bullet_texture, sf::Vector2f pos, float damage_scale, float reload_time);
    ~Weapon();

    void Update(float time, sf::Vector2f pos, std::vector<Character*>& characters);
    void Shoot(sf::Vector2f direction);
    void updateAttackSpeed(float scale);

    std::vector<Bullet*> getBullets();
};

