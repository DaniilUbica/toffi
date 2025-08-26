#pragma once

#include <vector>
#include <SFML/Graphics.hpp>

class Enemy;
class Player;

namespace game_engine {
    class Timer;
    class Character;
}

class EnemiesManager {
private:
    std::vector<std::shared_ptr<Enemy>> m_enemies;
	std::unique_ptr<game_engine::Timer> m_respawn_timer;
	std::shared_ptr<Player>             m_player;
    std::vector<sf::Texture>            m_enemies_textures;
	sf::Texture                         m_bullet_texture;
    float                               m_enemies_hp_scale = 1.0;

    void spawnEnemy();
    void removeEnemy();

public:
    EnemiesManager();
    ~EnemiesManager() = default;

    void Update(float time);
    void addTexture(const sf::Texture& texture);
	void drawBullets(sf::RenderWindow& window);

	void setPlayer(std::shared_ptr<Player> player);
	void setBulletTexture(const sf::Texture& bullet_texture);

    std::vector<std::shared_ptr<Enemy>> getEnemies() const;
    std::vector<std::shared_ptr<game_engine::Character>> getCharacters() const;
};

