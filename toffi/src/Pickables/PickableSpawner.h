#pragma once

#include "Primitives/Texture/Texture.hpp"

#include <map>

namespace game_engine {
    class Character;
    class Pickable;
}
class Player;

enum class PickableType {
	HEAL,
	BULLET_WAVE
};

class PickableSpawner {
private:
	static PickableSpawner*                             m_instance;
	std::map<PickableType, game_engine::primitives::Texture> m_pickable_textures;
	std::vector<std::shared_ptr<game_engine::Pickable>> m_pickables;
	std::shared_ptr<Player>                             m_player;

	PickableSpawner() = default;
	void checkCollisionsWithPlayer();

public:
	PickableSpawner(const PickableSpawner&) = delete;
	void operator=(const PickableSpawner&) = delete;
	~PickableSpawner();

	static PickableSpawner* instance();
	void Update();
	void spawnPickable(game_engine::primitives::Vector2f pos, PickableType type);
	void addPickableTexture(PickableType type, const game_engine::primitives::Texture& texture);

	std::vector<std::shared_ptr<game_engine::Pickable>> getPickables() const { return m_pickables; };

	void setPlayer(std::shared_ptr<Player> player) { m_player = player; };
};
