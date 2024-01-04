#include "../include/Enemies/EnemiesManager.h"
#include "../include/Enemies/Enemy.h"
#include "../include/Engine/Constants.h"
#include "../include/Engine/Timer.h"
#include "../include/Player.h"

EnemiesManager::EnemiesManager() {
    m_respawn_timer = new Timer(ENEMY_RESPAWN_TIMER);
}

EnemiesManager::~EnemiesManager() {
    for (auto e : m_enemies) {
        delete e;
    }
    delete m_respawn_timer;
}

void EnemiesManager::Update(float time) {
    spawnEnemy();

    for (auto e : m_enemies) {
        e->Update(time);
    }
}

void EnemiesManager::spawnEnemy() {
    float texture_index = rand() % m_enemies_textures.size() - 0;
    float start_x = rand() % int(ENEMY_MAXIMAL_SPAWN_POS_X) - ENEMY_MINIMAL_SPAWN_POS_X;
    float start_y = rand() % int(ENEMY_MAXIMAL_SPAWN_POS_Y) - ENEMY_MINIMAL_SPAWN_POS_Y;
    if ((abs(start_x - m_player->getPosition().x) > ENEMY_SPAWN_RANGE ||
        abs(start_y - m_player->getPosition().y) > ENEMY_SPAWN_RANGE) && !m_respawn_timer->isRunning()) {
        Enemy* enemy = new Enemy(m_enemies_textures[texture_index], sf::Vector2f(start_x, start_y),
            ENEMY_ATTACK_COOLDOWN, ENEMY_SPEED, ENEMY_DAMAGE);
        enemy->setPlayer(m_player);
        m_enemies.push_back(enemy);
        m_respawn_timer->Start();
    }
    else if (!m_respawn_timer->isRunning()) {
        spawnEnemy();
    }
}

void EnemiesManager::setPlayer(Player* player) {
    m_player = player;
}

void EnemiesManager::addTexture(sf::Texture& texture) {
    m_enemies_textures.push_back(texture);
}

std::vector<Enemy*> EnemiesManager::getEnemies() {
    return m_enemies;
}