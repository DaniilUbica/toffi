#include "Engine/PickableSpawner.h"
#include "Engine/Pickable.h"
#include "Engine/Character.h"
#include "Engine/Constants.h"
#include "Pickables/Heal.h"
#include "Player.h"

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
		if (m_player->getSprite().getGlobalBounds().intersects(pickable->getSprite().getGlobalBounds())) {
			pickable->onPicked();
		}
	}
}

void PickableSpawner::spawnPickable(sf::Vector2f pos, PickableType type) {
	std::srand(static_cast<unsigned int>(std::time(nullptr)));
	int value = std::rand() % 100;

	switch (type) {
		case PickableType::HEAL:
		{
			if (value < HEAL_SPAWN_CHANCE) {
				auto newPickable = std::make_shared<Heal>(m_pickable_textures[PickableType::HEAL], pos);
				newPickable->setPlayer(m_player);
				m_pickables.push_back(std::dynamic_pointer_cast<Pickable>(newPickable));
			}
			break;
		}
		default:
			break;
	}
}
