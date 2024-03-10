#pragma once

#include <vector>
#include <SFML/Graphics.hpp>

class Enemy;
class Timer;
class Player;
class Character;

class EnemiesManager {
private:
    std::vector<Enemy*>      m_enemies;
    Timer*                   m_respawn_timer;
    Player*                  m_player;
    std::vector<sf::Texture> m_enemies_textures;
    float                    m_enemies_hp_scale = 1.0;

    void spawnEnemy();
    void removeEnemy();

public:
    EnemiesManager();
    ~EnemiesManager();

    void Update(float time);
    void setPlayer(Player* player);
    void addTexture(const sf::Texture& texture);

    std::vector<Enemy*> getEnemies() const;
    std::vector<Character*> getCharacters() const;
};

