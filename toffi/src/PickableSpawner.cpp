#include "PickableSpawner.h"
#include "Pickable.h"
#include "Character.h"
#include "Constants.h"
#include "Pickables/Heal.h"
#include "Pickables/BulletWave.h"
#include "Player.h"
#include "Textures.h"

PickableSpawner* PickableSpawner::m_instance = nullptr;

PickableSpawner::~PickableSpawner() {
	m_instance = nullptr;
}

PickableSpawner* PickableSpawner::instance() {
	if (!m_instance) {
		m_instance = new PickableSpawner();
	}

	return m_instance;
}

void PickableSpawner::Update() {
	for (auto pickable : m_pickables) {
		if (pickable && pickable->getPicked()) {
			m_pickables.erase(std::find(m_pickables.begin(), m_pickables.end(), pickable));
		}
	}

	checkCollisionsWithPlayer();
}

void PickableSpawner::addPickableTexture(PickableType type, const sf::Texture& texture) {
	auto t = texture;
	m_pickable_textures[type] = t;
}

void PickableSpawner::checkCollisionsWithPlayer() {
	for (auto pickable : m_pickables) {
		if (m_player->getSprite()->getGlobalBounds().findIntersection(pickable->getSprite()->getGlobalBounds())) {
			pickable->onPicked();
		}
	}
}

void PickableSpawner::spawnPickable(sf::Vector2f pos, PickableType type) {
	std::srand(static_cast<unsigned int>(std::time(nullptr)));

	switch (type) {
		case PickableType::HEAL:
		{
			int value = std::rand() % 100;
			if (value < HEAL_SPAWN_CHANCE) {
				auto new_pickable = std::make_shared<Heal>(m_pickable_textures[PickableType::HEAL], pos);
				new_pickable->setPlayer(m_player);
				m_pickables.push_back(std::dynamic_pointer_cast<Pickable>(new_pickable));
			}
			break;
		}
		case PickableType::BULLET_WAVE:
		{
			int value = std::rand() % 100;
			if (value < BULLET_WAVE_SPAWN_CHANCE) {
				auto new_pickable = std::make_shared<BulletWave>(m_pickable_textures[PickableType::BULLET_WAVE], pos);
				new_pickable->setBulletTexture(TextureHolder::instance()->bullet_texture());
				new_pickable->setPlayer(m_player);
				m_pickables.push_back(std::dynamic_pointer_cast<Pickable>(new_pickable));
			}
		}
		default:
			break;
	}
}
