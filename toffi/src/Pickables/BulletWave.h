#pragma once

#include "Engine/Base/Pickable.h"

#include <cmath>

class Player;
class Bullet;

class BulletWave : public game_engine::Pickable {
private:
	game_engine::primitives::Texture m_bullet_texture;

public:
	BulletWave(std::shared_ptr<game_engine::Character> character, const game_engine::primitives::Texture& texture, game_engine::primitives::Vector2f pos);

	virtual void onPicked() override;

	void setBulletTexture(const game_engine::primitives::Texture& bullet_texture) { m_bullet_texture = bullet_texture; };
};

