#pragma once

#include "Engine/Base/Pickable.h"

#include <cmath>

class Player;
class Bullet;

class BulletWave : public game_engine::Pickable {
private:
	std::shared_ptr<Player> m_player;
	sf::Texture m_bullet_texture;

public:
	BulletWave(const sf::Texture& texture, sf::Vector2f pos);

	virtual void onPicked() override;

	void setPlayer(std::shared_ptr<Player> player);
	void setBulletTexture(const sf::Texture& bullet_texture) { m_bullet_texture = bullet_texture; };
};

