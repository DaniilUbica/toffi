#pragma once

#include <SFML/Graphics.hpp>

#include "Player.h"

class TextureHolder {

private:
	std::map<State, sf::Texture> m_player_textures;
	sf::Texture m_lvl1_border_texture;
	sf::Texture m_lvl1_background_texture;
	sf::Texture m_flying_eye_texture;
	sf::Texture m_bullet_texture;
	static TextureHolder* m_texture_holder;

	TextureHolder() = default;
	TextureHolder(const TextureHolder&);

public:
	~TextureHolder();
	static TextureHolder* instance();

	void setTextures();

	std::map<State, sf::Texture> player_textures() const { return m_player_textures; };
	sf::Texture lvl1_border_texture() const { return m_lvl1_border_texture; };
	sf::Texture lvl1_background_texture() const { return m_lvl1_background_texture; };
	sf::Texture flying_eye_texture() const { return m_flying_eye_texture; };
	sf::Texture bullet_texture() const { return m_bullet_texture; };
};
