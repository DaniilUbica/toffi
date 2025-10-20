#pragma once

#include "cpplib/singletone.hpp"

#include "Player/Player.h"

class TextureHolder : public game_engine::cpplib::singletone_from_this<TextureHolder> {
private:
	std::map<State, game_engine::primitives::Texture> m_player_textures;
	game_engine::primitives::Texture m_lvl1_border_texture;
	game_engine::primitives::Texture m_lvl1_background_texture;
	game_engine::primitives::Texture m_flying_eye_texture;
	game_engine::primitives::Texture m_spider_texture;
	game_engine::primitives::Texture m_bullet_texture;
    game_engine::primitives::Texture m_sword_texture;
	game_engine::primitives::Texture m_heal_texture;
    game_engine::primitives::Texture m_coin_texture;

public:
	void setTextures();

	std::map<State, game_engine::primitives::Texture> player_textures() const { return m_player_textures; };
	game_engine::primitives::Texture lvl1_border_texture() const { return m_lvl1_border_texture; };
	game_engine::primitives::Texture lvl1_background_texture() const { return m_lvl1_background_texture; };
	game_engine::primitives::Texture flying_eye_texture() const { return m_flying_eye_texture; };
	game_engine::primitives::Texture spider_texture() const { return m_spider_texture; };
	game_engine::primitives::Texture bullet_texture() const { return m_bullet_texture; };
    game_engine::primitives::Texture sword_texture() const { return m_sword_texture; };
	game_engine::primitives::Texture heal_texture() const { return m_heal_texture; };
    game_engine::primitives::Texture coin_texture() const { return m_coin_texture; };
};
