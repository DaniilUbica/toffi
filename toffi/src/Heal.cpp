#include "Pickables/Heal.h"
#include "Player.h"
#include "Engine/Constants.h"

Heal::Heal(const sf::Texture &texture, sf::Vector2f pos) {
    m_pos = pos;
    m_sprite.setTexture(texture);
    m_sprite.setPosition(m_pos);
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
