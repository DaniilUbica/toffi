#pragma once

#include "Enemy.h"

class Bullet;

class RangeEnemy : public Enemy {
private:
	std::vector<std::shared_ptr<Bullet>> m_bullets;
	game_engine::primitives::Texture m_bullet_texture;

	virtual void followPlayer(float time) override;
	virtual void updateDirection() override;
	virtual void attackIfCanAttack() override;

public:
	RangeEnemy(const game_engine::primitives::Texture& textures, const game_engine::primitives::Texture& bullet_texture, game_engine::primitives::Vector2f pos, float attack_cooldown, float speed, float damage, float health);
	~RangeEnemy() = default;

	void Update(float time) override;

	std::vector<std::shared_ptr<Bullet>> getBullets() const { return m_bullets; };
};
