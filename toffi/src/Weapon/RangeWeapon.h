#pragma once

#include "Weapon.h"

class RangeWeapon : public Weapon {
private:
	std::vector<std::shared_ptr<Bullet>> m_bullets;
	game_engine::primitives::Texture m_bullet_texture;

    void attackIfCanAttack() override;

public:
	RangeWeapon(const game_engine::primitives::Texture& bullet_texture, game_engine::primitives::Vector2f pos, float damage_scale, float reload_time);
	~RangeWeapon() = default;

	void Update(float time, game_engine::primitives::Vector2f pos, std::vector<std::shared_ptr<game_engine::Character>>& characters, float attack_range) override;
	void shootConcreteBullet(std::shared_ptr<Bullet> bullet);

	std::vector<std::shared_ptr<Bullet>> getBullets() const;
};
