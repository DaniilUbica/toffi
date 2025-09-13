#include "Pickables/Heal.h"
#include "Player/Player.h"
#include "Constants.h"

Heal::Heal(const game_engine::primitives::Texture& texture, game_engine::primitives::Vector2f pos) {
    m_pos = pos;
    m_texture = texture;
    m_sprite = std::make_shared<game_engine::primitives::Sprite>(m_texture);

    m_sprite->setPosition(m_pos);
}

void Heal::onPicked() {
	if (m_picked) {
		return;
	}

	Pickable::commonPicked();

    m_player->addHP(HEAL_DEFAULT_VALUE);
}

void Heal::setPlayer(std::shared_ptr<Player> player) { 
    m_player = player;
}
