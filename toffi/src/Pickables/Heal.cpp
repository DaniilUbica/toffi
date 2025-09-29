#include "Pickables/Heal.h"
#include "Player/Player.h"
#include "Constants.h"

Heal::Heal(std::shared_ptr<game_engine::Character> character, const game_engine::primitives::Texture& texture, game_engine::primitives::Vector2f pos) : game_engine::Pickable(character, texture, pos) {
    m_sprite->setPosition(m_pos);
}

void Heal::onPicked() {
	if (m_picked) {
		return;
	}

	Pickable::commonPicked();

    m_character->addHP(HEAL_DEFAULT_VALUE);
}
