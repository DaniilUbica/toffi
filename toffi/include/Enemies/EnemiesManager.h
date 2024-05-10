#pragma once

#include <vector>
#include <SFML/Graphics.hpp>

class Enemy;
class Timer;
class Player;
class Character;

class EnemiesManager {
private:
    std::vector<std::shared_ptr<Enemy>> m_enemies;
	std::unique_ptr<Timer>              m_respawn_timer;
	std::shared_ptr<Player>             m_player;
    std::vector<sf::Texture>            m_enemies_textures;
    float                               m_enemies_hp_scale = 1.0;

    void spawnEnemy();
    void removeEnemy();

public:
    EnemiesManager();
    ~EnemiesManager() = default;

    void Update(float time);
    void setPlayer(std::shared_ptr<Player> player);
    void addTexture(const sf::Texture& texture);

    std::vector<std::shared_ptr<Enemy>> getEnemies() const;
    std::vector<std::shared_ptr<Character>> getCharacters() const;
};

