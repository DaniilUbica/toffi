#include "Enemies/EnemiesManager.h"
#include "Enemies/Enemy.h"
#include "Engine/Constants.h"
#include "Engine/Timer.h"
#include "Player.h"

EnemiesManager::EnemiesManager() {
    m_respawn_timer = std::make_unique<Timer>(ENEMY_RESPAWN_TIMER);
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

    if ((abs(start_x - m_player->getPosition().x) > ENEMY_SPAWN_RANGE ||
        abs(start_y - m_player->getPosition().y) > ENEMY_SPAWN_RANGE) && !m_respawn_timer->isRunning()) {
		auto enemy = std::make_shared<Enemy>(m_enemies_textures[texture_index], sf::Vector2f(start_x, start_y),
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

void EnemiesManager::addTexture(const sf::Texture& texture) {
    m_enemies_textures.push_back(texture);
}

std::vector<std::shared_ptr<Enemy>> EnemiesManager::getEnemies() const {
    return m_enemies;
}

std::vector<std::shared_ptr<Character>> EnemiesManager::getCharacters() const {
	std::vector<std::shared_ptr<Character>> chars;

    for (auto& e : m_enemies) {
        chars.push_back(std::dynamic_pointer_cast<Character>(e));
    }

    return chars;
}
