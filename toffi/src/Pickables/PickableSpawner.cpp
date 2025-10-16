#include "PickableSpawner.h"
#include "Engine/Base/Pickable.h"
#include "Engine/Base/Character.h"
#include "Constants.h"
#include "Pickables/Heal.h"
#include "Pickables/BulletWave.h"
#include "Pickables/Currency.h"
#include "Player/Player.h"
#include "Textures/Textures.h"

PickableSpawner::PickableSpawner() {
    m_attractionsManager = std::make_unique<game_engine::physics::ObjectsAttractionManager>();
}

void PickableSpawner::Update(float time) {
    for (auto pickable : m_pickables) {
        pickable->Update(time);
    }

    for (auto it = m_pickables.begin(); it != m_pickables.end();) {
        if (*it && (*it)->picked()) {
            m_attractionsManager->removeAttractionObject(*it);
            it = m_pickables.erase(it);
        }
        else {
            ++it;
        }
    }

    m_attractionsManager->Update(time);
	checkCollisionsWithPlayer();
}

void PickableSpawner::addPickableTexture(PickableType type, const game_engine::primitives::Texture& texture) {
	auto t = texture;
	m_pickable_textures[type] = t;
}

void PickableSpawner::checkCollisionsWithPlayer() {
	for (auto pickable : m_pickables) {
		if (m_player->getSprite()->getGlobalBounds().intersects(pickable->getSprite()->getGlobalBounds())) {
			pickable->onPicked();
		}
	}
}

void PickableSpawner::spawnPickable(game_engine::primitives::Vector2f pos, PickableType type) {
	std::srand(static_cast<unsigned int>(std::time(nullptr)));

	switch (type) {
		case PickableType::HEAL:
		{
			int value = std::rand() % 100;
			if (value < HEAL_SPAWN_CHANCE) {
                const auto new_pickable = std::make_shared<Heal>(m_player, m_pickable_textures[PickableType::HEAL], pos);
				m_pickables.insert(std::dynamic_pointer_cast<game_engine::Pickable>(new_pickable));
			}
			break;
		}
		case PickableType::BULLET_WAVE:
		{
			int value = std::rand() % 100;
			if (value < BULLET_WAVE_SPAWN_CHANCE) {
                const auto new_pickable = std::make_shared<BulletWave>(m_player, m_pickable_textures[PickableType::BULLET_WAVE], pos);
				new_pickable->setBulletTexture(TextureHolder::instance()->bullet_texture());
				m_pickables.insert(std::dynamic_pointer_cast<game_engine::Pickable>(new_pickable));
			}
		}
        case PickableType::CURRENCY:
        {
            int value = std::rand() % 100;
            if (value < CURRENCY_SPAWN_CHANCE) {
                const auto valueToAdd = std::rand() % (CURRENCY_SPAWN_MAX_VALUE - CURRENCY_SPAWN_MIN_VALUE + 1);
                const auto new_pickable = std::make_shared<Currency>(m_player, m_pickable_textures[PickableType::CURRENCY], pos, valueToAdd);
                m_pickables.insert(std::dynamic_pointer_cast<game_engine::Pickable>(new_pickable));
            }
        }
		default:
			break;
	}

    for (const auto& pickable : m_pickables) {
        if (pickable->attractable()) {
            m_attractionsManager->addAttractionObject(pickable);
        }
    }
}

void PickableSpawner::setPlayer(std::shared_ptr<Player> player) {
    m_player = player;
    m_attractionsManager->setTarget(m_player);
}
