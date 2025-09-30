#include "Enemies/EnemiesManager.h"

#include "Enemies/Enemy.h"
#include "Enemies/RangeEnemy.h"
#include "Constants.h"
#include "Engine/Core/Timer.h"
#include "Player/Player.h"
#include "Weapon/Bullet.h"

#include "Engine/TimersHolder.hpp"

EnemiesManager::EnemiesManager() {
    m_respawn_timer = game_engine::TimersHolder::createTimer(ENEMY_RESPAWN_TIMER);
}

void EnemiesManager::Update(float time) {
    spawnEnemy();

    for (auto& e : m_enemies) {
        e->Update(time);
    }

    removeEnemy();
}

void EnemiesManager::spawnEnemy() {
    float texture_index = rand() % m_enemies_textures.size() - 0;
    float start_x = rand() % int(ENEMY_MAXIMAL_SPAWN_POS_X) - ENEMY_MINIMAL_SPAWN_POS_X;
    float start_y = rand() % int(ENEMY_MAXIMAL_SPAWN_POS_Y) - ENEMY_MINIMAL_SPAWN_POS_Y;
	int spawn_range_enemy = rand() % 2 - 0;

    if ((abs(start_x - m_player->getPosition().x) > ENEMY_SPAWN_RANGE ||
        abs(start_y - m_player->getPosition().y) > ENEMY_SPAWN_RANGE) && !m_respawn_timer->isRunning()) {
		auto enemy = spawn_range_enemy ? std::make_shared<RangeEnemy>(m_enemies_textures[texture_index], m_bullet_texture, game_engine::primitives::Vector2f(start_x, start_y),
            ENEMY_ATTACK_COOLDOWN, ENEMY_SPEED, ENEMY_DAMAGE, ENEMY_START_HP * m_enemies_hp_scale) : std::make_shared<Enemy>(m_enemies_textures[texture_index], game_engine::primitives::Vector2f(start_x, start_y),
																																  ENEMY_ATTACK_COOLDOWN, ENEMY_SPEED, ENEMY_DAMAGE, ENEMY_START_HP * m_enemies_hp_scale);
        enemy->setPlayer(m_player);
        m_enemies.push_back(enemy);
        m_respawn_timer->Start();
    }
    else if (!m_respawn_timer->isRunning()) {
        return;
    }
}

void EnemiesManager::removeEnemy() {
    auto dead_enemy_iter = std::find_if(m_enemies.begin(), m_enemies.end(), [](std::shared_ptr<Enemy> enemy) {
        return enemy->getHP() <= 0;
    });

    if (dead_enemy_iter != m_enemies.end()) {
		*dead_enemy_iter = nullptr;
        m_enemies.erase(dead_enemy_iter);
    }
}

void EnemiesManager::setPlayer(std::shared_ptr<Player> player) {
    m_player = player;
}

void EnemiesManager::setBulletTexture(const game_engine::primitives::Texture& bullet_texture) {
	m_bullet_texture = bullet_texture;
}

void EnemiesManager::addTexture(const game_engine::primitives::Texture& texture) {
    m_enemies_textures.push_back(texture);
}

void EnemiesManager::drawBullets(game_engine::primitives::RenderWindow& window) {
	for (auto enemy : m_enemies) {
		if (auto range_enemy = std::dynamic_pointer_cast<RangeEnemy>(enemy)) {
			for (auto bullet : range_enemy->getBullets()) {
				window.draw(*bullet->getSprite().get());
			}
		}
	}
}

std::vector<std::shared_ptr<Enemy>> EnemiesManager::getEnemies() const {
    return m_enemies;
}

std::vector<std::shared_ptr<game_engine::Character>> EnemiesManager::getCharacters() const {
	std::vector<std::shared_ptr<game_engine::Character>> chars;

    for (auto& e : m_enemies) {
        chars.push_back(std::dynamic_pointer_cast<game_engine::Character>(e));
    }

    return chars;
}
