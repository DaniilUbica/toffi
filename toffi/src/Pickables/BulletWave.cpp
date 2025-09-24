#include "Pickables/BulletWave.h"
#include "Pickables/Heal.h"
#include "Player/Player.h"
#include "Weapon/Bullet.h"
#include "Constants.h"
#include "Weapon/BulletWaveWeapon.h"

BulletWave::BulletWave(const game_engine::primitives::Texture& texture, game_engine::primitives::Vector2f pos) {
	m_pos = pos;
    m_texture = texture;
    m_sprite = std::make_shared<game_engine::primitives::Sprite>(m_texture);

	m_sprite->setPosition(m_pos);
}

void BulletWave::onPicked() {
	if (m_picked) {
		return;
	}

	Pickable::commonPicked();

    std::vector<std::shared_ptr<Bullet>> bullets;
    for (int angle = 0; angle < 360; angle += BULLET_WAVE_BULLETS_SPACING) {
        float radians = float(angle) * game_engine::PI / 180.f;
        game_engine::primitives::Vector2f direction = { std::cos(radians), std::sin(radians) };

        auto new_bullet = std::make_shared<Bullet>(m_bullet_texture, m_player->getPosition(), direction);
        new_bullet->updateDamage(BULLET_WAVE_DAMAGE / BULLET_DEFAULT_DAMAGE);

        bullets.push_back(new_bullet);
    }

    const auto weapons = m_player->getWeapons();
    std::shared_ptr<BulletWaveWeapon> bullet_wave_weapon = nullptr;
    for (const auto weapon : weapons) {
        if (weapon->getWeaponType() == WeaponType::BULLET_WAVE) {
            bullet_wave_weapon = std::dynamic_pointer_cast<BulletWaveWeapon>(weapon);
            break;
        }
    }

    if (bullet_wave_weapon) {
        bullet_wave_weapon->setBullets(bullets);
    }
}

void BulletWave::setPlayer(std::shared_ptr<Player> player) {
	m_player = player;
}
