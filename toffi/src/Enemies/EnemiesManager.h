#pragma once

#include <vector>

#include "Primitives/Texture/Texture.hpp"
#include "Primitives/RenderWindow/RenderWindow.hpp"

class Enemy;
class Player;

namespace game_engine {
    class Timer;
    class Character;
}

class EnemiesManager {
private:
    std::vector<std::shared_ptr<Enemy>>           m_enemies;
	std::unique_ptr<game_engine::Timer>           m_respawn_timer;
	std::shared_ptr<Player>                       m_player;
    std::vector<game_engine::primitives::Texture> m_enemies_textures;
	game_engine::primitives::Texture              m_bullet_texture;
    float                                         m_enemies_hp_scale = 1.0;

    void spawnEnemy();
    void removeEnemy();

public:
    EnemiesManager();
    ~EnemiesManager() = default;

    void Update(float time);
    void addTexture(const game_engine::primitives::Texture& texture);
	void drawBullets(game_engine::primitives::RenderWindow& window);

	void setPlayer(std::shared_ptr<Player> player);
	void setBulletTexture(const game_engine::primitives::Texture& bullet_texture);

    std::vector<std::shared_ptr<Enemy>> getEnemies() const;
    std::vector<std::shared_ptr<game_engine::Character>> getCharacters() const;
};

