#include "Pickables/BulletWave.h"
#include "Pickables/Heal.h"
#include "Player.h"
#include "Bullet.h"
#include "Engine/Constants.h"
#include "Weapon/RangeWeapon.h"

BulletWave::BulletWave(const sf::Texture &texture, sf::Vector2f pos) {
	m_pos = pos;
	m_sprite.setTexture(texture);
	m_sprite.setPosition(m_pos);
}

void BulletWave::onPicked() {
	if (m_picked) {
		return;
	}

	Pickable::commonPicked();

	for (int angle = 0; angle < 360; angle += BULLET_WAVE_BULLETS_SPACING) {
		float radians = float(angle) * PI / 180.f;
		sf::Vector2f direction = { std::cos(radians), std::sin(radians) };

		auto new_bullet = std::make_shared<Bullet>(m_bullet_texture, m_player->getPosition(), direction);
		new_bullet->updateDamage(BULLET_WAVE_DAMAGE / BULLET_DEFAULT_DAMAGE);
		auto weapon = m_player->getWeapon();

		if (auto range_weapon = std::dynamic_pointer_cast<RangeWeapon>(weapon)) {
			range_weapon->shootConcreteBullet(new_bullet);
		}
	}
}

void BulletWave::setPlayer(std::shared_ptr<Player> player) {
	m_player = player;
}
