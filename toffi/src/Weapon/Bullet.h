#pragma once

#include "Engine/Base/GameObject.h"

namespace game_engine {
    class Character;
}

class Bullet : public game_engine::GameObject {
private:
    sf::Vector2f m_direction = {};
    float        m_damage = 0.f;
    bool         m_collided = false;

    void commonUpdate(float time);
    bool checkCollisionWithCharacters(std::vector<std::shared_ptr<game_engine::Character>>& characters);
    bool checkCollisionWithCharacter(std::shared_ptr<game_engine::Character> character);
    bool checkCollisionWithMapBorders();

public:
    Bullet(const sf::Texture& texture, sf::Vector2f pos, sf::Vector2f direction);

    void Update(std::vector<std::shared_ptr<game_engine::Character>>& characters, float time);
    void Update(std::shared_ptr<game_engine::Character> characters, float time);
    void updateDamage(float scale);

    bool getCollided() const { return m_collided; };
};

